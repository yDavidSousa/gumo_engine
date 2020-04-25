#ifndef GUMO_ENGINE_APPLICATION_H
#define GUMO_ENGINE_APPLICATION_H

#include "core.h"
#include "window.h"
#include "input.h"
#include <gumo/renderer/texture.h>
#include <gumo/renderer/shader.h>
#include <gumo/renderer/vertex_array.h>
#include <gumo/renderer/camera.h>

typedef struct application
{
    window_t* window;
    int target_frame_rate;
    int system_language;
    bool is_running;
    bool is_minimized;
    char* data_path;
    char* company_name;
    char* product_name;

    //scene
    camera_t camera;
} application_t;

//Temp
GUMO_API extern void on_update(float delta_time);
GUMO_API extern void on_late_update();
//

GUMO_API void initialize_application(application_t* application, const char* data_path, const char* title, int width, int height);
GUMO_API void run_application(application_t* application);
GUMO_API void end_application();

#endif //GUMO_ENGINE_APPLICATION_H