#ifndef TOMOCY_CPP_TODO_USECASE_USECASE_H
#define TOMOCY_CPP_TODO_USECASE_USECASE_H

#include <tuple>
#include <vector>

#include "todo.h"

namespace usecase {
class CreateUser {
 public:
  CreateUser(todo::UserRepo& repo) noexcept;

  todo::User Do(const std::string& email, const std::string& password);

 private:
  todo::UserRepo& repo;
};
}  // namespace usecase

namespace usecase {
class AuthenticateUser {
 public:
  AuthenticateUser(const todo::UserRepo& repo) noexcept;

  std::tuple<todo::User, bool> Do(const std::string& email,
                                  const std::string& password) const noexcept;

 private:
  const todo::UserRepo& repo;
};
}  // namespace usecase

namespace usecase {
class GetTasks {
 public:
  GetTasks(const todo::TaskRepo& repo) noexcept;

  std::vector<todo::Task> Do(const std::string& userID) const noexcept;

 private:
  const todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class CreateTask {
 public:
  CreateTask(todo::TaskRepo& repo) noexcept;

  todo::Task Do(const std::string& userID, const std::string& name);

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class CompleteTask {
 public:
  CompleteTask(todo::TaskRepo& repo) noexcept;

  todo::Task Do(const std::string& id, const std::string& userID) noexcept;

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class DeleteTask {
 public:
  DeleteTask(todo::TaskRepo& repo) noexcept;

  void Do(const std::string& id, const std::string& userID) noexcept;

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

#endif