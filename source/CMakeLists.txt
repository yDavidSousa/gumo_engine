list(APPEND GUMO_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/renderer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/shader.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/vertex_array.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/buffer.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/camera.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/texture.c
        ${CMAKE_CURRENT_SOURCE_DIR}/application.c
        ${CMAKE_CURRENT_SOURCE_DIR}/window.c
        ${CMAKE_CURRENT_SOURCE_DIR}/logger.c
        ${CMAKE_CURRENT_SOURCE_DIR}/math.c
        ${CMAKE_CURRENT_SOURCE_DIR}/input.c)

set(GUMO_SOURCE_FILES ${GUMO_SOURCE_FILES} PARENT_SCOPE)