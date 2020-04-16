#pragma once

#include <gumo/core.h>
#include <gumo/renderer/texture.h>
#include <gumo/renderer/shader.h>
#include <gumo/renderer/vertex_array.h>
#include <gumo/window.h>

typedef struct application{
    window_t* window;
    int target_frame_rate;
    bool running;
    bool minimized;
    int shading_mode;
} application_t;

extern void on_update(float delta_time);
extern void on_late_update();

GUMO_API void initialize_application(application_t* application, char* title, int width, int height);
GUMO_API void run_application(application_t* application);