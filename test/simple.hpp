#pragma once
#include <chroma>

struct red {
  static constexpr auto error_message = "not a red function";
};

inline void a(callable_from<red> = {}) {}
inline void b(callable_from<red> = {}) { a(); }
