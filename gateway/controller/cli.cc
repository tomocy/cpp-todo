#include "gateway/controller/cli.h"

#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"

namespace controller::cli {
Command::Command(const std::string& name, const std::vector<std::string>& args)
    : name(name), args(args) {}

const std::string& Command::Name() const { return name; }

const std::vector<std::string>& Command::Args() const { return args; }
}  // namespace controller::cli

namespace controller::cli {
Command Parser::Parse(const std::vector<std::string>& args) {
  if (args.size() < 1) {
    return Command("", args);
  }

  return Command(args.at(0), std::vector<std::string>(std::begin(args) + 1,
                                                      std::end(args)));
}
}  // namespace controller::cli

namespace controller::cli {
App::App(const controller::Renderer& ren) : renderer(ren) {}

void App::Run(int n, const char* const* const args) const {
  auto converted = std::vector<std::string>(args + 1, args + n);
  Parser().Parse(converted);
}

void App::ShowHelp() const {
  std::cout << "todo" << std::endl;
  std::cout << "Usage:  [command] args..." << std::endl;
  std::cout << "Commands:" << std::endl;
}
}  // namespace controller::cli