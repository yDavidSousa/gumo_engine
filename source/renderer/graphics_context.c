#include <gumo/renderer/graphics_context.h>

graphics_context_t* create_context(GLFWwindow* window){
    graphics_context_t* graphics_context = malloc(sizeof *graphics_context);
    graphics_context->window_handle = window;
    glfwMakeContextCurrent(graphics_context->window_handle);
    return graphics_context;
}

void swap_buffers(graphics_context_t* context){
    //glBegin(GL_TRIANGLES);
    //glEnd();
    glfwSwapBuffers(context->window_handle);
}