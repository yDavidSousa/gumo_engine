#ifndef GUMO_ENGINE_ENTRY_POINT_H
#define GUMO_ENGINE_ENTRY_POINT_H

#include "application.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#ifdef GM_PLATFORM_WINDOWS
int main(int argc, char **argv)
{
    char path_save[1280];
    char abs_exe_path[1280];
    char *p;

    if(!(p = strrchr(argv[0], '\\')))
        getcwd(abs_exe_path, sizeof(abs_exe_path));
    else
    {
        *p = '\0';
        getcwd(path_save, sizeof(path_save));
        chdir(argv[0]);
        getcwd(abs_exe_path, sizeof(abs_exe_path));
        chdir(path_save);
    }

    char* title = "Sandbox";
    int width = 1280;
    int height = 720;

    application_t* application = MEM_ALLOC(application_t, 1);
    initialize_application(application, abs_exe_path, title, width, height);
    run_application(application);
    end_application();
    MEM_FREE(application);
}
#endif

#endif //GUMO_ENGINE_ENTRY_POINT_H