#ifndef TOMOCY_CPP_TODO_TODO_H
#define TOMOCY_CPP_TODO_TODO_H

#include <string>
#include <tuple>

namespace todo {
class Hash {
 public:
  Hash() = default;

  explicit Hash(const std::string& plain);

  bool Compare(const std::string& plain) const;

 private:
  std::size_t hash;
};
}  // namespace todo

namespace todo {
class User {
 public:
  User() = default;

  User(const std::string& id, const std::string& email,
       const std::string& password);

  const std::string& ID() const;

  const std::string& Email() const;

  const std::string& Password() const;

 private:
  std::string id;
  std::string email;
  std::string password;
};
}  // namespace todo

namespace todo {
class UserRepo {
 public:
  virtual ~UserRepo() {}
  virtual std::string NextID() = 0;
  virtual std::tuple<User, bool> FindByEmail(const std::string& email) = 0;
  virtual void Save(const User&) = 0;
};
}  // namespace todo

#endif