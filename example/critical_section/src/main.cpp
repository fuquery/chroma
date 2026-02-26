#include <chroma>
#include <lock.hpp>

void still_in_critical_section(callable_from<locked_context> = {}) {
  // ...
}

void must_be_locked(callable_from<locked_context> = {}) {
  // call can be implicit, lock is still held
  still_in_critical_section();
}

int main() {
  std::mutex mtx;
  {
    locked_context lock(mtx); // acquire lock

    // get color for the acquired lock
    must_be_locked(lock.context());
  }
}