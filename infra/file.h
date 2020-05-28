#ifndef TOMOCY_CPP_TODO_INFRA_FILE_H
#define TOMOCY_CPP_TODO_INFRA_FILE_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

#include "external/json/single_include/nlohmann/json.hpp"
#include "gateway/controller/cli.h"
#include "todo.h"

namespace infra::file {
struct User {
 public:
  User() = default;

  User(const todo::User& user) noexcept;

  todo::User ToUser() const noexcept;

  std::string id;
  std::string email;
  std::string password;
};

void to_json(nlohmann::json& json, const User& user);

void from_json(const nlohmann::json& json, User& user);
}  // namespace infra::file

namespace infra::file {
struct Store {
 public:
  Store() noexcept;

  Store(const std::map<std::string, std::string>& session,
        const std::map<std::string, User>& users) noexcept;

  std::map<std::string, std::string> session;

  std::map<std::string, User> users;
};

void to_json(nlohmann::json& json, const Store& store);

void from_json(const nlohmann::json& json, Store& store);
}  // namespace infra::file

namespace infra::file {
class File {
 public:
  explicit File(const std::string& workspace) noexcept;

  Store Load() const noexcept;

  void Save(const Store& store) const noexcept;

 private:
  void InitWorkspaceIfNotExist() const noexcept;

  bool DoesStoreFileExist() const noexcept;

  std::string StorePath() const noexcept;

  std::string workspace;
};
}  // namespace infra::file

namespace infra::file {
class Session : public controller::cli::Session {
 public:
  Session(const std::string& workspace) noexcept;

  void SetAuthenticatedUserID(const std::string& userID) noexcept override;

  std::tuple<std::string, bool> GetAuthenticatedUserID() const
      noexcept override;

 private:
  const std::string kAuthenticatedUserID = "authenticated_user_id";

  File file;
};
}  // namespace infra::file

namespace infra::file {
class UserRepo : public todo::UserRepo {
 public:
  explicit UserRepo(const std::string& workspace) noexcept;

  std::string NextID() const noexcept override;

  std::tuple<todo::User, bool> FindByEmail(const std::string& email) const
      noexcept override;

  void Save(const todo::User& user) noexcept override;

 private:
  File file;
};
}  // namespace infra::file

#endif