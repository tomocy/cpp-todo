#include "infra/memory.h"

#include <random>
#include <string>

#include "infra/rand.h"
#include "todo.h"

namespace infra::memory {
std::string UserRepo::NextID() { return infra::rand::Generate(30); }

void UserRepo::Save(const todo::User& user) { users[user.ID()] = user; }

const std::map<std::string, todo::User>& UserRepo::Users() { return users; }
}  // namespace infra::memory