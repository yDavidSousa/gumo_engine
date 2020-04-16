#include <gumo/renderer/renderer_2d.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

void renderer_initialize(){

}

inline void renderer_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height){
    glViewport(x, y, width, height);
}

inline void renderer_clear_color(color_t color){
    glClearColor(color.r, color.g, color.b, color.a);
}

inline void renderer_clear(){
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_indexed(vertex_array_t* vertex_array, unsigned int index_count){
    unsigned int count = vertex_array->index_buffer->size;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void submit(shader_t* shader, vertex_array_t* vertex_array, unsigned int shading_mode){
    switch (shading_mode){
        case SHADED:
            bind_shader(shader);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
    }

    bind_vertex_array(vertex_array);
    draw_indexed(vertex_array, 0);
}