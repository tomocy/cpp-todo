#ifndef TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H
#define TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H

#include "todo.h"

namespace presenter::text {
class Renderer {
 public:
  void ShowUser(const todo::User&) const;
};
}  // namespace presenter::text

#endif