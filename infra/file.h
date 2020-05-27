#ifndef TOMOCY_CPP_TODO_INFRA_FILE_H
#define TOMOCY_CPP_TODO_INFRA_FILE_H

#include <string>
#include <vector>

#include "todo.h"

namespace infra::file {
struct User {
 public:
  User() = default;

  User(const todo::User& user) noexcept;

  todo::User ToUser() const noexcept;

  std::string id;
  std::string email;
  std::string password;
};
}  // namespace infra::file

namespace infra::file {
struct Store {
 public:
  Store() = default;

  Store(const std::vector<User>& users);

  std::vector<User> users;
};
}  // namespace infra::file

#endif