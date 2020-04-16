list(APPEND GUMO_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/graphics_context.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/renderer_2d.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shader.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/vertex_array.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/buffer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/orthographic_camera.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/texture.c
        ${CMAKE_CURRENT_SOURCE_DIR}/application.c
        ${CMAKE_CURRENT_SOURCE_DIR}/window.c
        ${CMAKE_CURRENT_SOURCE_DIR}/logger.c)

set(GUMO_SOURCE_FILES ${GUMO_SOURCE_FILES} PARENT_SCOPE)