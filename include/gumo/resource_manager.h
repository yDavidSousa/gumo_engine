#ifndef GUMO_ENGINE_RESOURCE_MANAGER_H
#define GUMO_ENGINE_RESOURCE_MANAGER_H

#include "core.h"
#include <gumo/renderer/texture.h>
#include <gumo/renderer/shader.h>

GUMO_API shader_t* load_shader_from_file(const char* vert_path, const char* frag_path);
GUMO_API texture_t* load_texture_from_file(const char* path);

#endif //GUMO_ENGINE_RESOURCE_MANAGER_H