#include <chroma>
#include <ui.h>
void display(callable_from<ui::context> = {}) {
    gl::ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    gl::Clear(GL_COLOR_BUFFER_BIT);

    gl::Begin(GL_TRIANGLES);
        gl::Vertex2f(-0.5f, -0.5f);
        gl::Vertex2f( 0.5f, -0.5f);
        gl::Vertex2f( 0.0f,  0.5f);
    gl::End();

    glut::SwapBuffers();
}

int main(int argc, char** argv) {
    $with(ui::context) {
        ui::init(argc, argv);
        ui::create_window("foo", {400, 300});
        ui::loop(func<display>);
    };
}