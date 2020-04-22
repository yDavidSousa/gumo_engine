#include <gumo/renderer/buffer.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

// Vertex Buffer

static int get_attribute_bytes(attribute_type_t type)
{
    switch (type)
    {
        case ATTRIBUTE_FLOAT:  return 4;
        case ATTRIBUTE_VEC2:   return 4 * 2;
        case ATTRIBUTE_VEC3:   return 4 * 3;
        case ATTRIBUTE_VEC4:   return 4 * 4;
        case ATTRIBUTE_INT:    return 4;
        case ATTRIBUTE_VEC2I:  return 4 * 2;
        case ATTRIBUTE_VEC3I:  return 4 * 3;
        case ATTRIBUTE_VEC4I:  return 4 * 4;
        case ATTRIBUTE_MAT3:   return 4 * 3 * 3;
        case ATTRIBUTE_MAT4:   return 4 * 4 * 4;
        case ATTRIBUTE_BOOL:   return 1;
        default:               return 0;
    }
}

static unsigned int get_attribute_type(attribute_type_t type)
{
    switch (type)
    {
        case ATTRIBUTE_FLOAT:    return 0x1406;
        case ATTRIBUTE_VEC2:   return 0x1406;
        case ATTRIBUTE_VEC3:   return 0x1406;
        case ATTRIBUTE_VEC4:   return 0x1406;
        case ATTRIBUTE_MAT3:     return 0x1406;
        case ATTRIBUTE_MAT4:     return 0x1406;
        case ATTRIBUTE_INT:      return 0x1404;
        case ATTRIBUTE_VEC2I:     return 0x1404;
        case ATTRIBUTE_VEC3I:     return 0x1404;
        case ATTRIBUTE_VEC4I:     return 0x1404;
        case ATTRIBUTE_BOOL:     return 0x8B56;
        default:       return 0;
    }
}

static int get_attribute_size(attribute_type_t type)
{
    switch (type)
    {
        case ATTRIBUTE_FLOAT:    return 1;
        case ATTRIBUTE_VEC2:   return 2;
        case ATTRIBUTE_VEC3:   return 3;
        case ATTRIBUTE_VEC4:   return 4;
        case ATTRIBUTE_MAT3:     return 3 * 3;
        case ATTRIBUTE_MAT4:     return 4 * 4;
        case ATTRIBUTE_INT:      return 1;
        case ATTRIBUTE_VEC2I:     return 2;
        case ATTRIBUTE_VEC3I:     return 3;
        case ATTRIBUTE_VEC4I:     return 4;
        case ATTRIBUTE_BOOL:     return 1;
        default:       return 0;
    }
}

vertex_attribute_t create_vertex_attribute(char* name, attribute_type_t type, bool normalized){
    vertex_attribute_t vertex_attribute;
    vertex_attribute.name = name;
    vertex_attribute.size = get_attribute_size(type);
    vertex_attribute.type = get_attribute_type(type);
    vertex_attribute.bytes = get_attribute_bytes(type);
    vertex_attribute.normalized = normalized;
    return vertex_attribute;
}

void set_vertex_attributes(vertex_buffer_t* vertex_buffer, vertex_attribute_t* attributes, int length){

    vertex_buffer->vertex_attributes_array = MEM_ALLOC(vertex_attribute_t, length);
    vertex_buffer->vertex_attributes_length = length;

    int stride = 0;
    unsigned int offset = 0;
    for (unsigned int index = 0; index < length; ++index) {
        attributes[index].data_offset = offset;
        stride = stride + attributes[index].bytes;
        offset = offset + attributes[index].bytes;
        vertex_buffer->vertex_attributes_array[index] = attributes[index];
    }
    vertex_buffer->stride = stride;
}

void create_vertex_buffer(float* vertices, unsigned int size, vertex_buffer_t* vertex_buffer){
    glCreateBuffers(1, &vertex_buffer->unique_id); //Generate vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->unique_id); //Bind vertex buffer to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //Copies the defined vertex data into the buffer's memory
}

void delete_vertex_buffer(vertex_buffer_t* vertex_buffer)
{
    glDeleteBuffers(1, &vertex_buffer->unique_id);
}

inline void bind_vertex_buffer(vertex_buffer_t* vertex_buffer){
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->unique_id);
}

inline void unbind_vertex_buffer(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// Index Buffer

void create_index_buffer(unsigned int* indices, unsigned int size, index_buffer_t* index_buffer){
    glCreateBuffers(1, &index_buffer->unique_id);
    glBindBuffer(GL_ARRAY_BUFFER, index_buffer->unique_id);
    glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    index_buffer->size = size;
}

void delete_index_buffer(index_buffer_t* index_buffer)
{
    glDeleteBuffers(1, &index_buffer->unique_id);
}

inline void bind_index_buffer(index_buffer_t* index_buffer){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->unique_id);
}

inline void unbind_index_buffer(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}