#include "rand.h"

#include <random>
#include <string>

namespace infra::rand {
const std::string letters =
    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

std::random_device seed;
std::seed_seq seeds = {seed(), seed()};
std::default_random_engine gen(seeds);

std::string Generate(int n) {
  std::uniform_int_distribution<int> range(0, letters.size() - 1);

  auto s = std::string(n, ' ');
  for (auto i = 0; i < s.size(); ++i) {
    s.at(i) = letters.at(range(gen));
  }

  return s;
}
}  // namespace infra::rand