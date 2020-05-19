#ifndef TOMOCY_CPP_TODO_INFRA_MEMORY_H
#define TOMOCY_CPP_TODO_INFRA_MEMORY_H

#include <map>
#include <string>
#include <tuple>

#include "gateway/controller/cli.h"
#include "infra/rand.h"
#include "todo.h"

namespace infra::memory {
class Session : public controller::cli::Session {
 public:
  Session() = default;

  explicit Session(std::map<std::string, std::string>&& data);

  void SetAuthenticatedUserID(const std::string& id) override;

  std::tuple<std::string, bool> GetAuthenticatedUserID() override;

 private:
  const std::string kAuthenticatedUserID = "authenticated_user_id";

  std::map<std::string, std::string> data;
};
}  // namespace infra::memory

namespace infra::memory {
class UserRepo : public todo::UserRepo {
 public:
  UserRepo() = default;

  explicit UserRepo(std::map<std::string, todo::User>&& users);

  std::string NextID();

  std::tuple<todo::User, bool> FindByEmail(const std::string& email);

  void Save(const todo::User&);

  const std::map<std::string, todo::User>& Users();

 private:
  std::map<std::string, todo::User> users;
};
}  // namespace infra::memory

namespace infra::memory {
class TaskRepo : public todo::TaskRepo {
 public:
  TaskRepo() = default;

  explicit TaskRepo(std::map<std::string, todo::Task>&& tasks);

  std::string NextID() override;

  std::vector<todo::Task> Get(const std::string& userID) override;

  void Save(const todo::Task& task) override;

  const std::map<std::string, todo::Task>& Tasks();

 private:
  std::map<std::string, todo::Task> tasks;
};
}  // namespace infra::memory

#endif