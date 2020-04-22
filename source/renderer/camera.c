#include <gumo/renderer/camera.h>

void initialize_camera(camera_t* camera, float aspect_ratio, int type)
{
    camera->position = VECTOR3_ZERO;
    camera->rotation = 0.0f;

    camera->type = type;
    camera->aspect_ratio = aspect_ratio;
    if(camera->type == ORTHOGRAPHIC_CAMERA)
    {
        camera->size = 1.0f;
        camera->projection_matrix = matrix4_ortho(-aspect_ratio * camera->size, aspect_ratio * camera->size, -camera->size, camera->size, -1.0f, 1.0f);
    }
    else
    {
        camera->field_of_view = 60;
    }

    camera->view_matrix = MATRIX4_IDENTITY;
    camera->view_projection_matrix = matrix4_multiply(camera->projection_matrix, camera->view_matrix);
}

void camera_set_position(camera_t* camera, vector3_t position)
{
    camera->position = position;
    camera_recalculate_matrix(camera);
}

void camera_set_rotation(camera_t* camera, float rotation)
{
    camera->rotation = rotation;
    camera_recalculate_matrix(camera);
}

void camera_recalculate_matrix(camera_t* camera)
{
    matrix4_t position = matrix4_translate(MATRIX4_IDENTITY, camera->position);
    matrix4_t rotation = matrix4_rotate(MATRIX4_IDENTITY, to_radians(camera->rotation), VECTOR3_FORWARD);
    matrix4_t transform = matrix4_multiply(position, rotation);

    camera->view_matrix = matrix4_inverse(transform);
    camera->view_projection_matrix = matrix4_multiply(camera->projection_matrix, camera->view_matrix);
}

void camera_update(camera_t* camera, float delta_time)
{
    if (key_pressing(KEYCODE_D))
    {
        camera->position.x += COS(to_radians(camera->rotation)) * 2 * delta_time;
        camera->position.y += SIN(to_radians(camera->rotation)) * 2 * delta_time;
    }
    else if (key_pressing(KEYCODE_A))
    {
        camera->position.x -= COS(to_radians(camera->rotation)) * 2 * delta_time;
        camera->position.y -= SIN(to_radians(camera->rotation)) * 2 * delta_time;
    }

    if(key_pressing(KEYCODE_W))
    {
        camera->position.x += -SIN(to_radians(camera->rotation)) * 2 * delta_time;
        camera->position.y += COS(to_radians(camera->rotation)) * 2 * delta_time;
    }
    else if(key_pressing(KEYCODE_S))
    {
        camera->position.x -= -SIN(to_radians(camera->rotation)) * 2 * delta_time;
        camera->position.y -= COS(to_radians(camera->rotation)) * 2 * delta_time;
    }

    if(key_pressing(KEYCODE_Q))
    {
        camera->size -= 1.0f * delta_time;
        camera->projection_matrix = matrix4_ortho(-camera->aspect_ratio * camera->size, camera->aspect_ratio * camera->size, -camera->size, camera->size, -1.0f, 1.0f);
        camera->view_projection_matrix = matrix4_multiply(camera->projection_matrix, camera->view_matrix);
    }
    else if(key_pressing(KEYCODE_E))
    {
        camera->size += 1.0f * delta_time;
        camera->projection_matrix = matrix4_ortho(-camera->aspect_ratio * camera->size, camera->aspect_ratio * camera->size, -camera->size, camera->size, -1.0f, 1.0f);
        camera->view_projection_matrix = matrix4_multiply(camera->projection_matrix, camera->view_matrix);
    }

    camera_set_position(camera, camera->position);
}