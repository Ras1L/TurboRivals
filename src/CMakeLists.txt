add_executable(${PROJECT_NAME} 
    main.cpp
    App/Application.cpp
    Core/Physics.cpp
    Core/GameWorld.cpp
    Core/VehiclePhysicsComponent.cpp
    Core/TrackCollisionComponent.cpp
    Render/CarCamera.cpp
    Render/RenderSystem.cpp
    Render/ResourceManager.cpp
    UI/Window.cpp
    UI/InputManager.cpp
    Sound/SoundManager.cpp
    Network/NetworkManager.cpp
    Network/Client.cpp
    Network/Server.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${INCLUDE_DIR}
    ${RAYLIB_DIR}/include
    ${ENET_DIR}/include
    ${BULLET_DIR}/src
    ${IMGUI_DIR}
    ${RLIMGUI_DIR}
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    enet
    BulletDynamics
    BulletCollision
    LinearMath
    rlImGui
)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Wno-missing-field-initializers
)