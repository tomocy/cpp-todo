#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H

#include <iostream>
#include <string>
#include <vector>

namespace controller::cli {
class App {
 public:
  App();

  void Run(int n, const char* const* args) const;

 private:
  void Parse(const std::vector<std::string>&) const;

  void ShowHelp() const;
};
}  // namespace controller::cli

#endif