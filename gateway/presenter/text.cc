#include "gateway/presenter/text.h"

#include <iostream>
#include <string>
#include <vector>

#include "todo.h"

namespace presenter::text {
void UserRenderer::Show(const todo::User& user) const noexcept {
  std::cout << "ID: " << user.ID() << std::endl;
  std::cout << "Email: " << user.Email() << std::endl;
}

void UserRenderer::ShowMessage(const std::string& msg) const noexcept {
  std::cout << msg << std::endl;
}

void UserRenderer::ShowErr(const std::string& msg) const noexcept {
  std::cerr << msg << std::endl;
}
}  // namespace presenter::text

namespace presenter::text {
void TaskRenderer::Show(const std::vector<todo::Task>& tasks) const noexcept {
  for (auto task : tasks) {
    std::cout << "-----" << std::endl;
    Show(task);
  }
}

void TaskRenderer::Show(const todo::Task& task) const noexcept {
  std::cout << "ID: " << task.ID() << std::endl;
  std::cout << "User ID: " << task.UserID() << std::endl;
  std::cout << "Name: " << task.Name() << std::endl;
  std::cout << "Status: "
            << (task.IsCompleted() ? "Completed" : "Not Completed")
            << std::endl;
}

void TaskRenderer::ShowMessage(const std::string& msg) const noexcept {
  std::cout << msg << std::endl;
}

void TaskRenderer::ShowErr(const std::string& msg) const noexcept {
  std::cerr << msg << std::endl;
}
}  // namespace presenter::text