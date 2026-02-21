// RUN: %verify

#include <chroma>

struct A {
  static constexpr auto error_message = "not in A";
};

struct B {
  static constexpr auto error_message = "not in B";
};

void fnc(callable_from<A> = {}) {}
void other_fnc(callable_from<B> = {}) {
  // STATIC_ASSERT: not in A
  fnc();
}

void test() {
  // STATIC_ASSERT: not in B
  other_fnc();
}