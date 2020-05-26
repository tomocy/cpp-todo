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

  explicit Session(std::map<std::string, std::string>&& data) noexcept;

  void SetAuthenticatedUserID(const std::string& id) noexcept override;

  std::tuple<std::string, bool> GetAuthenticatedUserID() const
      noexcept override;

 private:
  const std::string kAuthenticatedUserID = "authenticated_user_id";

  std::map<std::string, std::string> data;
};
}  // namespace infra::memory

namespace infra::memory {
class UserRepo : public todo::UserRepo {
 public:
  UserRepo() = default;

  explicit UserRepo(std::map<std::string, todo::User>&& users) noexcept;

  std::string NextID() const noexcept;

  std::tuple<todo::User, bool> FindByEmail(const std::string& email) const
      noexcept;

  void Save(const todo::User&) noexcept;

  const std::map<std::string, todo::User>& Users() const noexcept;

 private:
  std::map<std::string, todo::User> users;
};
}  // namespace infra::memory

namespace infra::memory {
class TaskRepo : public todo::TaskRepo {
 public:
  TaskRepo() = default;

  explicit TaskRepo(std::map<std::string, todo::Task>&& tasks) noexcept;

  std::string NextID() const noexcept override;

  std::vector<todo::Task> Get(const std::string& userID) const
      noexcept override;

  std::tuple<todo::Task, bool> FindOfUser(const std::string& id,
                                          const std::string& userID) const
      noexcept override;

  void Save(const todo::Task& task) noexcept override;

  void Delete(const todo::Task& task) noexcept override;

  const std::map<std::string, todo::Task>& Tasks() const noexcept;

 private:
  std::map<std::string, todo::Task> tasks;
};
}  // namespace infra::memory

#endif