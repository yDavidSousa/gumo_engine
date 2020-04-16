#include <../../gumo.h>
#include <math.h>
#include <string.h>

unsigned int string_hash(const char* string);
unsigned int string_hashcode(const char* string);

application_t* create_application(){
    application_t* application = malloc(sizeof *application);
    //printf("button hash: %u\n", string_hashcode("button"));
    //printf("checkbox hash: %u\n", string_hashcode("checkbox"));
    //printf("button hash: %u\n", string_hashcode("button"));
    //printf("checkbox hash: %u\n", string_hashcode("checkbox"));
    //printf("button hash: %u\n", string_hashcode("button"));
    //printf("checkbox hash: %u\n", string_hashcode("checkbox"));
    return application;
}

void on_update(float delta_time){
    //GM_LOG_INFO("deltaTime: %f", delta_time);
}

void on_late_update(){
    //GM_LOG_INFO("lateupdate");
}

unsigned int string_hash(const char* string)
{
    unsigned int result = 5381;

    int index = 0;
    char current = string[index];

    while (current != '\0') {
        result = ((result << 5u) + result) + current;
        current = string[index++];
    }

    return result;
}

unsigned int string_hashcode(const char* string)
{
    unsigned int result = 0;
    unsigned int length = strlen(string);

    int index = 0;
    while (string[index] != '\0') {
        result = result + string[index] +  (int)pow(31, (length - index + 1));
        index = index + 1;
    }

    return result;
}