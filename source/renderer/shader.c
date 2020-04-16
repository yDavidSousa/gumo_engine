#include <gumo/renderer/shader.h>
#include <gumo/logger.h>
#include <gl/glew.h>
#include <glfw/glfw3.h>
#include <stdio.h>

#define BUFFER_LENGTH 2048

void create_shader_from_file(shader_t* shader, const char* path){
    FILE* file = fopen(path, "r");
    GM_ASSERT(file != NULL, "Couldn't open shader file!");

    char vertex_source[BUFFER_LENGTH];
    memset(vertex_source, 0, BUFFER_LENGTH * sizeof(char));

    char fragment_source[BUFFER_LENGTH];
    memset(fragment_source, 0, BUFFER_LENGTH * sizeof(char));

    char buffer[BUFFER_LENGTH];
    while(!feof(file)){
        fscanf(file, "%s", buffer);

        if(strcmp(buffer, "#type") == 0){
            fscanf(file, "%s", buffer);
            if(strcmp(buffer, "vertex") == 0){
                fseek(file, 0, SEEK_CUR);
                int file_start = ftell(file);
                int file_end = file_start;

                while(!feof(file)){
                    fscanf(file, "%s", buffer);
                    int current = ftell(file);
                    if(strcmp(buffer, "#type") == 0){
                        file_end = file_end - 11;
                        break;
                    } else {
                        file_end = current;
                    }
                }

                fseek(file, file_start, SEEK_SET);
                fread(vertex_source, sizeof(char), (file_end - file_start) + 1, file);
            }

            if(strcmp(buffer, "fragment") == 0){
                fseek(file, 0, SEEK_CUR);
                int file_start = ftell(file);
                int file_end = file_start;

                while(!feof(file)){
                    fscanf(file, "%s", buffer);
                    int current = ftell(file);
                    if(strcmp(buffer, "#type") == 0){
                        file_end = file_end - 11;
                        break;
                    } else {
                        file_end = current;
                    }
                }

                fseek(file, file_start, SEEK_SET);
                fread(fragment_source, sizeof(char), (file_end - file_start) + 1, file);
            }
        }
    }

    create_shader(vertex_source, fragment_source, shader);

    fclose(file);
}

void create_shader(const char* vertex_source, const char* fragment_source, shader_t* shader){
    // Create an empty vertex shader handle
    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);

    // Compile the vertex shader
    glCompileShader(vertex_shader);

    int success = 0;
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if(success == false)
    {
        //int max_length = 512;
        //glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &max_length);

        // The maxLength includes the NULL character
        char info_log[512];
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);

        // We don't need the shader anymore.
        glDeleteShader(vertex_shader);

        // Use the infoLog as you see fit.
        GM_LOG_ERROR("Vertex shader compilation failure!");
        GM_LOG_ERROR(info_log);

        // In this simple program, we'll just leave
        return;
    }

    // Create an empty fragment shader handle
    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);

    // Compile the fragment shader
    glCompileShader(fragment_shader);

    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (success == false)
    {
        // The max_length includes the NULL character
        char info_log[512];
        glGetShaderInfoLog(fragment_shader, 512, NULL, &info_log[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragment_shader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertex_shader);

        // Use the infoLog as you see fit.
        GM_LOG_ERROR("Fragment shader compilation failure!");
        GM_LOG_ERROR(info_log);

        // In this simple program, we'll just leave
        return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    unsigned int program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == false)
    {
        // The maxLength includes the NULL character
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, &info_log[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        // Use the infoLog as you see fit.
        GM_LOG_ERROR("Shader link failure!");
        GM_LOG_ERROR(info_log);

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    shader->id = program;
    //shader->vertex = vertex_shader;
    //shader->fragment = fragment_shader;
}

inline void delete_shader(shader_t* shader){
    glDeleteProgram(shader->id);
}

inline void bind_shader(shader_t* shader){
    glUseProgram(shader->id);
}

void shader_set_int(shader_t* shader, const char* name, int value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform1i(location, value);
}

void shader_set_int_array(shader_t* shader, const char* name, int* values, unsigned int length){
    int location = glGetUniformLocation(shader->id, name);
    glUniform1iv(location, length, values);
}

void shader_set_float(shader_t* shader, const char* name, float value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform1f(location, value);
}

void shader_set_float2(shader_t* shader, const char* name, struct vec2 value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform2f(location, value.x, value.y);
}

void shader_set_float3(shader_t* shader, const char* name, struct vec3 value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform3f(location, value.x, value.y, value.z);
}

void shader_set_float4(shader_t* shader, const char* name, struct vec4 value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void shader_set_color(shader_t* shader, const char* name, color_t value){
    int location = glGetUniformLocation(shader->id, name);
    glUniform4f(location, value.r, value.g, value.b, value.a);
}