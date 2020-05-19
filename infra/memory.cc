#include "infra/memory.h"

#include <random>
#include <string>
#include <tuple>

#include "infra/rand.h"
#include "todo.h"

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