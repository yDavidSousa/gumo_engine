#include <gumo/renderer/buffer.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

// Vertex Buffer

static int get_attribute_bytes(enum attribute_type type)
{
    switch (type)
    {
        case FLOAT:    return 4;
        case FLOAT2:   return 4 * 2;
        case FLOAT3:   return 4 * 3;
        case FLOAT4:   return 4 * 4;
        case MAT3:     return 4 * 3 * 3;
        case MAT4:     return 4 * 4 * 4;
        case INT:      return 4;
        case INT2:     return 4 * 2;
        case INT3:     return 4 * 3;
        case INT4:     return 4 * 4;
        case BOOL:     return 1;
        default:       return 0;
    }
}

static unsigned int get_attribute_type(enum attribute_type type)
{
    switch (type)
    {
        case FLOAT:    return 0x1406;
        case FLOAT2:   return 0x1406;
        case FLOAT3:   return 0x1406;
        case FLOAT4:   return 0x1406;
        case MAT3:     return 0x1406;
        case MAT4:     return 0x1406;
        case INT:      return 0x1404;
        case INT2:     return 0x1404;
        case INT3:     return 0x1404;
        case INT4:     return 0x1404;
        case BOOL:     return 0x8B56;
        default:       return 0;
    }
}

static int get_attribute_size(enum attribute_type type)
{
    switch (type)
    {
        case FLOAT:    return 1;
        case FLOAT2:   return 2;
        case FLOAT3:   return 3;
        case FLOAT4:   return 4;
        case MAT3:     return 3 * 3;
        case MAT4:     return 4 * 4;
        case INT:      return 1;
        case INT2:     return 2;
        case INT3:     return 3;
        case INT4:     return 4;
        case BOOL:     return 1;
        default:       return 0;
    }
}

vertex_attribute_t create_attribute_type(char* name, enum attribute_type type, bool normalized){
    vertex_attribute_t vertex_attribute;
    vertex_attribute.name = name;
    vertex_attribute.size = get_attribute_size(type);
    vertex_attribute.type = get_attribute_type(type);
    vertex_attribute.bytes = get_attribute_bytes(type);
    vertex_attribute.normalized = normalized;
    return vertex_attribute;
}

void set_vertex_attributes(vertex_buffer_t* vertex_buffer, vertex_attribute_t* attributes, int length){
    int stride = 0;
    unsigned int offset = 0;
    for (unsigned int index = 0; index < length; ++index) {
        attributes[index].data_offset = offset;
        stride = stride + attributes[index].bytes;
        offset = offset + attributes[index].bytes;
    }
    vertex_buffer->stride = stride;
    vertex_buffer->vertex_attributes_array = attributes;
    vertex_buffer->vertex_attributes_length = length;
}

void create_vertex_buffer(float* vertices, unsigned int size, vertex_buffer_t* vertex_buffer){
    glCreateBuffers(1, &vertex_buffer->unique_id); //Generate vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer->unique_id); //Bind vertex buffer to GL_ARRAY_BUFFER
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW); //Copies the defined vertex data into the buffer's memory
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
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->unique_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    index_buffer->size = size;
}

inline void bind_index_buffer(index_buffer_t* index_buffer){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer->unique_id);
}

inline void unbind_index_buffer(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}