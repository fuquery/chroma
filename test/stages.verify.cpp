// RUN: %verify

#include <chroma>

struct Phase1 {
  static constexpr auto error_message = "not in phase 1";
  operator struct Phase2() const;
};

struct Phase2 {
  static constexpr auto error_message = "not in phase 2";
  operator struct Phase3() const;
};

struct Phase3 {
  static constexpr auto error_message = "not in phase 3";
};

void phase1_fnc(callable_from<Phase1> = {}) {}
void phase2_fnc(callable_from<Phase2> = {}) {}
void phase3_fnc(callable_from<Phase3> = {}) {}

void enter_phase3(callable_from<Phase3> = {}) {
  phase3_fnc();
}

void do_init(callable_from<Phase1> = {});
void enter_phase2(callable_from<Phase2> = {}) {
  phase2_fnc();
  enter_phase3();

  // STATIC_ASSERT: not in phase 1
  do_init();
}

void do_init(callable_from<Phase1>) {
  phase1_fnc();
  enter_phase2();

  // STATIC_ASSERT: not in phase 3
  enter_phase3();
}

int main(){
    $with(Phase1) {
      do_init();
    };
}
