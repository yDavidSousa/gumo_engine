#include <../../gumo.h>

application_t* create_application(){
    application_t* application = malloc(sizeof *application);
    return application;
}

void on_update(float delta_time){
    //GM_LOG_INFO("deltaTime: %f", delta_time);
}

void on_late_update(){
    //GM_LOG_INFO("lateupdate");
}