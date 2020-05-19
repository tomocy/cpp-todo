#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"
#include "todo.h"

namespace controller::cli {
class Command {
 public:
  Command(const std::string& name,
          const std::map<std::string, std::string>& flags,
          const std::vector<std::string>& args);

  const std::string& Name() const;

  const std::map<std::string, std::string> Flags() const;

  const std::string Flag(const std::string& name) const;

  const std::vector<std::string>& Args() const;

 private:
  std::string name;
  std::map<std::string, std::string> flags;
  std::vector<std::string> args;
};
}  // namespace controller::cli

namespace controller::cli {
class Parser {
 public:
  Command Parse(const std::vector<std::string>& args) const;

 private:
  bool IsFlag(const std::string& s) const;

  std::string TrimFlagHyphen(const std::string& s) const;
};
}  // namespace controller::cli

namespace controller::cli {
class App {
 public:
  App(todo::UserRepo& userRepo, todo::TaskRepo& taskRepo,
      const controller::UserRenderer& userRen,
      const controller::TaskRenderer& taskRen);

  void Run(int n, const char* const* args) const;

 private:
  void ShowHelp() const;

  todo::UserRepo& userRepo;
  todo::TaskRepo& taskRepo;
  const controller::UserRenderer& userRenderer;
  const controller::TaskRenderer& taskRenderer;
};
}  // namespace controller::cli

namespace controller::cli {
class UserApp {
 public:
  UserApp(todo::UserRepo& repo, const controller::UserRenderer& ren);

  void Run(const std::vector<std::string>& args) const;

 private:
  void Create(const std::string& email, const std::string& password) const;

  void Authenticate(const std::string& email,
                    const std::string& password) const;

  void ShowHelp() const;

  todo::UserRepo& repo;
  const controller::UserRenderer& renderer;
};
}  // namespace controller::cli

namespace controller::cli {
class TaskApp {
 public:
  TaskApp(todo::TaskRepo& repo, const controller::TaskRenderer& ren);

  void Run(const std::vector<std::string>& args) const;

 private:
  void ShowHelp() const;

  todo::TaskRepo& repo;
  const controller::TaskRenderer& renderer;
};
}  // namespace controller::cli

#endif