#include "todo.h"

#include <functional>
#include <string>

namespace todo {
Hash::Hash(const std::string& plain) noexcept
    : hash(std::hash<std::string>{}(plain)) {}

bool Hash::Compare(const std::string& plain) const {
  auto hash = std::hash<std::string>{}(plain);
  return this->hash == hash;
}

std::string Hash::ToString() const noexcept { return std::to_string(hash); }
}  // namespace todo

namespace todo {
User::User(const std::string& id, const std::string& email,
           const std::string& password) {
  setID(id);
  setEmail(email);
  setPassword(password);
}

const std::string& User::ID() const { return id; }

const std::string& User::Email() const { return email; }

const Hash& User::Password() const { return password; }

void User::setID(const std::string& id) {
  if (id.empty()) {
    throw Exception("id should not be empty");
  }

  this->id = id;
}

void User::setEmail(const std::string& email) {
  if (email.empty()) {
    throw Exception("email should not be empty");
  }

  this->email = email;
}

void User::setPassword(const std::string& password) {
  if (password.empty()) {
    throw Exception("password should not be empty");
  }

  this->password = Hash(password);
}
}  // namespace todo

namespace todo {
Task::Task(const std::string& id, const std::string& userID,
           const std::string& name)
    : completed(false) {
  setID(id);
  setUserID(userID);
  setName(name);
}

const std::string& Task::ID() const { return id; }

const std::string& Task::UserID() const { return userID; }

const std::string& Task::Name() const { return name; }

bool Task::IsCompleted() const { return completed; }

void Task::Complete() { completed = true; }

void Task::setID(const std::string& id) {
  if (id.empty()) {
    throw Exception("id should not be empty");
  }

  this->id = id;
}

void Task::setUserID(const std::string& userID) {
  if (userID.empty()) {
    throw Exception("user id should not be empty");
  }

  this->userID = userID;
}

void Task::setName(const std::string& name) {
  if (name.empty()) {
    throw Exception("name should not be empty");
  }

  this->name = name;
}
}  // namespace todo

namespace todo {
Exception::Exception(const std::string& msg) noexcept : msg(msg) {}

const char* Exception::what() const noexcept { return msg.c_str(); }
}  // namespace todo