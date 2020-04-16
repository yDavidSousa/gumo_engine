#pragma once

#include <gumo/core.h>
#include <mathc.h>

typedef struct color{
    float r, g, b, a;
} color_t;

typedef struct shader{
    unsigned int id;
} shader_t;

GUMO_API void create_shader_from_file(shader_t* shader, const char* path);
GUMO_API void create_shader(const char* vertex_source, const char* fragment_source, shader_t* shader);
GUMO_API void delete_shader(shader_t* shader);
GUMO_API void bind_shader(shader_t* shader);

GUMO_API void shader_set_int(shader_t* shader, const char* name, int value);
GUMO_API void shader_set_int_array(shader_t* shader, const char* name, int* values, unsigned int length);
GUMO_API void shader_set_float(shader_t* shader, const char* name, float value);
GUMO_API void shader_set_float2(shader_t* shader, const char* name, struct vec2 value);
GUMO_API void shader_set_float3(shader_t* shader, const char* name, struct vec3 value);
GUMO_API void shader_set_float4(shader_t* shader, const char* name, struct vec4 value);
GUMO_API void shader_set_color(shader_t* shader, const char* name, color_t value);