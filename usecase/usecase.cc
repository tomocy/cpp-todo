#include "usecase/usecase.h"

#include <string>

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