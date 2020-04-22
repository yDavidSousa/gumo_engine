#ifndef GUMO_ENGINE_SHADER_H
#define GUMO_ENGINE_SHADER_H

#include <gumo/core.h>
#include <mathc.h>
#include <gumo/math.h>

typedef struct color
{
    float r, g, b, a;
} color_t;

GUMO_API const color_t COLOR_BLUE;
GUMO_API const color_t COLOR_RED;
GUMO_API const color_t COLOR_GREEN;
GUMO_API const color_t COLOR_WHITE;
GUMO_API const color_t COLOR_BLACK;

typedef struct shader
{
    unsigned int id;
} shader_t;

GUMO_API void compile_shader(const char* vertex_source, const char* fragment_source, shader_t* shader);
GUMO_API void delete_shader(shader_t* shader);
GUMO_API void bind_shader(shader_t* shader);

GUMO_API void shader_set_int(shader_t* shader, const char* name, int value);
GUMO_API void shader_set_int_array(shader_t* shader, const char* name, int* values, unsigned int length);
GUMO_API void shader_set_float(shader_t* shader, const char* name, float value);
GUMO_API void shader_set_float2(shader_t* shader, const char* name, struct vec2 value);
GUMO_API void shader_set_float3(shader_t* shader, const char* name, struct vec3 value);
GUMO_API void shader_set_float4(shader_t* shader, const char* name, struct vec4 value);
GUMO_API void shader_set_color(shader_t* shader, const char* name, color_t value);

GUMO_API void shader_set_matrix4(shader_t* shader, const char* name, const matrix4_t* matrix4);

#endif //GUMO_ENGINE_SHADER_H