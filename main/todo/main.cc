#include <cstdlib>

#include "gateway/controller/cli.h"
#include "gateway/presenter/text.h"

int main(int n, const char* const* const args) {
  const auto ren = presenter::text::Renderer();
  auto app = controller::cli::App(ren);
  app.Run(n, args);

  return EXIT_SUCCESS;
}