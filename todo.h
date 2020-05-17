#ifndef TOMOCY_CPP_TODO_TODO_H
#define TOMOCY_CPP_TODO_TODO_H

#include <string>

namespace todo {
class User {
 public:
  User() = default;

  explicit User(const std::string& id);

  const std::string& ID() const;

 private:
  std::string id;
};
}  // namespace todo

#endif