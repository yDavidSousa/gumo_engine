#ifndef GUMO_ENGINE_RENDERER_H
#define GUMO_ENGINE_RENDERER_H

#include <gumo/renderer/shader.h>
#include <gumo/renderer/vertex_array.h>
#include <gumo/renderer/camera.h>
#include <gumo/resource_manager.h>
#include "texture.h"

typedef enum
{
    BLEND_ALPHA,
    BLEND_ADDITIVE,
    BLEND_MULTIPLIED,
} blend_mode_t;

typedef enum
{
    DRAW_SHADED,
    DRAW_WIREFRAME,
    DRAW_SHADED_WIREFRAME
} draw_mode_t;

typedef struct renderer_storage
{
    vertex_array_t vertex_array;
    shader_t flat_color_shader;
} renderer_storage_t;

renderer_storage_t renderer_storage;

GUMO_API void initialize_renderer(const char* data_path);
GUMO_API void renderer_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
GUMO_API void renderer_clear_color(color_t color);
GUMO_API void renderer_clear();

GUMO_API void begin_scene(camera_t* camera, blend_mode_t blend_mode, draw_mode_t draw_mode);
GUMO_API void end_scene();

GUMO_API void draw_indexed(vertex_array_t* vertex_array, unsigned int index_count);
GUMO_API void submit(shader_t* shader, vertex_array_t* vertex_array, matrix4_t transform);

GUMO_API void draw_mesh_color(vector2_t position, vector2_t size, color_t color);
GUMO_API void draw_mesh_texture(vector2_t position, vector2_t size, texture_t texture);

#endif //GUMO_ENGINE_RENDERER_H