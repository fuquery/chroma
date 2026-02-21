#pragma once
#include <print>
#include <type_traits>
#include <cstdio>
#include <chroma>

struct io_context {
  static constexpr auto error_message = "need io context";
};

inline int safe_puts(const char* str, callable_from<io_context> = {}) {
  return std::puts(str);
}

namespace _io_impl {
template <typename... Ts>
struct format_string {
  std::basic_format_string<char, Ts...> fmt;

  template <typename U>
    requires std::convertible_to<U const&, std::string_view>
  consteval format_string(U const& fmt, callable_from<io_context> = {}) : fmt(fmt) {}
  operator std::basic_format_string<char, Ts...>() const { return fmt; }
};
}  // namespace _io_impl

template <typename... Ts>
void safe_print(_io_impl::format_string<std::type_identity_t<Ts>...> fmt, Ts&&... args) {
  std::println(fmt, std::forward<Ts>(args)...);
}

// poison all identifiers related to standard library functions that perform IO
#pragma GCC poison fgetc getc fgets fputc putc getchar putchar puts
#pragma GCC poison scanf fscanf sscanf vscanf vfscanf vsscanf printf
#pragma GCC poison fprintf sprintf snprintf vprintf vfprintf vsprintf vsnprintf
#pragma GCC poison cout cin clog cerr

#ifndef POISON_PRINT
#  define POISON_PRINT 1
#endif

#if POISON_PRINT
#  pragma GCC poison print println
#endif
