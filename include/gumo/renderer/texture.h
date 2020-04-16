#pragma once

#include <gumo/core.h>

typedef struct texture{
    unsigned int unique_id;
    unsigned int width, height, channels;
    unsigned int internal_format, data_format;
} texture_t;

GUMO_API void create_texture_from_file(texture_t* texture, const char* path);
GUMO_API void create_texture(texture_t* texture, unsigned int width, unsigned int height);
GUMO_API void bind_texture(texture_t* texture, unsigned int slot);
GUMO_API void delete_texture(texture_t* texture);
GUMO_API bool texture_compare(texture_t* text1, texture_t* text2);