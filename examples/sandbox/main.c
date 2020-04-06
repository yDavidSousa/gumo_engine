#include <stdio.h>
#include <../../gumo.h>

application_t* create_application(){
    application_t* application = malloc(sizeof *application);
    return application;
}

void on_update(float delta_time){
    printf("on_update: %f\n", delta_time);
}

void on_late_update(){
    printf("on_late_update\n");
}