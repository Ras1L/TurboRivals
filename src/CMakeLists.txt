add_executable(${PROJECT_NAME} 
    main.cpp
    Core/Physics.cpp
    App/Application.cpp
    Render/CarCamera.cpp
    Render/Level.cpp
    UI/Window.cpp
    UI/InputManager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
    ${RAYLIB_DIR}/include
    ${ENET_DIR}/include
)
target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib enet)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Wno-missing-field-initializers
)