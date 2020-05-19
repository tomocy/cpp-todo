#ifndef TOMOCY_CPP_TODO_INFRA_MEMORY_H
#define TOMOCY_CPP_TODO_INFRA_MEMORY_H

#include <map>
#include <string>
#include <tuple>

#include "infra/rand.h"
#include "todo.h"

namespace infra::memory {
class UserRepo : public todo::UserRepo {
 public:
  UserRepo() = default;

  explicit UserRepo(std::map<std::string, todo::User>&& users);

  std::string NextID();

  std::tuple<todo::User, bool> FindByEmail(const std::string& email);

  void Save(const todo::User&);

  const std::map<std::string, todo::User>& Users();

 private:
  std::map<std::string, todo::User> users;
};
}  // namespace infra::memory

#endif