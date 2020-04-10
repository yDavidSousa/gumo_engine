#pragma once

#include <gumo/core.h>
#include <glfw/glfw3.h>

typedef struct graphics_context{
    GLFWwindow* window_handle;
} graphics_context_t;

GUMO_API graphics_context_t* create_context(GLFWwindow* window);
GUMO_API void swap_buffers(graphics_context_t* context);