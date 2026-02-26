// RUN: %verify

#include <chroma>

struct B {
  static constexpr auto error_message = "not in B";

  B() = delete;
  explicit B(int) {}
  operator callable_from<B>() const {
    return chroma::color<B>();
  }
};

void fnc2(callable_from<B> = {}) {}

void test2() {
  // ERROR_HERE: {{.*}}unchecked access to unignorable color
  fnc2(unchecked);
}