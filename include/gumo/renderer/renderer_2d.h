#pragma once

#include <gumo/renderer/shader.h>
#include <gumo/renderer/vertex_array.h>

enum shading_mode{
    SHADED,
    WIREFRAME,
    SHADED_WIREFRAME
};

GUMO_API void renderer_initialize();
GUMO_API void renderer_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);
GUMO_API void renderer_clear_color(color_t color);
GUMO_API void renderer_clear();

GUMO_API void draw_indexed(vertex_array_t* vertex_array, unsigned int index_count);
GUMO_API void submit(shader_t* shader, vertex_array_t* vertex_array, unsigned int shading_mode);