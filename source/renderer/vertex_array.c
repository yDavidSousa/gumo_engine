#include <gumo/renderer/vertex_array.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

inline void create_vertex_array(vertex_array_t* vertex_array)
{
    glCreateVertexArrays(1, &vertex_array->unique_id);
}

inline void delete_vertex_array(vertex_array_t* vertex_array){
    glDeleteVertexArrays(1, &vertex_array->unique_id);
}

inline void bind_vertex_array(vertex_array_t* vertex_array)
{
    glBindVertexArray(vertex_array->unique_id);
}

inline void unbind_vertex_array()
{
    glBindVertexArray(0);
}

void set_vertex_buffer(vertex_array_t* vertex_array, vertex_buffer_t* vertex_buffer)
{
    GM_ASSERT(vertex_buffer->vertex_attributes_length, "Vertex buffer has no attribute!");

    glBindVertexArray(vertex_array->unique_id);
    bind_vertex_buffer(vertex_buffer);

    for (unsigned int index = 0; index < vertex_buffer->vertex_attributes_length; ++index)
    {
        vertex_attribute_t attribute = vertex_buffer->vertex_attributes_array[index];

        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index, attribute.size, attribute.type, attribute.normalized,
                              vertex_buffer->stride, (const void *) attribute.data_offset);
    }

    vertex_array->vertex_buffer = vertex_buffer;
}

void set_index_buffer(vertex_array_t* vertex_array, index_buffer_t* index_buffer)
{
    glBindVertexArray(vertex_array->unique_id);
    bind_index_buffer(index_buffer);
    vertex_array->index_buffer = index_buffer;
}