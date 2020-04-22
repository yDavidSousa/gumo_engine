#ifndef GUMO_ENGINE_CAMERA_H
#define GUMO_ENGINE_CAMERA_H

#include <gumo/core.h>
#include <gumo/math.h>
#include <gumo/input.h>

#define ORTHOGRAPHIC_CAMERA 0
#define PERSPECTIVE_CAMERA 1

typedef struct camera
{
    matrix4_t projection_matrix;
    matrix4_t view_matrix;
    matrix4_t view_projection_matrix;

    vector3_t position;
    float rotation;

    int type;
    float aspect_ratio;
    float size, field_of_view;
} camera_t;

GUMO_API void initialize_camera(camera_t* camera, float aspect_ratio, int type);
GUMO_API void camera_set_position(camera_t* camera, vector3_t position);
GUMO_API void camera_set_rotation(camera_t* camera, float rotation);
GUMO_API void camera_update(camera_t* camera, float delta_time);

GUMO_API void camera_recalculate_matrix(camera_t* camera);

#endif //GUMO_ENGINE_CAMERA_H