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
                 const std::vector<std::string>& args)
    : name(name), flags(flags), args(args) {}

const std::string& Command::Name() const { return name; }

const std::map<std::string, std::string> Command::Flags() const {
  return flags;
}

const std::string Command::Flag(const std::string& name) const {
  if (flags.find(name) == flags.end()) {
    return "";
  }

  return flags.at(name);
}

const std::vector<std::string>& Command::Args() const { return args; }
}  // namespace controller::cli

namespace controller::cli {
Command Parser::Parse(const std::vector<std::string>& args) const {
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

bool Parser::IsFlag(const std::string& s) const {
  auto i = s.find("-");
  return i != std::string::npos && i == 0;
}

std::string Parser::TrimFlagHyphen(const std::string& s) const {
  auto i = s.find_first_not_of("-");
  if (i == std::string::npos) {
    return s;
  }

  return s.substr(i);
}
}  // namespace controller::cli

namespace controller::cli {
App::App(Session& session, todo::UserRepo& userRepo, todo::TaskRepo& taskRepo,
         const controller::UserRenderer& userRen,
         const controller::TaskRenderer& taskRen)
    : session(session),
      userRepo(userRepo),
      taskRepo(taskRepo),
      userRenderer(userRen),
      taskRenderer(taskRen) {}

void App::Run(int n, const char* const* const args) const {
  auto converted = std::vector<std::string>(args + 1, args + n);
  auto cmd = Parser().Parse(converted);

  if (cmd.Name() == "user") {
    auto app = UserApp(session, userRepo, userRenderer);
    app.Run(cmd.Args());
    return;
  }
  if (cmd.Name() == "task") {
    auto app = TaskApp(session, taskRepo, taskRenderer);
    app.Run(cmd.Args());
    return;
  }

  ShowHelp();
}

void App::ShowHelp() const {
  std::cout << "todo" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  user" << std::endl;
  std::cout << "  task" << std::endl;
}
}  // namespace controller::cli

namespace controller::cli {
UserApp::UserApp(Session& session, todo::UserRepo& repo,
                 const controller::UserRenderer& ren)
    : session(session), repo(repo), renderer(ren) {}

void UserApp::Run(const std::vector<std::string>& args) const {
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

  ShowHelp();
}

void UserApp::Create(const std::string& email,
                     const std::string& password) const {
  auto create = usecase::CreateUser(repo);
  auto user = create.Do(email, password);

  session.SetAuthenticatedUserID(user.ID());

  renderer.Show(user);
}

void UserApp::Authenticate(const std::string& email,
                           const std::string& password) const {
  auto authenticate = usecase::AuthenticateUser(repo);
  auto [user, ok] = authenticate.Do(email, password);
  if (!ok) {
    renderer.ShowErr("invalid credentials");
    return;
  }

  session.SetAuthenticatedUserID(user.ID());

  renderer.Show(user);
}

void UserApp::ShowHelp() const {
  std::cout << "user" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  create" << std::endl;
  std::cout << "  authenticate" << std::endl;
}
}  // namespace controller::cli

namespace controller::cli {
TaskApp::TaskApp(Session& session, todo::TaskRepo& repo,
                 const controller::TaskRenderer& ren)
    : session(session), repo(repo), renderer(ren) {}

void TaskApp::Run(const std::vector<std::string>& args) const {
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

  if (cmd.Name() == "delete") {
    auto [userID, found] = session.GetAuthenticatedUserID();
    if (!found) {
      renderer.ShowErr("You need to be authenticated to delete a task");
      return;
    }

    auto id = cmd.Flag("id");
    Delete(id);
    return;
  }

  ShowHelp();
}

void TaskApp::Get(const std::string& userID) const {
  auto get = usecase::GetTasks(repo);
  auto tasks = get.Do(userID);

  renderer.Show(tasks);
}

void TaskApp::Create(const std::string& userID, const std::string& name) const {
  auto create = usecase::CreateTask(repo);
  auto task = create.Do(userID, name);

  renderer.Show(task);
}

void TaskApp::Delete(const std::string& id) const {
  usecase::DeleteTask(repo).Do(id);
}

void TaskApp::ShowHelp() const {
  std::cout << "task" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  get" << std::endl;
  std::cout << "  create" << std::endl;
  std::cout << "  delete" << std::endl;
}
}  // namespace controller::cli