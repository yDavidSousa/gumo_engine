#pragma once

#include <gumo/core.h>
#include <gumo/renderer/graphics_context.h>

typedef struct window_data{
    char* title;
    int width, height;
} window_data_t;

typedef struct window {
    GLFWwindow* window;
    graphics_context_t* context;
    window_data_t data;
} window_t;

GUMO_API window_t* create_window(char* title, int width, int height);
GUMO_API void initialize_window(window_t* window);
GUMO_API void update_window(window_t* window);
GUMO_API void set_vsync_window(bool value);