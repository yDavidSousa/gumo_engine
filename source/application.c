#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <gumo/application.h>
#include <gumo/window.h>

void initialize_application(application_t* application, char* title, int width, int height){
    application->window = create_window(title, width, height);
    initialize_window(application->window);
    application->target_frame_rate = 60;
    application->running = true;

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
    unsigned int indices[3] = { 0, 1, 2 };

    glewInit();
    glGenVertexArrays(1, &application->vertex_array);
    glGenBuffers(1, &application->vertex_buffer);
    glGenBuffers(1, &application->index_buffer);

    glBindVertexArray(application->vertex_array);
    glBindBuffer(GL_ARRAY_BUFFER, application->vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, application->index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Vertex Array
    // Vertex Buffer
    // Index Buffer
    // Shader
}

void run_application(application_t* application){
    const float MAX_PERIOD = 1 / (float)application->target_frame_rate;

    float last_time = 0;
    float current_time = 0;
    float delta_time = 0;

    while (application->running){
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(application->vertex_array);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        update_window(application->window);

        if(glfwWindowShouldClose(application->window->window)){
            application->running = false;
        }

        //Time loop
        current_time = (float)glfwGetTime();
        delta_time = current_time - last_time;
        last_time = current_time;

        //process input

        if(delta_time >= MAX_PERIOD){
            last_time = current_time;
            //OnMainLoopBegin
            //OnEarlyUpdate
            on_update(delta_time);
            on_late_update();
            //OnPreRender
            //OnRender
            //OnPostRender
            //OnMainLoopEnd
        }

        //render
    }

    glfwDestroyWindow(application->window->window);
    glfwTerminate();
}