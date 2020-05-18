#include "todo.h"

#include <string>

namespace todo {
User::User(const std::string& id, const std::string& email,
           const std::string& password)
    : id(id), email(email), password(password) {}

const std::string& User::ID() const { return id; }

const std::string& User::Email() const { return email; }

const std::string& User::Password() const { return password; }
}  // namespace todo