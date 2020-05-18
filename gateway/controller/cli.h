#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H

#include <iostream>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"

namespace controller::cli {
class Command {
 public:
  Command(const std::string& name, const std::vector<std::string>& args);

  const std::string& Name() const;

  const std::vector<std::string>& Args() const;

 private:
  std::string name;
  std::vector<std::string> args;
};
}  // namespace controller::cli

namespace controller::cli {
class Parser {
 public:
  Command Parse(const std::vector<std::string>& args);
};
}  // namespace controller::cli

namespace controller::cli {
class App {
 public:
  App(const controller::Renderer& ren);

  void Run(int n, const char* const* args) const;

 private:
  void ShowHelp() const;

  const controller::Renderer& renderer;
};
}  // namespace controller::cli

#endif