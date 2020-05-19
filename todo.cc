#include "todo.h"

#include <functional>
#include <string>

namespace todo {
Hash::Hash(const std::string& plain) : hash(std::hash<std::string>{}(plain)) {}

bool Hash::Compare(const std::string& plain) const {
  auto hash = std::hash<std::string>{}(plain);
  return this->hash == hash;
}
}  // namespace todo

namespace todo {
User::User(const std::string& id, const std::string& email,
           const std::string& password)
    : id(id), email(email), password(Hash(password)) {}

const std::string& User::ID() const { return id; }

const std::string& User::Email() const { return email; }

const Hash& User::Password() const { return password; }
}  // namespace todo

namespace todo {
Task::Task(const std::string& id, const std::string& userID,
           const std::string& name)
    : id(id), userID(userID), name(name) {}

const std::string& Task::ID() const { return id; }

const std::string& Task::UserID() const { return userID; }

const std::string& Task::Name() const { return name; }
}  // namespace todo