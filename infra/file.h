#ifndef TOMOCY_CPP_TODO_INFRA_FILE_H
#define TOMOCY_CPP_TODO_INFRA_FILE_H

#include <string>
#include <vector>

#include "external/json/single_include/nlohmann/json.hpp"
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

void to_json(nlohmann::json& json, const User& user);

void from_json(const nlohmann::json& json, User& user);
}  // namespace infra::file

namespace infra::file {
struct Store {
 public:
  Store() = default;

  Store(const std::vector<User>& users) noexcept;

  std::vector<User> users;
};

void to_json(nlohmann::json& json, const Store& store);

void from_json(const nlohmann::json& json, Store& store);
}  // namespace infra::file

#endif