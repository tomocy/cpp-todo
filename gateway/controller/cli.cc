#include "gateway/controller/cli.h"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"
#include "todo.h"
#include "usecase/usecase.h"

namespace controller::cli {
Command::Command(const std::string& name,
                 const std::map<std::string, std::string>& flags,
                 const std::vector<std::string>& args) noexcept
    : name(name), flags(flags), args(args) {}

const std::string& Command::Name() const noexcept { return name; }

const std::map<std::string, std::string> Command::Flags() const noexcept {
  return flags;
}

const std::string Command::Flag(const std::string& name) const noexcept {
  if (flags.find(name) == flags.end()) {
    return "";
  }

  return flags.at(name);
}

const std::vector<std::string>& Command::Args() const noexcept { return args; }
}  // namespace controller::cli

namespace controller::cli {
Command Parser::Parse(const std::vector<std::string>& args) const noexcept {
  if (args.size() < 1) {
    return Command("", std::map<std::string, std::string>(), args);
  }

  auto flags = std::map<std::string, std::string>();
  auto rest_args = std::vector<std::string>();

  if (args.size() == 1) {
    return Command(args.at(0), flags, rest_args);
  }
  if (args.size() == 2) {
    rest_args.push_back(args.at(1));
    return Command(args.at(0), flags, rest_args);
  }

  for (auto left = std::begin(args) + 1, right = std::begin(args) + 2;
       left != std::end(args) || right != std::end(args);
       left += 2, right += 2) {
    if (!(IsFlag(*left))) {
      std::for_each(left, std::end(args),
                    [&rest_args](auto arg) { rest_args.push_back(arg); });
      break;
    }

    flags[TrimFlagHyphen(*left)] = *right;
  }

  return Command(args.at(0), flags, rest_args);
}

bool Parser::IsFlag(const std::string& s) const noexcept {
  auto i = s.find("--");
  return i != std::string::npos && i == 0;
}

std::string Parser::TrimFlagHyphen(const std::string& s) const noexcept {
  auto i = s.find_first_not_of("-");
  if (i == std::string::npos) {
    return s;
  }

  return s.substr(i);
}
}  // namespace controller::cli

namespace controller::cli {
App::App(Session& session, todo::UserRepo& user_repo, todo::TaskRepo& task_repo,
         const controller::UserRenderer& user_ren,
         const controller::TaskRenderer& task_ren) noexcept
    : session(session),
      user_repo(user_repo),
      task_repo(task_repo),
      user_renderer(user_ren),
      task_renderer(task_ren) {}

void App::Run(int n, const char* const* const args) const noexcept {
  auto converted = std::vector<std::string>(args + 1, args + n);
  auto cmd = Parser().Parse(converted);

  if (cmd.Name() == "user") {
    auto app = UserApp(session, user_repo, user_renderer);
    app.Run(cmd.Args());
    return;
  }
  if (cmd.Name() == "task") {
    auto app = TaskApp(session, task_repo, task_renderer);
    app.Run(cmd.Args());
    return;
  }

  ShowHelp();
}

void App::ShowHelp() const noexcept {
  std::cout << "todo" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  user" << std::endl;
  std::cout << "  task" << std::endl;
}
}  // namespace controller::cli

namespace controller::cli {
UserApp::UserApp(Session& session, todo::UserRepo& repo,
                 const controller::UserRenderer& ren) noexcept
    : session(session), repo(repo), renderer(ren) {}

void UserApp::Run(const std::vector<std::string>& args) const noexcept {
  auto cmd = Parser().Parse(args);

  if (cmd.Name() == "create") {
    auto email = cmd.Flag("email"), password = cmd.Flag("password");
    Create(email, password);
    return;
  }
  if (cmd.Name() == "authenticate") {
    auto email = cmd.Flag("email"), password = cmd.Flag("password");
    Authenticate(email, password);
    return;
  }
  if (cmd.Name() == "deauthenticate") {
    Deauthenticate();
    return;
  }

  ShowHelp();
}

void UserApp::Create(const std::string& email,
                     const std::string& password) const noexcept {
  try {
    auto user = usecase::CreateUser(repo).Do(email, password);
    session.SetAuthenticatedUserID(user.ID());

    renderer.Show(user);
  } catch (const todo::Exception& e) {
    renderer.ShowErr(e.what());
  }
}

void UserApp::Authenticate(const std::string& email,
                           const std::string& password) const noexcept {
  auto [user, ok] = usecase::AuthenticateUser(repo).Do(email, password);
  if (!ok) {
    renderer.ShowErr("invalid credentials");
    return;
  }

  session.SetAuthenticatedUserID(user.ID());

  renderer.Show(user);
}

void UserApp::Deauthenticate() const noexcept {
  session.DropAuthenticatedUserID();
  renderer.ShowMessage("You are successfully logged out.");
}

void UserApp::ShowHelp() const noexcept {
  std::cout << "user" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  create" << std::endl;
  std::cout << "  authenticate" << std::endl;
  std::cout << "  deauthenticate" << std::endl;
}
}  // namespace controller::cli

namespace controller::cli {
TaskApp::TaskApp(Session& session, todo::TaskRepo& repo,
                 const controller::TaskRenderer& ren) noexcept
    : session(session), repo(repo), renderer(ren) {}

void TaskApp::Run(const std::vector<std::string>& args) const noexcept {
  auto cmd = Parser().Parse(args);

  if (cmd.Name() == "get") {
    auto [userID, found] = session.GetAuthenticatedUserID();
    if (!found) {
      renderer.ShowErr("You need to be authenticated to get tasks");
      return;
    }

    Get(userID);
    return;
  }

  if (cmd.Name() == "create") {
    auto [userID, found] = session.GetAuthenticatedUserID();
    if (!found) {
      renderer.ShowErr("You need to be authenticated to create a task");
      return;
    }

    auto name = cmd.Flag("name");
    Create(userID, name);
    return;
  }

  if (cmd.Name() == "complete") {
    auto [userID, found] = session.GetAuthenticatedUserID();
    if (!found) {
      renderer.ShowErr("You need to be authenticated to create a task");
      return;
    }

    auto id = cmd.Flag("id");
    Complete(id, userID);
    return;
  }

  if (cmd.Name() == "delete") {
    auto [userID, found] = session.GetAuthenticatedUserID();
    if (!found) {
      renderer.ShowErr("You need to be authenticated to delete a task");
      return;
    }

    auto id = cmd.Flag("id");
    Delete(id, userID);
    return;
  }

  ShowHelp();
}

void TaskApp::Get(const std::string& userID) const noexcept {
  auto tasks = usecase::GetTasks(repo).Do(userID);

  renderer.Show(tasks);
}

void TaskApp::Create(const std::string& userID, const std::string& name) const
    noexcept {
  try {
    auto task = usecase::CreateTask(repo).Do(userID, name);

    renderer.Show(task);
  } catch (const todo::Exception& e) {
    renderer.ShowErr(e.what());
  }
}

void TaskApp::Complete(const std::string& id, const std::string& userID) const
    noexcept {
  try {
    auto task = usecase::CompleteTask(repo).Do(id, userID);

    renderer.ShowMessage("The task is successfully completed.");
    renderer.Show(task);
  } catch (const todo::Exception& e) {
    renderer.ShowErr(e.what());
  }
}

void TaskApp::Delete(const std::string& id, const std::string& userID) const
    noexcept {
  try {
    usecase::DeleteTask(repo).Do(id, userID);
    renderer.ShowMessage("The task is successfully deleted.");
  } catch (const todo::Exception& e) {
    renderer.ShowErr(e.what());
  }
}

void TaskApp::ShowHelp() const noexcept {
  std::cout << "task" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  get" << std::endl;
  std::cout << "  create" << std::endl;
  std::cout << "  complete" << std::endl;
  std::cout << "  delete" << std::endl;
}
}  // namespace controller::cli