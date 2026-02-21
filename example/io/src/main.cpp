#include "safe_io.hpp"
#include <chroma>

void io_func(callable_from<io_context> = {}) {
  safe_puts("foo");
  safe_print("foo {} bar", 42);
}

int main() {
  //puts("foo"); //error: attempt to use a poisoned identifier
  $unchecked {
    io_func();
  };
}