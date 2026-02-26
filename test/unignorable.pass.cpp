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
  auto b = B(123);
  fnc2(b);
}