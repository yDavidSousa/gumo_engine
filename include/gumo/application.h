#pragma once

#include <glfw/glfw3.h>
#include <gumo/core.h>
#include "window.h"

typedef struct application{
    window_t* window;
    int target_frame_rate;
    bool running;
    unsigned int vertex_array;
    unsigned int vertex_buffer;
    unsigned int index_buffer;
} application_t;

extern void on_update(float delta_time);
extern void on_late_update();

GUMO_API void initialize_application(application_t* application, char* title, int width, int height);
GUMO_API void run_application(application_t* application);