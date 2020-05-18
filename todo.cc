#include "todo.h"

#include <string>

namespace todo {
User::User(const std::string& id, const std::string& email)
    : id(id), email(email) {}

const std::string& User::ID() const { return id; }

const std::string& User::Email() const { return email; }
}  // namespace todo