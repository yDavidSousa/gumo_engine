#include <glfw/glfw3.h>
#include <gumo/application.h>
#include <gumo/window.h>

void initialize_application(application_t* application, char* title, int width, int height){
    application->window = create_window(title, width, height);
    initialize_window(application->window);
    application->target_frame_rate = 60;
    application->running = true;
}

void run_application(application_t* application){
    const float MAX_PERIOD = 1 / (float)application->target_frame_rate;

    float last_time = 0;
    float current_time = 0;
    float delta_time = 0;

    while (application->running){
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

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