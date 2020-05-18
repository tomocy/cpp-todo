#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CLI_H

#include <iostream>
#include <string>
#include <vector>

#include "gateway/controller/controller.h"

namespace controller::cli {
class App {
 public:
  App(const controller::Renderer&);

  void Run(int n, const char* const* args) const;

 private:
  void Parse(const std::vector<std::string>&) const;

  void CreateUser(const std::string& email, const std::string& password) const;

  void ShowHelp() const;

  const controller::Renderer& renderer;
};
}  // namespace controller::cli

#endif