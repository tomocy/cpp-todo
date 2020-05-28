#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"
#include "infra/file.h"

int main(int n, const char* const* const args) {
  auto workspace = std::string(".");

  auto session = infra::file::Session(workspace);

  auto userRepo = infra::file::UserRepo(workspace);
  const auto userRen = presenter::text::UserRenderer();

  auto taskRepo = infra::file::TaskRepo(workspace);
  const auto taskRen = presenter::text::TaskRenderer();

  auto app =
      controller::cli::App(session, userRepo, taskRepo, userRen, taskRen);
  app.Run(n, args);

  return EXIT_SUCCESS;
}