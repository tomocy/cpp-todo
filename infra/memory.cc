#include "infra/memory.h"

#include <map>
#include <random>
#include <string>
#include <tuple>

#include "infra/rand.h"
#include "todo.h"

namespace infra::memory {
Session::Session(std::map<std::string, std::string>&& data) noexcept
    : data(std::move(data)) {}

void Session::SetAuthenticatedUserID(const std::string& id) noexcept {
  data[kAuthenticatedUserID] = id;
}

std::tuple<std::string, bool> Session::GetAuthenticatedUserID() const noexcept {
  if (data.find(kAuthenticatedUserID) == data.end()) {
    return {"", false};
  }

  return {data.at(kAuthenticatedUserID), true};
}

void Session::DropAuthenticatedUserID() noexcept {
  data.erase(kAuthenticatedUserID);
}
}  // namespace infra::memory

namespace infra::memory {
UserRepo::UserRepo(std::map<std::string, todo::User>&& users) noexcept
    : users(std::move(users)) {}

std::string UserRepo::NextID() const noexcept {
  return infra::rand::Generate(30);
}

std::tuple<todo::User, bool> UserRepo::FindByEmail(
    const std::string& email) const noexcept {
  for (const auto [id, user] : users) {
    if (user.Email() == email) {
      return {user, true};
    }
  }

  return {todo::User(), false};
}

void UserRepo::Save(const todo::User& user) noexcept {
  users[user.ID()] = user;
}

const std::map<std::string, todo::User>& UserRepo::Users() const noexcept {
  return users;
}
}  // namespace infra::memory

namespace infra::memory {
TaskRepo::TaskRepo(std::map<std::string, todo::Task>&& tasks) noexcept
    : tasks(std::move(tasks)) {}

std::string TaskRepo::NextID() const noexcept {
  return infra::rand::Generate(50);
}

std::vector<todo::Task> TaskRepo::Get(const std::string& user_id) const
    noexcept {
  auto tasks = std::vector<todo::Task>();

  for (auto [_, task] : this->tasks) {
    if (task.UserID() != user_id) {
      continue;
    }

    tasks.push_back(task);
  }

  return tasks;
}

std::tuple<todo::Task, bool> TaskRepo::FindOfUser(
    const std::string& id, const std::string& user_id) const noexcept {
  if (tasks.find(id) == tasks.end()) {
    return {todo::Task(), false};
  }
  if (tasks.at(id).UserID() != user_id) {
    return {todo::Task(), false};
  }

  return {tasks.at(id), true};
}

void TaskRepo::Save(const todo::Task& task) noexcept {
  tasks[task.ID()] = task;
}

void TaskRepo::Delete(const std::string& id,
                      const std::string& user_id) noexcept {
  auto [_, found] = FindOfUser(id, user_id);
  if (!found) {
    return;
  }

  tasks.erase(id);
}

const std::map<std::string, todo::Task>& TaskRepo::Tasks() const noexcept {
  return tasks;
}
}  // namespace infra::memory