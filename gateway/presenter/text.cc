#include "gateway/presenter/text.h"

#include <iostream>
#include <string>

#include "todo.h"

namespace presenter::text {
void UserRenderer::Show(const todo::User& user) const {
  std::cout << "ID: " << user.ID() << std::endl;
  std::cout << "Email: " << user.Email() << std::endl;
}

void UserRenderer::ShowErr(const std::string& msg) const {
  std::cerr << msg << std::endl;
}
}  // namespace presenter::text