#include <cstdlib>
#include <map>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"
#include "infra/memory.h"

int main(int n, const char* const* const args) {
  auto userRepo = infra::memory::UserRepo(std::map<std::string, todo::User>{
      {"test user 1",
       todo::User("test user 1", "test_user_1@example.com", "test user 1")},
  });
  const auto ren = presenter::text::UserRenderer();
  auto app = controller::cli::App(userRepo, ren);
  app.Run(n, args);

  return EXIT_SUCCESS;
}