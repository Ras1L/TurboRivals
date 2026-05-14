set (MY_SOURCES 
    main.cpp
    App/Application.cpp
    App/GameScene.cpp
    App/MenuScene.cpp
    App/SceneManager.cpp
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
    Network/ENet.cpp
    Network/NetworkManager.cpp
    Network/Client.cpp
    Network/Server.cpp
)

file(GLOB IMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../external/imgui-1.92.7/*cpp")
file (GLOB RLIMGUI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/../external/rlImGui-Raylib_5_5/*cpp")

add_executable(${PROJECT_NAME} 
    ${MY_SOURCES}
    ${IMGUI_SOURCES}
    ${RLIMGUI_SOURCES}
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
)
target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Wno-missing-field-initializers
)