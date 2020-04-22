#pragma once

#include <gumo/renderer/buffer.h>

typedef struct vertex_array
{
    unsigned int unique_id;

    vertex_buffer_t* vertex_buffer; //TODO(David): Array
    unsigned int vertex_buffer_index;

    index_buffer_t* index_buffer;
} vertex_array_t;

GUMO_API void create_vertex_array(vertex_array_t* vertex_array);
GUMO_API void delete_vertex_array(vertex_array_t* vertex_array);
GUMO_API void bind_vertex_array(vertex_array_t* vertex_array);
GUMO_API void unbind_vertex_array();

GUMO_API void set_vertex_buffer(vertex_array_t* vertex_array, vertex_buffer_t* vertex_buffer);
GUMO_API void set_index_buffer(vertex_array_t* vertex_array, index_buffer_t* index_buffer);