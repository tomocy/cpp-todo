#include "usecase/usecase.h"

#include <string>
#include <tuple>

#include "gtest/gtest.h"
#include "infra/memory.h"

TEST(CreateUser, Success) {
  auto repo = infra::memory::UserRepo();

  auto [email, password] =
      std::tuple{std::string("test email"), std::string("test password")};

  auto user = usecase::CreateUser(repo).Do(email, password);

  EXPECT_EQ(repo.Users().size(), 1);
  EXPECT_EQ(user.Email(), email);
  EXPECT_TRUE(user.Password().Compare(password));
}

TEST(AuthenticateUser, Success) {
  auto repo = infra::memory::UserRepo();

  auto [email, password] =
      std::tuple{std::string("test email"), std::string("test password")};

  auto created = usecase::CreateUser(repo).Do(email, password);

  auto [user, authenticated] =
      usecase::AuthenticateUser(repo).Do(email, password);

  EXPECT_TRUE(authenticated);
  EXPECT_EQ(user.ID(), created.ID());
  EXPECT_EQ(user.Email(), created.Email());
}

TEST(GetTasks, Success) {
  auto repo = infra::memory::TaskRepo();

  auto userID = "test user id";

  auto task = usecase::CreateTask(repo).Do(userID, "test name");

  auto tasks = usecase::GetTasks(repo).Do(userID);

  EXPECT_EQ(tasks.size(), 1);
  EXPECT_EQ(tasks.at(0).UserID(), userID);
}

TEST(CreateTask, Success) {
  auto repo = infra::memory::TaskRepo();

  auto [userID, name] =
      std::tuple{std::string("test user id"), std::string("test name")};

  auto task = usecase::CreateTask(repo).Do(userID, name);

  EXPECT_FALSE(task.ID().empty());
  EXPECT_EQ(task.UserID(), userID);
  EXPECT_EQ(task.Name(), name);
  EXPECT_FALSE(task.IsCompleted());
}

TEST(CompleteTask, Success) {
  auto repo = infra::memory::TaskRepo();

  auto created = usecase::CreateTask(repo).Do("test user id", "test name");

  auto task = usecase::CompleteTask(repo).Do(created.ID(), created.UserID());

  EXPECT_TRUE(task.IsCompleted());
}

TEST(DeleteTask, Success) {
  auto repo = infra::memory::TaskRepo();

  auto task = usecase::CreateTask(repo).Do("test user id", "test name");

  usecase::DeleteTask(repo).Do(task.ID(), task.UserID());

  EXPECT_EQ(repo.Tasks().size(), 0);
}