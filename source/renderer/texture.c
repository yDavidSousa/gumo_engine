#include <gumo/renderer/texture.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

void generate_texture(texture_t* texture, unsigned char* data)
{
    glCreateTextures(GL_TEXTURE_2D, 1, &texture->unique_id);
    glTextureStorage2D(texture->unique_id, 1, texture->internal_format, texture->width, texture->height);

    //Filter Mode (Texture Filtering)
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Bilinear
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Point

    //Wrap Mode (Texture Wrapping) 1. Repeat 2.Mirror 3.Clamp-Edge 4.Clamp-Border
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(texture->unique_id, 0, 0, 0, texture->width, texture->height, texture->data_format, GL_UNSIGNED_BYTE, data);
}

void create_texture(texture_t* texture, unsigned int width, unsigned int height)
{
    texture->internal_format = GL_RGBA8;
    texture->data_format = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &texture->unique_id);
    glTextureStorage2D(texture->unique_id, 1, texture->internal_format, width, height);

    glTextureParameteri(texture->unique_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

inline void bind_texture(texture_t* texture, unsigned int slot)
{
    glBindTextureUnit(slot, texture->unique_id);
}

inline void delete_texture(texture_t* texture)
{
    glDeleteTextures(1, &texture->unique_id);
}

inline bool texture_compare(texture_t* t0, texture_t* t1)
{
    return t0->unique_id == t1->unique_id;
}