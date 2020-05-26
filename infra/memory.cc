#include "infra/memory.h"

#include <map>
#include <random>
#include <string>
#include <tuple>

#include "infra/rand.h"
#include "todo.h"

namespace infra::memory {
Session::Session(std::map<std::string, std::string>&& data)
    : data(std::move(data)) {}

void Session::SetAuthenticatedUserID(const std::string& id) {
  data[kAuthenticatedUserID] = id;
}

std::tuple<std::string, bool> Session::GetAuthenticatedUserID() {
  if (data.find(kAuthenticatedUserID) == data.end()) {
    return {"", false};
  }

  return {data.at(kAuthenticatedUserID), true};
}
}  // namespace infra::memory

namespace infra::memory {
UserRepo::UserRepo(std::map<std::string, todo::User>&& users)
    : users(std::move(users)) {}

std::string UserRepo::NextID() { return infra::rand::Generate(30); }

std::tuple<todo::User, bool> UserRepo::FindByEmail(const std::string& email) {
  for (const auto [id, user] : users) {
    if (user.Email() == email) {
      return {user, true};
    }
  }

  return {todo::User(), false};
}

void UserRepo::Save(const todo::User& user) { users[user.ID()] = user; }

const std::map<std::string, todo::User>& UserRepo::Users() { return users; }
}  // namespace infra::memory

namespace infra::memory {
TaskRepo::TaskRepo(std::map<std::string, todo::Task>&& tasks)
    : tasks(std::move(tasks)) {}

std::string TaskRepo::NextID() { return infra::rand::Generate(50); }

std::vector<todo::Task> TaskRepo::Get(const std::string& userID) {
  auto tasks = std::vector<todo::Task>();

  for (auto [_, task] : this->tasks) {
    if (task.UserID() != userID) {
      continue;
    }

    tasks.push_back(task);
  }

  return tasks;
}

std::tuple<todo::Task, bool> TaskRepo::FindOfUser(const std::string& id,
                                                  const std::string& userID) {
  if (tasks.find(id) == tasks.end()) {
    return {todo::Task(), false};
  }
  if (tasks.at(id).UserID() != userID) {
    return {todo::Task(), false};
  }

  return {tasks.at(id), true};
}

void TaskRepo::Save(const todo::Task& task) { tasks[task.ID()] = task; }

void TaskRepo::Delete(const todo::Task& task) { tasks.erase(task.ID()); }
}  // namespace infra::memory