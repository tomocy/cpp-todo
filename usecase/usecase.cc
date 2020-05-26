#include "usecase/usecase.h"

#include <string>
#include <tuple>
#include <vector>

#include "todo.h"

namespace usecase {
CreateUser::CreateUser(todo::UserRepo& repo) : repo(repo) {}

todo::User CreateUser::Do(const std::string& email,
                          const std::string& password) {
  auto id = repo.NextID();
  auto user = todo::User(id, email, password);

  repo.Save(user);

  return user;
}
}  // namespace usecase

namespace usecase {
AuthenticateUser::AuthenticateUser(todo::UserRepo& repo) : repo(repo) {}

std::tuple<todo::User, bool> AuthenticateUser::Do(const std::string& email,
                                                  const std::string& password) {
  auto [user, found] = repo.FindByEmail(email);
  if (!found) {
    return {todo::User(), false};
  }

  if (!user.Password().Compare(password)) {
    return {todo::User(), false};
  }

  return {user, true};
}
}  // namespace usecase

namespace usecase {
GetTasks::GetTasks(todo::TaskRepo& repo) : repo(repo) {}

std::vector<todo::Task> GetTasks::Do(const std::string& userID) {
  return repo.Get(userID);
}
}  // namespace usecase

namespace usecase {
CreateTask::CreateTask(todo::TaskRepo& repo) : repo(repo) {}

todo::Task CreateTask::Do(const std::string& userID, const std::string& name) {
  auto id = repo.NextID();
  auto task = todo::Task(id, userID, name);

  repo.Save(task);

  return task;
}
}  // namespace usecase

namespace usecase {
CompleteTask::CompleteTask(todo::TaskRepo& repo) : repo(repo) {}

todo::Task CompleteTask::Do(const std::string& id, const std::string& userID) {
  auto [task, found] = repo.FindOfUser(id, userID);
  if (!found) {
    return todo::Task();
  }

  task.Complete();

  repo.Save(task);

  return task;
}
}  // namespace usecase

namespace usecase {
DeleteTask::DeleteTask(todo::TaskRepo& repo) : repo(repo) {}

void DeleteTask::Do(const std::string& id, const std::string& userID) {
  auto [task, found] = repo.FindOfUser(id, userID);
  if (!found) {
    return;
  }

  repo.Delete(task);
}
}  // namespace usecase