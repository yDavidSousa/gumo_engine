#include <gumo/window.h>

static bool GLFWInitialized = false;

static void error_callback(int error, const char* description)
{
    GM_LOG_CRITICAL("%s", description);
}

void initialize_window(window_t* window, char* title, int width, int height)
{
    if(GLFWInitialized == false)
    {
        bool success = glfwInit();
        
        GM_ASSERT(success, "Could not initialize GLFW!");

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        glfwSetErrorCallback(error_callback);
        GLFWInitialized = true;
    }

    window->window = glfwCreateWindow(width, height, title, NULL, NULL);
    GM_LOG_INFO("Creating window Gumo Engine (%d, %d)", width, height);

    window->title = title;
    window->width = width;
    window->height = height;

    if(window->window == NULL)
    {
        glfwTerminate();
    }

    glfwMakeContextCurrent(window->window);

    set_vsync_window(true);
}

void update_window(window_t* window)
{
    glfwPollEvents();
    glfwSwapBuffers(window->window);
}

void set_vsync_window(bool value)
{
    glfwSwapInterval(value);
}