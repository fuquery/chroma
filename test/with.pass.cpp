// RUN: %compile

#include <chroma>

struct A {
  static constexpr auto error_message = "not in A";
};

struct B {
  static constexpr auto error_message = "not in B";
};

void fnc1(callable_from<A> = {}) {}
void fnc2(callable_from<B> = {}) {}

void test() {
  $with(A, B) {
    fnc1();
    fnc2();
  };
}