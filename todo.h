#ifndef TOMOCY_CPP_TODO_TODO_H
#define TOMOCY_CPP_TODO_TODO_H

#include <string>

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

class UserRepo {
 public:
  virtual ~UserRepo() {}
  virtual std::string NextID() = 0;
  virtual void Save(const User&) = 0;
};
}  // namespace todo

#endif