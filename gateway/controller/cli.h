#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "gateway/controller/controller.h"
#include "todo.h"

namespace controller::cli {
class Command {
 public:
  Command(const std::string& name,
          const std::map<std::string, std::string>& flags,
          const std::vector<std::string>& args) noexcept;

  const std::string& Name() const noexcept;

  const std::map<std::string, std::string> Flags() const noexcept;

  const std::string Flag(const std::string& name) const noexcept;

  const std::vector<std::string>& Args() const noexcept;

 private:
  std::string name;
  std::map<std::string, std::string> flags;
  std::vector<std::string> args;
};
}  // namespace controller::cli

namespace controller::cli {
class Parser {
 public:
  Command Parse(const std::vector<std::string>& args) const noexcept;

 private:
  bool IsFlag(const std::string& s) const noexcept;

  std::string TrimFlagHyphen(const std::string& s) const noexcept;
};
}  // namespace controller::cli

namespace controller::cli {
class Session {
 public:
  virtual ~Session() {}
  virtual void SetAuthenticatedUserID(const std::string& id) noexcept = 0;
  virtual std::tuple<std::string, bool> GetAuthenticatedUserID() const
      noexcept = 0;
};
}  // namespace controller::cli

namespace controller::cli {
class App {
 public:
  App(Session& session, todo::UserRepo& userRepo, todo::TaskRepo& taskRepo,
      const controller::UserRenderer& userRen,
      const controller::TaskRenderer& taskRen) noexcept;

  void Run(int n, const char* const* args) const noexcept;

 private:
  void ShowHelp() const noexcept;

  Session& session;
  todo::UserRepo& userRepo;
  todo::TaskRepo& taskRepo;
  const controller::UserRenderer& userRenderer;
  const controller::TaskRenderer& taskRenderer;
};
}  // namespace controller::cli

namespace controller::cli {
class UserApp {
 public:
  UserApp(Session& session, todo::UserRepo& repo,
          const controller::UserRenderer& ren) noexcept;

  void Run(const std::vector<std::string>& args) const noexcept;

 private:
  void Create(const std::string& email, const std::string& password) const
      noexcept;

  void Authenticate(const std::string& email, const std::string& password) const
      noexcept;

  void ShowHelp() const noexcept;

  Session& session;
  todo::UserRepo& repo;
  const controller::UserRenderer& renderer;
};
}  // namespace controller::cli

namespace controller::cli {
class TaskApp {
 public:
  TaskApp(Session& session, todo::TaskRepo& repo,
          const controller::TaskRenderer& ren) noexcept;

  void Run(const std::vector<std::string>& args) const noexcept;

 private:
  void Get(const std::string& userID) const noexcept;

  void Create(const std::string& userID, const std::string& name) const
      noexcept;

  void Complete(const std::string& id, const std::string& userID) const
      noexcept;

  void Delete(const std::string& id, const std::string& userID) const noexcept;

  void ShowHelp() const noexcept;

  Session& session;
  todo::TaskRepo& repo;
  const controller::TaskRenderer& renderer;
};
}  // namespace controller::cli

#endif