#pragma once
#include <string>
#include <chroma>

#include "glut.h"
#include "gl.h"

template <auto V>
struct constant {
  constexpr static auto value = V;
};

template <auto V>
constexpr auto func = constant<V>();

namespace ui {
struct context
    : gl::context
    , glut::context {
  static constexpr auto error_message = "not in ui context";
};

struct Dimensions {
  int width;
  int height;
};

inline void init(int argc, char** argv, callable_from<ui::context> = {}) {
  glut::Init(&argc, argv);
}

inline void create_window(std::string const& name,
                          Dimensions dimensions,
                          callable_from<ui::context> = {}) {
  glut::InitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glut::InitWindowSize(dimensions.width, dimensions.height);
  glut::CreateWindow(name.c_str());
}

namespace _impl {
template <auto F>
auto* unchecked_callback(constant<F> fnc) {
  return +[][[= unchecked]] { F(unchecked); };
}
}  // namespace _impl

template <auto F>
void loop(constant<F> fnc, callable_from<ui::context> = {}) {
  // wrap fnc - the caller of the callback won't be in correct context
  glut::DisplayFunc(ui::_impl::unchecked_callback(fnc));
  glut::MainLoop();
}
}  // namespace ui
