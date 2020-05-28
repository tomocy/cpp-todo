#include "infra/file.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

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
Task::Task(const todo::Task& task) noexcept
    : id(task.ID()),
      userID(task.UserID()),
      name(task.Name()),
      completed(task.IsCompleted()) {}

todo::Task Task::ToTask() const noexcept {
  return todo::Task(id, userID, name, completed);
}

void to_json(nlohmann::json& json, const Task& task) {
  json = nlohmann::json{{"id", task.id},
                        {"user_id", task.userID},
                        {"name", task.name},
                        {"completed", task.completed}};
}

void from_json(const nlohmann::json& json, Task& task) {
  json.at("id").get_to(task.id);
  json.at("user_id").get_to(task.userID);
  json.at("name").get_to(task.name);
  json.at("completed").get_to(task.completed);
}
}  // namespace infra::file

namespace infra::file {
Store::Store() noexcept : users(std::map<std::string, User>()) {}

Store::Store(const std::map<std::string, std::string>& session,
             const std::map<std::string, User>& users,
             const std::map<std::string, Task>& tasks) noexcept
    : session(session), users(users), tasks(tasks) {}

void to_json(nlohmann::json& json, const Store& store) {
  json = nlohmann::json{{"session", store.session},
                        {"users", store.users},
                        {"tasks", store.tasks}};
}

void from_json(const nlohmann::json& json, Store& store) {
  json.at("session").get_to(store.session);
  json.at("users").get_to(store.users);
  json.at("tasks").get_to(store.tasks);
}
}  // namespace infra::file

namespace infra::file {
File::File(const std::string& workspace) noexcept : workspace(workspace) {
  InitWorkspaceIfNotExist();
}

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

void File::InitWorkspaceIfNotExist() const noexcept {
  if (DoesStoreFileExist()) {
    return;
  }

  std::ofstream file(StorePath());
  auto json = nlohmann::json(Store());

  file << json << std::endl;
}

bool File::DoesStoreFileExist() const noexcept {
  return std::filesystem::exists(StorePath());
}

std::string File::StorePath() const noexcept {
  return workspace + "/store.json";
}
}  // namespace infra::file

namespace infra::file {
Session::Session(const std::string& workspace) noexcept
    : file(File(workspace)) {}

void Session::SetAuthenticatedUserID(const std::string& userID) noexcept {
  auto store = file.Load();

  store.session[kAuthenticatedUserID] = userID;

  file.Save(store);
}

std::tuple<std::string, bool> Session::GetAuthenticatedUserID() const noexcept {
  auto store = file.Load();

  if (store.session.find(kAuthenticatedUserID) == store.session.end()) {
    return {"", false};
  }

  return {store.session.at(kAuthenticatedUserID), true};
}

void Session::DropAuthenticatedUserID() noexcept {
  auto store = file.Load();

  store.session.erase(kAuthenticatedUserID);

  file.Save(store);
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

  for (auto [_, user] : store.users) {
    if (user.email != email) {
      continue;
    }

    return {user.ToUser(), true};
  }

  return {todo::User(), false};
}

void UserRepo::Save(const todo::User& user) noexcept {
  auto store = file.Load();

  auto converted = User(user);
  store.users[converted.id] = converted;

  file.Save(store);
}
}  // namespace infra::file

namespace infra::file {
TaskRepo::TaskRepo(const std::string& workspace) noexcept
    : file(File(workspace)) {}

std::string TaskRepo::NextID() const noexcept {
  return infra::rand::Generate(50);
}

std::vector<todo::Task> TaskRepo::Get(const std::string& userID) const
    noexcept {
  auto store = file.Load();

  auto tasks = std::vector<todo::Task>();
  for (auto [_, task] : store.tasks) {
    if (task.userID != userID) {
      continue;
    }

    tasks.push_back(task.ToTask());
  }

  return tasks;
}

std::tuple<todo::Task, bool> TaskRepo::FindOfUser(
    const std::string& id, const std::string& userID) const noexcept {
  auto store = file.Load();

  if (store.tasks.find(id) == store.tasks.end()) {
    return {todo::Task(), false};
  }
  if (store.tasks.at(id).userID != userID) {
    return {todo::Task(), false};
  }

  return {store.tasks.at(id).ToTask(), true};
}

void TaskRepo::Save(const todo::Task& task) noexcept {
  auto store = file.Load();

  auto converted = Task(task);
  store.tasks[converted.id] = converted;

  file.Save(store);
}

void TaskRepo::Delete(const std::string& id,
                      const std::string& userID) noexcept {
  auto [task, found] = FindOfUser(id, userID);
  if (!found) {
    return;
  }

  auto store = file.Load();

  store.tasks.erase(task.ID());

  file.Save(store);
}
}  // namespace infra::file