// RUN: %compile

#include <chroma>

struct A {
  static constexpr auto error_message = "not in A";
  static constexpr auto ignorable     = false;

  chroma::color<A> make_context() & { return {}; }
};

void fnc1(callable_from<A> = {}) {}

void test() {
  auto a = A();
  fnc1(a.make_context());
}