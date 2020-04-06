#include <stdio.h>
#include <stdlib.h>
#include <glfw/glfw3.h>
#include <gumo/window.h>

static bool GLFWInitialized = false;

static void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
}

static void close_callback(GLFWwindow* window){
}

window_t* create_window(char* title, int width, int height){
    window_t* window = malloc(sizeof *window);
    window->data.title = title;
    window->data.width = width;
    window->data.height = height;
    return window;
}

void initialize_window(window_t* window){

    if(GLFWInitialized == false){
        bool success = glfwInit();
        //ASSERT

        glfwSetErrorCallback(error_callback);
        GLFWInitialized = true;
    }

    window->window = glfwCreateWindow(window->data.width, window->data.height, window->data.title, NULL, NULL);
    if(window->window == NULL){
        glfwTerminate();
    }

    window->context = create_context(window->window);

    glfwSetKeyCallback(window->window, key_callback);
    glfwSetWindowCloseCallback(window->window, close_callback);

    set_vsync_window(true);
}

void update_window(window_t* window){
    glfwPollEvents();
    swap_buffers(window->context);
}

void set_vsync_window(bool value){
    glfwSwapInterval(value);
}