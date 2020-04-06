list(APPEND GUMO_SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/graphics_context.c
        ${CMAKE_CURRENT_SOURCE_DIR}/renderer/renderer_2d.c
        ${CMAKE_CURRENT_SOURCE_DIR}/application.c
        ${CMAKE_CURRENT_SOURCE_DIR}/window.c)

set(GUMO_SOURCE_FILES ${GUMO_SOURCE_FILES} PARENT_SCOPE)