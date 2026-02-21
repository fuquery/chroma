// RUN: %verify

#include <chroma>

struct A {
  static constexpr auto error_message = "not in A";
};

struct B : A {
  static constexpr auto error_message = "not in B";
};

void fnc1(callable_from<B> = {}) {}

void fnc2(callable_from<A> = {}) {
  // STATIC_ASSERT: not in B
  fnc1();
}

void fnc3(callable_from<B> = {}) {
  fnc2();
}
