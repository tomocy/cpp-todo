#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H

#include <string>

#include "todo.h"

namespace controller {
class Renderer {
 public:
  virtual ~Renderer() {}
  virtual void ShowErr(const std::string& msg) const = 0;
};
}  // namespace controller

namespace controller {
class UserRenderer : public Renderer {
 public:
  virtual ~UserRenderer() {}
  virtual void Show(const todo::User& user) const = 0;
};
}  // namespace controller

#endif
