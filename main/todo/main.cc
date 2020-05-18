#include <cstdlib>

#include "gateway/controller/cli.h"

int main(int n, const char* const* const args) {
  auto app = controller::cli::App();
  app.Run(n, args);

  return EXIT_SUCCESS;
}