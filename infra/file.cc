#include "infra/file.h"

#include <string>
#include <vector>

#include "todo.h"

namespace infra::file {
User::User(const todo::User& user) noexcept
    : id(user.ID()),
      email(user.Email()),
      password(user.Password().ToString()) {}

todo::User User::ToUser() const noexcept {
  return todo::User(id, email, todo::Hash(todo::HashedString(password)));
}
}  // namespace infra::file

namespace infra::file {
Store::Store(const std::vector<User>& users) noexcept : users(users) {}
}  // namespace infra::file