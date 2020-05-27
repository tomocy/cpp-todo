#include "infra/file.h"

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "external/json/single_include/nlohmann/json.hpp"
#include "infra/rand.h"
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

namespace infra::file {
File::File(const std::string& workspace) noexcept : workspace(workspace) {}

Store File::Load() const noexcept {
  std::ifstream file(StorePath());
  nlohmann::json json;
  file >> json;

  return json.get<Store>();
}

void File::Save(const Store& store) const noexcept {
  std::ofstream file(StorePath());
  auto json = nlohmann::json(store);

  file << json;
}

std::string File::StorePath() const noexcept {
  return workspace + "/store.json";
}
}  // namespace infra::file

namespace infra::file {
UserRepo::UserRepo(const std::string& workspace) noexcept
    : file(File(workspace)) {}

std::string UserRepo::NextID() const noexcept {
  return infra::rand::Generate(30);
}

std::tuple<todo::User, bool> UserRepo::FindByEmail(
    const std::string& email) const noexcept {
  auto store = file.Load();

  for (auto user : store.users) {
    if (user.email != email) {
      continue;
    }

    return {user.ToUser(), true};
  }

  return {todo::User(), false};
}

void UserRepo::Save(const todo::User& user) noexcept {
  auto store = file.Load();
  for (auto i = 0; i < store.users.size(); ++i) {
    if (store.users.at(i).id != user.ID()) {
      continue;
    }

    store.users.at(i) = user;
    file.Save(store);
    return;
  }

  store.users.push_back(user);
  file.Save(store);
}
}  // namespace infra::file