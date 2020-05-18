#include "gateway/presenter/text.h"

#include <iostream>

#include "todo.h"

namespace presenter::text {
void Renderer::ShowUser(const todo::User& user) const {
  std::cout << "ID: " << user.ID() << std::endl;
  std::cout << "Email: " << user.Email() << std::endl;
}
}  // namespace presenter::text