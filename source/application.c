#include <gumo/input.h>
#include <gumo/application.h>
#include <gumo/renderer/renderer.h>
#include <gumo/resource_manager.h>

vertex_array_t* vertex_array;
shader_t* shader;
texture_t* texture;

void initialize_application(application_t* application, char* title, int width, int height)
{
    application->window = MEM_ALLOC(window_t, 1);
    application->target_frame_rate = 60;
    application->is_running = true;

    initialize_window(application->window, title, width, height);
    float aspect_ratio = (float)width / (float)height;
    initialize_camera(&application->camera, aspect_ratio, ORTHOGRAPHIC_CAMERA);
    initialize_input(application->window);
    initialize_renderer();

    // Shader
    char* vertex_src = "D:\\Projects\\gumo_engine\\resources\\shaders\\default_texture.vert";
    char* fragment_src = "D:\\Projects\\gumo_engine\\resources\\shaders\\default_texture.frag";
    shader = load_shader_from_file(vertex_src, fragment_src);

    // Vertex Array
    vertex_array = MEM_ALLOC(vertex_array_t, 1);
    create_vertex_array(vertex_array);

    // Vertex Buffer
    float vertices[3 * 3 * 2 * 4] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left
    };
    vertex_buffer_t* vertex_buffer = MEM_ALLOC(vertex_buffer_t, 1);
    create_vertex_buffer(vertices, sizeof(vertices), vertex_buffer);

    vertex_attribute_t vertex_attributes[] = {
            create_vertex_attribute("Position", ATTRIBUTE_VEC3, false),
            create_vertex_attribute("Colors", ATTRIBUTE_VEC3, false),
            create_vertex_attribute("TextureCords", ATTRIBUTE_VEC2, false)
    };
    set_vertex_attributes(vertex_buffer, vertex_attributes, sizeof vertex_attributes / sizeof *vertex_attributes);
    set_vertex_buffer(vertex_array, vertex_buffer);

    // Index Buffer
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };
    index_buffer_t* index_buffer = MEM_ALLOC(index_buffer_t, 1);
    create_index_buffer(indices, sizeof(indices), index_buffer);
    set_index_buffer(vertex_array, index_buffer);

    //Texture
    texture = load_texture_from_file("D:\\Projects\\gumo_engine\\resources\\textures\\luppi.png");

    bind_texture(texture, 0);
    shader_set_int(shader, "u_Texture", 0);
}

void run_application(application_t* application)
{
    float last_time = 0;
    float current_time = 0;
    float delta_time = 0;

    const color_t CLEAR_COLOR = {0.1f, 0.1f, 0.1f, 1.0f};

    while (application->is_running)
    {
        if(glfwWindowShouldClose(application->window->window))
        {
            application->is_running = false;
            break;
        }

        //TIME LOOP
        current_time = (float)glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;

        //INPUT HANDLE
        update_keyboard();

        //on_update(delta_time);
        //on_late_update();

        camera_update(&application->camera, delta_time);

        // RENDER
        renderer_clear_color(CLEAR_COLOR);
        renderer_clear();

        begin_scene(&application->camera, BLEND_ALPHA, DRAW_SHADED);
        {
            draw_mesh_color((vector2_t){-1.0f, 0.0f}, VECTOR2_ONE, COLOR_RED);

            bind_texture(texture, 0);
            submit(shader, vertex_array, matrix4_translate(MATRIX4_IDENTITY, (vector3_t){-1.0f, 0.0f}));
        }
        end_scene();

        update_window(application->window);
    }

    glfwDestroyWindow(application->window->window);
    glfwTerminate();
}

void end_application()
{
    MEM_FREE(vertex_array);
    MEM_FREE(shader);
    MEM_FREE(texture);
}