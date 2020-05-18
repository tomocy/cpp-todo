#include "gateway/controller/cli.h"

#include <iostream>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"

namespace controller::cli {
App::App(const controller::Renderer& ren) : renderer(ren) {}

void App::Run(int n, const char* const* const args) const {
  auto converted = std::vector<std::string>(args, args + n);
  Parse(converted);
}

void App::Parse(const std::vector<std::string>& args) const { ShowHelp(); }

void App::ShowHelp() const {
  std::cout << "todo" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
}
}  // namespace controller::cli