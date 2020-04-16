#pragma once

#include <gumo/core.h>

enum attribute_type {
    NONE,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    MAT3,
    MAT4,
    INT,
    INT2,
    INT3,
    INT4,
    BOOL
};

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
    unsigned int stride;
    vertex_attribute_t* vertex_attributes_array;
    int vertex_attributes_length;
} vertex_buffer_t;

typedef struct index_buffer{
    unsigned int unique_id;
    unsigned int size;
} index_buffer_t;

GUMO_API vertex_attribute_t create_attribute_type(char* name, enum attribute_type type, bool normalized);
GUMO_API void set_vertex_attributes(vertex_buffer_t* vertex_buffer, vertex_attribute_t* attributes, int length);

GUMO_API void create_vertex_buffer(float* vertices, unsigned int size, vertex_buffer_t* vertex_buffer);
GUMO_API void bind_vertex_buffer(vertex_buffer_t* vertex_buffer);
GUMO_API void unbind_vertex_buffer();

GUMO_API void create_index_buffer(unsigned int* indices, unsigned int size, index_buffer_t* index_buffer);
GUMO_API void bind_index_buffer(index_buffer_t* index_buffer);
GUMO_API void unbind_index_buffer();