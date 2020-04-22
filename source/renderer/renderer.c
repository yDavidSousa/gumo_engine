#include <gumo/renderer/renderer.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>

matrix4_t view_projection_matrix;

GUMO_API void initialize_renderer()
{
    glewInit();
    glEnable(GL_BLEND);

    // Vertex Array
    create_vertex_array(&renderer_storage.vertex_array);

    // Vertex Buffer
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
    };
    vertex_buffer_t* vertex_buffer = MEM_ALLOC(vertex_buffer_t, 1);
    create_vertex_buffer(vertices, sizeof(vertices), vertex_buffer);

    // Vertex Attributes
    vertex_attribute_t vertex_attributes[] = {
            create_vertex_attribute("a_Position", ATTRIBUTE_VEC3, false)
    };
    set_vertex_attributes(vertex_buffer, vertex_attributes, sizeof vertex_attributes / sizeof *vertex_attributes);
    set_vertex_buffer(&renderer_storage.vertex_array, vertex_buffer);

    // Index Buffer
    unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
    index_buffer_t* index_buffer = MEM_ALLOC(index_buffer_t, 1);
    create_index_buffer(indices, sizeof(indices), index_buffer);
    set_index_buffer(&renderer_storage.vertex_array, index_buffer);

    // Shader
    char* vertex_src = "D:\\Projects\\gumo_engine\\resources\\shaders\\flat_color.vert";
    char* fragment_src = "D:\\Projects\\gumo_engine\\resources\\shaders\\flat_color.frag";
    renderer_storage.flat_color_shader = *load_shader_from_file(vertex_src, fragment_src);
}

inline void renderer_viewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    glViewport(x, y, width, height);
}

inline void renderer_clear_color(color_t color)
{
    glClearColor(color.r, color.g, color.b, color.a);
}

inline void renderer_clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void draw_indexed(vertex_array_t* vertex_array, unsigned int index_count)
{
    unsigned int count = vertex_array->index_buffer->size;
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void begin_scene(camera_t* camera, blend_mode_t blend_mode, draw_mode_t draw_mode)
{
    switch (draw_mode){
        case DRAW_WIREFRAME: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
        case DRAW_SHADED: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
        default: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
    }

    switch(blend_mode)
    {
        case BLEND_ALPHA: glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); break;
        case BLEND_ADDITIVE: glBlendFunc(GL_SRC_ALPHA, GL_ONE); break;
        case BLEND_MULTIPLIED: glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA); break;
        default: break;
    }

    view_projection_matrix = camera->view_projection_matrix;
}

void end_scene()
{
}

void submit(shader_t* shader, vertex_array_t* vertex_array, matrix4_t transform)
{
    bind_shader(shader);
    shader_set_matrix4(shader, "u_ViewProjection", &view_projection_matrix);
    //shader_set_matrix4(shader, "u_Transform", &transform);

    bind_vertex_array(vertex_array);
    draw_indexed(vertex_array, 0);
}

void draw_mesh_color(vector2_t position, vector2_t size, color_t color)
{
    bind_shader(&renderer_storage.flat_color_shader);
    shader_set_matrix4(&renderer_storage.flat_color_shader, "u_ViewProjection", &view_projection_matrix);

    shader_set_color(&renderer_storage.flat_color_shader, "u_Color", color);

    matrix4_t mat_position = matrix4_translate(MATRIX4_IDENTITY, (vector3_t){position.x, position.y, 0.0f});
    matrix4_t mat_scale = matrix4_scale(MATRIX4_IDENTITY, (vector3_t){size.x, size.y, 1.0f});
    matrix4_t mat_rotation = matrix4_rotate(MATRIX4_IDENTITY, to_radians(0.0f), VECTOR3_FORWARD);
    matrix4_t transform = matrix4_multiply(matrix4_multiply(mat_position, mat_rotation), mat_scale);
    shader_set_matrix4(&renderer_storage.flat_color_shader, "u_Transform", &transform);

    bind_vertex_array(&renderer_storage.vertex_array);
    draw_indexed(&renderer_storage.vertex_array, 0);
}

void draw_mesh_texture(vector2_t position, vector2_t size, texture_t texture)
{

}