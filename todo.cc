#include "todo.h"

#include <functional>
#include <string>

#include "external/bcrypt/include/bcrypt/BCrypt.hpp"

namespace todo {
HashedString::HashedString(const std::string& s) noexcept : s(s) {}

const std::string& HashedString::ToString() const noexcept { return s; }
}  // namespace todo

namespace todo {
Hash::Hash(const std::string& plain) noexcept
    : hash(BCrypt::generateHash(plain)) {}

Hash::Hash(const HashedString& hash) noexcept : hash(hash.ToString()) {}

bool Hash::Compare(const std::string& plain) const {
  return BCrypt::validatePassword(plain, hash);
}

std::string Hash::ToString() const noexcept { return hash; }
}  // namespace todo

namespace todo {
User::User(const std::string& id, const std::string& email,
           const std::string& password) {
  setID(id);
  setEmail(email);
  setPassword(password);
}

User::User(const std::string& id, const std::string& email,
           const Hash& password) {
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

void User::setPassword(const Hash& password) { this->password = password; }

void User::setPassword(const std::string& password) {
  if (password.empty()) {
    throw Exception("password should not be empty");
  }

  this->password = Hash(password);
}
}  // namespace todo

namespace todo {
Task::Task(const std::string& id, const std::string& user_id,
           const std::string& name)
    : completed(false) {
  setID(id);
  setUserID(user_id);
  setName(name);
}

Task::Task(const std::string& id, const std::string& user_id,
           const std::string& name, bool completed)
    : completed(completed) {
  setID(id);
  setUserID(user_id);
  setName(name);
}

const std::string& Task::ID() const { return id; }

const std::string& Task::UserID() const { return user_id; }

const std::string& Task::Name() const { return name; }

bool Task::IsCompleted() const { return completed; }

void Task::Complete() { completed = true; }

void Task::setID(const std::string& id) {
  if (id.empty()) {
    throw Exception("id should not be empty");
  }

  this->id = id;
}

void Task::setUserID(const std::string& user_id) {
  if (user_id.empty()) {
    throw Exception("user id should not be empty");
  }

  this->user_id = user_id;
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