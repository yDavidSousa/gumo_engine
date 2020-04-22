#ifndef GUMO_ENGINE_TEXTURE_H
#define GUMO_ENGINE_TEXTURE_H

#include <gumo/core.h>

typedef enum
{
    FILTER_POINT,
    FILTER_BILINEAR,
} filter_mode_t;

typedef struct texture
{
    unsigned int unique_id;
    unsigned int width, height, channels;
    unsigned int internal_format, data_format;
} texture_t;

GUMO_API void generate_texture(texture_t* texture, unsigned char* data);
GUMO_API void create_texture(texture_t* texture, unsigned int width, unsigned int height);
GUMO_API void bind_texture(texture_t* texture, unsigned int slot);
GUMO_API void delete_texture(texture_t* texture);
GUMO_API bool texture_compare(texture_t* t0, texture_t* t1);

#endif //GUMO_ENGINE_TEXTURE_H