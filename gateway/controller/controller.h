#ifndef TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H
#define TOMOCY_CPP_TODO_GATEWAY_CONTROLLER_CONTROLLER_H

#include <string>
#include <vector>

#include "todo.h"

namespace controller {
class Renderer {
 public:
  virtual ~Renderer() {}
  virtual void ShowMessage(const std::string& msg) const noexcept = 0;
  virtual void ShowErr(const std::string& msg) const noexcept = 0;
};
}  // namespace controller

namespace controller {
class UserRenderer : public Renderer {
 public:
  virtual ~UserRenderer() {}
  virtual void Show(const todo::User& user) const noexcept = 0;
};
}  // namespace controller

namespace controller {
class TaskRenderer : public Renderer {
 public:
  virtual ~TaskRenderer() {}
  virtual void Show(const std::vector<todo::Task>& tasks) const noexcept = 0;
  virtual void Show(const todo::Task& task) const noexcept = 0;
};
}  // namespace controller

#endif
