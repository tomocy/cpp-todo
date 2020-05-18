#include "gateway/controller/cli.h"

#include <iostream>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"
#include "todo.h"
#include "usecase/usecase.h"

namespace controller::cli {
Command::Command(const std::string& name, const std::vector<std::string>& args)
    : name(name), args(args) {}

const std::string& Command::Name() const { return name; }

const std::vector<std::string>& Command::Args() const { return args; }
}  // namespace controller::cli

namespace controller::cli {
Command Parser::Parse(const std::vector<std::string>& args) {
  if (args.size() < 1) {
    return Command("", args);
  }

  return Command(args.at(0), std::vector<std::string>(std::begin(args) + 1,
                                                      std::end(args)));
}
}  // namespace controller::cli

namespace controller::cli {
App::App(todo::UserRepo& userRepo, const controller::Renderer& ren)
    : userRepo(userRepo), renderer(ren) {}

void App::Run(int n, const char* const* const args) const {
  auto converted = std::vector<std::string>(args + 1, args + n);
  auto cmd = Parser().Parse(converted);

  if (cmd.Name() == "user") {
    auto app = UserApp(userRepo, renderer);
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
}
}  // namespace controller::cli

namespace controller::cli {
UserApp::UserApp(todo::UserRepo& repo, const controller::Renderer& ren)
    : repo(repo), renderer(ren) {}

void UserApp::Run(const std::vector<std::string>& args) const {
  auto cmd = Parser().Parse(args);

  if (cmd.Name() == "create") {
    auto email = "email", password = "password";
    Create(email, password);
    return;
  }

  ShowHelp();
}

void UserApp::Create(const std::string& email,
                     const std::string& password) const {
  auto create = usecase::CreateUser(repo);
  auto user = create.Do(email, password);

  renderer.ShowUser(user);
}

void UserApp::ShowHelp() const {
  std::cout << "user" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
  std::cout << "  create" << std::endl;
}
}  // namespace controller::cli