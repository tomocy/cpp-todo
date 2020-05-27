#ifndef TOMOCY_CPP_TODO_TODO_H
#define TOMOCY_CPP_TODO_TODO_H

#include <string>
#include <tuple>

namespace todo {
class HashedString {
 public:
  explicit HashedString(const std::string& s) noexcept;

  const std::string& ToString() const noexcept;

 private:
  std::string s;
};
}  // namespace todo

namespace todo {
class Hash {
 public:
  Hash() = default;

  explicit Hash(const std::string& plain) noexcept;

  explicit Hash(const HashedString& hash) noexcept;

  bool Compare(const std::string& plain) const;

  std::string ToString() const noexcept;

 private:
  std::string hash;
};
}  // namespace todo

namespace todo {
class User {
 public:
  User() = default;

  User(const std::string& id, const std::string& email, const Hash& password);

  User(const std::string& id, const std::string& email,
       const std::string& password);

  const std::string& ID() const;

  const std::string& Email() const;

  const Hash& Password() const;

 private:
  void setID(const std::string& id);

  void setEmail(const std::string& email);

  void setPassword(const Hash& password);

  void setPassword(const std::string& password);

  std::string id;
  std::string email;
  Hash password;
};
}  // namespace todo

namespace todo {
class UserRepo {
 public:
  virtual ~UserRepo() {}
  virtual std::string NextID() const = 0;
  virtual std::tuple<User, bool> FindByEmail(
      const std::string& email) const = 0;
  virtual void Save(const User&) = 0;
};
}  // namespace todo

namespace todo {
class Task {
 public:
  Task() = default;

  Task(const std::string& id, const std::string& userID,
       const std::string& name);

  const std::string& ID() const;

  const std::string& UserID() const;

  const std::string& Name() const;

  bool IsCompleted() const;

  void Complete();

 private:
  void setID(const std::string& id);

  void setUserID(const std::string& userID);

  void setName(const std::string& name);

  std::string id;
  std::string userID;
  std::string name;
  bool completed;
};
}  // namespace todo

namespace todo {
class TaskRepo {
 public:
  virtual ~TaskRepo() {}
  virtual std::string NextID() const = 0;
  virtual std::vector<Task> Get(const std::string& userID) const = 0;
  virtual std::tuple<todo::Task, bool> FindOfUser(
      const std::string& id, const std::string& userID) const = 0;
  virtual void Save(const Task&) = 0;
  virtual void Delete(const Task&) = 0;
};
}  // namespace todo

namespace todo {
class Exception : public std::exception {
 public:
  explicit Exception(const std::string& msg) noexcept;

  const char* what() const noexcept;

 private:
  const std::string msg;
};
}  // namespace todo

#endif