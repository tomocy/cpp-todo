#ifndef TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H
#define TOMOCY_CPP_TODO_GATEWAY_PRESENTER_TEXT_H

#include <string>
#include <vector>

#include "gateway/controller/controller.h"
#include "todo.h"

namespace presenter::text {
class UserRenderer : public controller::UserRenderer {
 public:
  void Show(const todo::User&) const noexcept override;
  void ShowMessage(const std::string& msg) const noexcept override;
  void ShowErr(const std::string& msg) const noexcept override;
};
}  // namespace presenter::text

namespace presenter::text {
class TaskRenderer : public controller::TaskRenderer {
 public:
  void Show(const std::vector<todo::Task>& tasks) const noexcept override;
  void Show(const todo::Task&) const noexcept override;
  void ShowMessage(const std::string& msg) const noexcept override;
  void ShowErr(const std::string& msg) const noexcept override;
};
}  // namespace presenter::text

#endif