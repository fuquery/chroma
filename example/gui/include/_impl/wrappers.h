#pragma once
#include <chroma>

#define PRAGMA(x)          _Pragma(#x)
#define POISON(identifier) PRAGMA(GCC poison identifier)

#define UNWRAP_VARIADIC(...)           __VA_ARGS__
#define ADD_COLOR(color, ...) (__VA_ARGS__ __VA_OPT__(, ) callable_from<color> = {})
#define WRAP_FNC(prefix, name, rtype, args)                                                     \
  namespace prefix {                                                                            \
  rtype name ADD_COLOR(prefix::context, UNWRAP_VARIADIC args) {                                          \
    template for (auto _ : "") {                                                                \
      static constexpr auto _current_function = std::meta::access_context::current().scope();   \
      static constexpr auto [... _idx] = [:std::meta::reflect_constant_array(std::views::iota(  \
                                               0zu,                                             \
                                               parameters_of(_current_function).size() - 1)):]; \
      if constexpr (is_void_type(return_type_of(_current_function))) {                          \
        prefix##name([:parameters_of(_current_function)[_idx]:]...);                            \
      } else {                                                                                  \
        return prefix##name([:parameters_of(_current_function)[_idx]:]...);                     \
      }                                                                                         \
    }                                                                                           \
  }                                                                                             \
  }                                                                                             \
  POISON(prefix##name)
