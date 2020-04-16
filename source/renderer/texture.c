#include <gumo/renderer/texture.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void create_texture_from_file(texture_t* texture, const char* path){
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = NULL;
    data = stbi_load(path, &width, &height, &channels, 0);
    GM_ASSERT(data, "Failed to load image!");
    texture->width = width;
    texture->height = height;

    unsigned int internal_format = 0, data_format = 0;
    if(channels == 4){
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    }
    else if(channels == 3){
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }
    texture->internal_format = internal_format;
    texture->data_format = data_format;

    glCreateTextures(GL_TEXTURE_2D, 1, &texture->unique_id);
    glTextureStorage2D(texture->unique_id, 1, internal_format, width, height);

    //Filter Mode (Texture Filtering)
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Bilinear
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Point

    //Wrap Mode (Texture Wrapping) 1. Repeat 2.Mirror 3.Clamp-Edge 4.Clamp-Border
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(texture->unique_id, 0, 0, 0, width, height, data_format, GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
}

void create_texture(texture_t* texture, unsigned int width, unsigned int height){
    texture->internal_format = GL_RGBA8;
    texture->data_format = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &texture->unique_id);
    glTextureStorage2D(texture->unique_id, 1, texture->internal_format, width, height);

    glTextureParameteri(texture->unique_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(texture->unique_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void bind_texture(texture_t* texture, unsigned int slot){
    glBindTextureUnit(slot, texture->unique_id);
}

void delete_texture(texture_t* texture){
    glDeleteTextures(1, &texture->unique_id);
}

inline bool texture_compare(texture_t* text1, texture_t* text2){
    return text1->unique_id == text2->unique_id;
}