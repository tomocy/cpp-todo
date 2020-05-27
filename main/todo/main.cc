#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"
#include "infra/file.h"
#include "infra/memory.h"

int main(int n, const char* const* const args) {
  auto authenticatedUserID = std::string("test_authenticated_user_1");

  auto session = infra::memory::Session();
  session.SetAuthenticatedUserID(authenticatedUserID);

  auto userRepo = infra::file::UserRepo(".");
  const auto userRen = presenter::text::UserRenderer();

  auto taskRepo = infra::memory::TaskRepo();
  for (auto i = 0; i < 10; ++i) {
    taskRepo.Save(todo::Task(std::to_string(i), authenticatedUserID,
                             "test task " + std::to_string(i)));
  }
  const auto taskRen = presenter::text::TaskRenderer();

  auto app =
      controller::cli::App(session, userRepo, taskRepo, userRen, taskRen);
  app.Run(n, args);

  return EXIT_SUCCESS;
}