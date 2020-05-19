#include "gateway/presenter/text.h"

#include <iostream>
#include <string>

#include "todo.h"

namespace presenter::text {
void Renderer::ShowUser(const todo::User& user) const {
  std::cout << "ID: " << user.ID() << std::endl;
  std::cout << "Email: " << user.Email() << std::endl;
}

void Renderer::ShowErr(const std::string& msg) const {
  std::cerr << msg << std::endl;
}
}  // namespace presenter::text