add_library(
    TextureLoader
    TextureLoader/TextureLoader.h
    TextureLoader/TextureLoader.cpp
)

add_library(
    Window
    Engine/Window/Window.h
    Engine/Window/Window.cpp
)

add_library(
    Scene
    Engine/Scene/Scene.h
    Engine/Scene/Scene.cpp
)

add_library(
    Audio
    Audio/Audio.h
    Audio/Audio.cpp
)

add_library(
    Chess
    Chess/Chess.h
    Chess/Chess.cpp
)


add_library(
    Desk
    Chess/Desk/Desk.h
    Chess/Desk/Desk.cpp
)

add_library(
    ChangeSceneButton
    Buttons/ChangeScene/ChangeSceneButton.h
    Buttons/ChangeScene/ChangeSceneButton.cpp
)

add_library(
    ExitButton
    Buttons/Exit/ExitButton.h
    Buttons/Exit/ExitButton.cpp
)

add_library(
    DeskController
    Chess/DeskController/DeskController.h
    Chess/DeskController/DeskController.cpp
)