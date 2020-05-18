#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H

#include "todo.h"

namespace controller {
class Renderer {
 public:
  virtual ~Renderer() {}
  virtual void ShowUser(const todo::User&) const = 0;
};
}  // namespace controller

#endif
