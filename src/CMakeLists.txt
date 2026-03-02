add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${RAYLIB_DIR}/include
    ${ENET_DIR}/include
)
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib enet)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)