#include "usecase/usecase.h"

#include <string>
#include <tuple>

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