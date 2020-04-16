#include <gumo/application.h>
#include <gumo/renderer/renderer_2d.h>

vertex_array_t* vertex_array;
shader_t* shader;
texture_t* texture;

void initialize_application(application_t* application, char* title, int width, int height){
    application->window = create_window(title, width, height);
    initialize_window(application->window);
    application->target_frame_rate = 60;
    application->running = true;
    application->shading_mode = SHADED;

    glewInit();

    // Shader
    shader = malloc(sizeof(shader_t));
    create_shader_from_file(shader, "D:\\Projects\\gumo_engine\\resources\\shaders\\default_texture.glsl");

    // Vertex Array
    vertex_array = malloc(sizeof(vertex_array_t));
    create_vertex_array(vertex_array);

    // Vertex Buffer
    float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   6.0f, 4.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   6.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 4.0f  // top left
    };
    vertex_buffer_t* vertex_buffer = malloc(sizeof(vertex_buffer_t));
    create_vertex_buffer(vertices, sizeof(vertices), vertex_buffer);

    vertex_attribute_t vertex_attributes[] = {
            create_attribute_type("Position", FLOAT3, false),
            create_attribute_type("Colors", FLOAT3, false),
            create_attribute_type("TextureCords", FLOAT2, false)
    };
    set_vertex_attributes(vertex_buffer, vertex_attributes, sizeof vertex_attributes / sizeof *vertex_attributes);
    set_vertex_buffer(vertex_array, vertex_buffer);

    // Index Buffer
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };
    index_buffer_t* index_buffer = malloc(sizeof(index_buffer_t));
    create_index_buffer(indices, sizeof(indices), index_buffer);
    set_index_buffer(vertex_array, index_buffer);

    //Texture
    texture = malloc(sizeof(texture_t));
    create_texture_from_file(texture, "D:\\Projects\\gumo_engine\\resources\\textures\\wall.jpg");

    renderer_viewport(0, 0, width, height);
}

void run_application(application_t* application){
    //const float MAX_PERIOD = 1 / (float)application->target_frame_rate;

    float last_time = 0;
    float current_time = 0;
    float delta_time = 0;

    const color_t CLEAR_COLOR = {0.1f, 0.1f, 0.1f, 1.0f};

    while (application->running){
        if(glfwWindowShouldClose(application->window->window)){
            application->running = false;
            break;
        }

        //TIME LOOP
        {
            current_time = (float)glfwGetTime();
            delta_time = current_time - last_time;
            last_time = current_time;
        }

        //INPUT HANDLE
        {

        }

        on_update(delta_time);
        on_late_update();

        // RENDER
        {
            renderer_clear_color(CLEAR_COLOR);
            renderer_clear();

            bind_texture(texture, 0);
            submit(shader, vertex_array, application->shading_mode);
        }

        update_window(application->window);
    }

    glfwDestroyWindow(application->window->window);
    glfwTerminate();
}