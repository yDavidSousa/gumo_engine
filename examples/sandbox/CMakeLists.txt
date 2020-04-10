project(sandbox)

set(SOURCE_FILES main.c)

add_executable(sandbox ${SOURCE_FILES})
target_link_libraries(sandbox PRIVATE gumo_engine)

file(COPY ${DEPS_BINARIES_DIR}/ DESTINATION /)