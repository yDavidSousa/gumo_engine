#include <gumo/resource_manager.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define BUFFER_LENGTH 2048

static unsigned int string_hash(const char* string)
{
    unsigned int result = 5381;

    int index = 0;
    char current = string[index];

    while (current != '\0') {
        result = ((result << 5u) + result) + current;
        current = string[index++];
    }

    return result;
}

static unsigned int string_hashcode(const char* string)
{
    unsigned int result = 0;
    unsigned int length = strlen(string);

    int index = 0;
    while (string[index] != '\0') {
        result = result + string[index] +  (int)pow(31, (length - index + 1));
        index = index + 1;
    }

    return result;
}

static char* read_file_content(const char *file_path) {
    FILE* file = fopen(file_path, "r");
    GM_ASSERT(file != NULL, "Couldn't open shader file with path: %s", file_path);

    char* buffer = MEM_ALLOC(char, BUFFER_LENGTH);
    fscanf(file, "%[^\0]", buffer);
    fclose(file);

    return buffer;
}

shader_t* load_shader_from_file(const char* vert_path, const char* frag_path)
{
    shader_t* shader = MEM_ALLOC(shader_t, 1);

    char* vertex_source = read_file_content(vert_path);
    char* fragment_source = read_file_content(frag_path);

    compile_shader(vertex_source, fragment_source, shader);

    MEM_FREE(vertex_source);
    MEM_FREE(fragment_source);

    return shader;
}

texture_t* load_texture_from_file(const char* path)
{
    texture_t* texture = MEM_ALLOC(texture_t, 1);

    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
    GM_ASSERT(data, "Failed to load texture with path: %s", path);

    texture->width = width;
    texture->height = height;
    unsigned int internal_format = 0, data_format = 0;
    if(channels == 4)
    {
        internal_format = GL_RGBA8;
        data_format = GL_RGBA;
    }
    else if(channels == 3)
    {
        internal_format = GL_RGB8;
        data_format = GL_RGB;
    }
    texture->internal_format = internal_format;
    texture->data_format = data_format;

    generate_texture(texture, data);

    stbi_image_free(data);

    return texture;
}