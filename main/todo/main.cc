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

  auto user_repo = infra::file::UserRepo(workspace);
  const auto user_ren = presenter::text::UserRenderer();

  auto task_repo = infra::file::TaskRepo(workspace);
  const auto task_ren = presenter::text::TaskRenderer();

  auto app =
      controller::cli::App(session, user_repo, task_repo, user_ren, task_ren);
  app.Run(n, args);

  return EXIT_SUCCESS;
}