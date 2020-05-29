cmake_minimum_required(VERSION 3.0.0)
project(GameCMake VERSION 0.1.0)

include(CTest)
enable_testing()

#good includes
include_directories(src/TextureLoader)

include_directories(src/Engine/Scene)
include_directories(src/Engine/GameObject)
include_directories(src/Engine/Window)
include_directories(src/Engine/ObjBehaviour)

include_directories(src/Chess)
include_directories(src/Chess/Desk)
include_directories(src/Chess/Desk/Cell)
include_directories(src/Chess/DeskController)

include_directories(src/Buttons/ChangeScene)
include_directories(src/Buttons/Exit)

include_directories(src/Audio)


include_directories(src/AssetPath)

#subdirectories
add_subdirectory(src)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(GameCMake main.cpp)
target_link_libraries(GameCMake sfml-graphics sfml-audio)

#libraries
target_link_libraries(GameCMake Window)
target_link_libraries(GameCMake Scene)

target_link_libraries(GameCMake Chess)
target_link_libraries(GameCMake Desk)
target_link_libraries(GameCMake DeskController)

target_link_libraries(GameCMake ExitButton)
target_link_libraries(GameCMake ChangeSceneButton)

target_link_libraries(GameCMake TextureLoader)
target_link_libraries(GameCMake Audio)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)