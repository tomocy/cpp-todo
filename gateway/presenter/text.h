#ifndef TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H
#define TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H

#include "gateway/controller/controller.h"
#include "todo.h"

namespace presenter::text {
class Renderer : public controller::Renderer {
 public:
  void ShowUser(const todo::User&) const override;
};
}  // namespace presenter::text

#endif