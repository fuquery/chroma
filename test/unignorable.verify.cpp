// RUN: %verify

#include <chroma>

struct A {
  static constexpr auto error_message = "not in A";
  static constexpr auto ignorable     = false;
};

void fnc1(callable_from<A> = {}) {}

void test() {
  // ERROR_HERE: {{.*}}unchecked access to unignorable color
  fnc1(unchecked);
}