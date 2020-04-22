#ifndef GUMO_ENGINE_ENTRY_POINT_H
#define GUMO_ENGINE_ENTRY_POINT_H

#include "application.h"

#ifdef GM_PLATFORM_WINDOWS
int main(int argc, char **argv)
{
    char* title = "Sandbox";
    int width = 1280;
    int height = 720;

    application_t* application = MEM_ALLOC(application_t, 1);
    initialize_application(application, title, width, height);
    run_application(application);
    end_application();
    MEM_FREE(application);
}
#endif

#endif //GUMO_ENGINE_ENTRY_POINT_H