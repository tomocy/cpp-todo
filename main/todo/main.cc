#include <cstdlib>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"
#include "infra/memory.h"

int main(int n, const char* const* const args) {
  auto userRepo = infra::memory::UserRepo();
  const auto ren = presenter::text::Renderer();
  auto app = controller::cli::App(userRepo, ren);
  app.Run(n, args);

  return EXIT_SUCCESS;
}