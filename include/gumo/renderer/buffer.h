#pragma once

#include <gumo/core.h>

typedef enum
{
    NONE,
    ATTRIBUTE_FLOAT,
    ATTRIBUTE_VEC2,
    ATTRIBUTE_VEC3,
    ATTRIBUTE_VEC4,
    ATTRIBUTE_INT,
    ATTRIBUTE_VEC2I,
    ATTRIBUTE_VEC3I,
    ATTRIBUTE_VEC4I,
    ATTRIBUTE_MAT3,
    ATTRIBUTE_MAT4,
    ATTRIBUTE_BOOL
} attribute_type_t;

typedef struct vertex_attribute{
    char* name;
    int size;
    int bytes;
    unsigned int type;
    bool normalized;
    unsigned int data_offset;
} vertex_attribute_t;

typedef struct vertex_buffer{
    unsigned int unique_id;

    //layout
    unsigned int stride;
    vertex_attribute_t* vertex_attributes_array;
    int vertex_attributes_length;
} vertex_buffer_t;

typedef struct index_buffer{
    unsigned int unique_id;
    unsigned int size;
} index_buffer_t;

GUMO_API vertex_attribute_t create_vertex_attribute(char* name, attribute_type_t type, bool normalized);
GUMO_API void set_vertex_attributes(vertex_buffer_t* vertex_buffer, vertex_attribute_t* attributes, int length);

GUMO_API void create_vertex_buffer(float* vertices, unsigned int size, vertex_buffer_t* vertex_buffer);
GUMO_API void delete_vertex_buffer(vertex_buffer_t* vertex_buffer);
GUMO_API void bind_vertex_buffer(vertex_buffer_t* vertex_buffer);
GUMO_API void unbind_vertex_buffer();

GUMO_API void create_index_buffer(unsigned int* indices, unsigned int size, index_buffer_t* index_buffer);
GUMO_API void delete_index_buffer(index_buffer_t* index_buffer);
GUMO_API void bind_index_buffer(index_buffer_t* index_buffer);
GUMO_API void unbind_index_buffer();