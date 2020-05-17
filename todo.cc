#include "todo.h"

#include <string>

namespace todo {
User::User(const std::string& id) : id(id) {}

const std::string& User::ID() const { return id; }
}  // namespace todo