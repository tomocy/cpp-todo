#include <cstdlib>
#include <map>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"
#include "infra/memory.h"

int main(int n, const char* const* const args) {
  auto session = infra::memory::Session();
  session.SetAuthenticatedUserID("test authenticated user 1");

  auto userRepo = infra::memory::UserRepo(std::map<std::string, todo::User>{
      {"test user 1",
       todo::User("test user 1", "test_user_1@example.com", "test user 1")},
  });
  const auto userRen = presenter::text::UserRenderer();

  auto taskRepo = infra::memory::TaskRepo();
  const auto taskRen = presenter::text::TaskRenderer();

  auto app =
      controller::cli::App(session, userRepo, taskRepo, userRen, taskRen);
  app.Run(n, args);

  return EXIT_SUCCESS;
}