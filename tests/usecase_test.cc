#include "usecase/usecase.h"

#include <string>
#include <tuple>

#include "gtest/gtest.h"
#include "infra/memory.h"

TEST(CreateUser, Success) {
  auto repo = infra::memory::UserRepo();

  auto [email, password] =
      std::tuple{std::string("aiueo"), std::string("aiueo")};

  auto user = usecase::CreateUser(repo).Do(email, password);

  EXPECT_EQ(repo.Users().size(), 1);
  EXPECT_EQ(user.Email(), email);
  EXPECT_TRUE(user.Password().Compare(password));
}