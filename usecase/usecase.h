#ifndef TOMOCY_CPP_TODO_USECASE_USECASE_H
#define TOMOCY_CPP_TODO_USECASE_USECASE_H

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

#endif