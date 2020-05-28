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
  auto workspace = std::string(".");

  auto session = infra::file::Session(workspace);

  auto userRepo = infra::file::UserRepo(workspace);
  const auto userRen = presenter::text::UserRenderer();

  auto taskRepo = infra::memory::TaskRepo();
  for (auto i = 0; i < 10; ++i) {
    taskRepo.Save(todo::Task(std::to_string(i), "aiueo",
                             "test task " + std::to_string(i)));
  }
  const auto taskRen = presenter::text::TaskRenderer();

  auto app =
      controller::cli::App(session, userRepo, taskRepo, userRen, taskRen);
  app.Run(n, args);

  return EXIT_SUCCESS;
}