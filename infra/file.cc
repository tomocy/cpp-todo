#include "infra/file.h"

#include <string>
#include <vector>

#include "todo.h"

namespace infra::file {
User::User(const todo::User& user)
    : id(user.ID()),
      email(user.Email()),
      password(user.Password().ToString()) {}
}  // namespace infra::file

namespace infra::file {
Store::Store(const std::vector<User>& users) : users(users) {}
}  // namespace infra::file