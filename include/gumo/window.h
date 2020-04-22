#ifndef GUMO_ENGINE_WINDOW_H
#define GUMO_ENGINE_WINDOW_H

#include "core.h"
#include <gl/glew.h>
#include <glfw/glfw3.h>

typedef struct window
{
    char* title;
    int width, height;
    GLFWwindow* window;
} window_t;

GUMO_API void initialize_window(window_t* window, char* title, int width, int height);
GUMO_API void update_window(window_t* window);

GUMO_API void set_vsync_window(bool value);

#endif //GUMO_ENGINE_WINDOW_H