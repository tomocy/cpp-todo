#include "infra/file.h"

#include <string>
#include <vector>

#include "external/json/single_include/nlohmann/json.hpp"
#include "todo.h"

namespace infra::file {
User::User(const todo::User& user) noexcept
    : id(user.ID()),
      email(user.Email()),
      password(user.Password().ToString()) {}

todo::User User::ToUser() const noexcept {
  return todo::User(id, email, todo::Hash(todo::HashedString(password)));
}

void to_json(nlohmann::json& json, const User& user) {
  json = nlohmann::json{
      {"id", user.id}, {"email", user.email}, {"password", user.password}};
}

void from_json(const nlohmann::json& json, User& user) {
  json.at("id").get_to(user.id);
  json.at("email").get_to(user.email);
  json.at("password").get_to(user.password);
}
}  // namespace infra::file

namespace infra::file {
Store::Store(const std::vector<User>& users) noexcept : users(users) {}

void to_json(nlohmann::json& json, const Store& store) {
  json = nlohmann::json{{"users", store.users}};
}

void from_json(const nlohmann::json& json, Store& store) {
  json.at("users").get_to(store);
}
}  // namespace infra::file