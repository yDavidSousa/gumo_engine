#pragma once

#ifdef GM_PLATFORM_WINDOWS

extern application_t* create_application();

int main(int argc, char **argv){
    application_t* application = create_application();
    initialize_application(application, "Sandbox", 640, 480);
    run_application(application);
    free(application);
}

#endif