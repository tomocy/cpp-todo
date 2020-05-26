#ifndef TOMOCY_CPP_TODO_USECASE_USECASE_H
#define TOMOCY_CPP_TODO_USECASE_USECASE_H

#include <tuple>
#include <vector>

#include "todo.h"

namespace usecase {
class CreateUser {
 public:
  CreateUser(todo::UserRepo& repo);

  todo::User Do(const std::string& email, const std::string& password);

 private:
  todo::UserRepo& repo;
};
}  // namespace usecase

namespace usecase {
class AuthenticateUser {
 public:
  AuthenticateUser(todo::UserRepo& repo);

  std::tuple<todo::User, bool> Do(const std::string& email,
                                  const std::string& password);

 private:
  todo::UserRepo& repo;
};
}  // namespace usecase

namespace usecase {
class GetTasks {
 public:
  GetTasks(todo::TaskRepo& repo);

  std::vector<todo::Task> Do(const std::string& userID);

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class CreateTask {
 public:
  CreateTask(todo::TaskRepo& repo);

  todo::Task Do(const std::string& userID, const std::string& name);

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class CompleteTask {
 public:
  CompleteTask(todo::TaskRepo& repo);

  todo::Task Do(const std::string& id, const std::string& userID);

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

namespace usecase {
class DeleteTask {
 public:
  DeleteTask(todo::TaskRepo& repo);

  void Do(const std::string& id);

 private:
  todo::TaskRepo& repo;
};
}  // namespace usecase

#endif