#ifndef TOMOCY_CPP_TODO_TODO_H
#define TOMOCY_CPP_TODO_TODO_H

#include <string>

namespace todo {
class User {
 public:
  User() = default;

  User(const std::string& id, const std::string& email);

  const std::string& ID() const;

  const std::string& Email() const;

 private:
  std::string id;
  std::string email;
};
}  // namespace todo

#endif