#pragma once
#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include "Scene.h"

namespace Engine
{
    class Window
    {
    private:
        Scene m_currentScene;
        bool m_isSceneChanged;
        sf::RenderWindow m_win;

    public:
        void startGameLoop();

    public:
        void switchScene(Scene &currentScene);
        void close();

    public:
        Window(const Window&) = delete;

        static Window& get()
        {
            return m_instance;
        }

    private:
        Window();
        static Window m_instance;
    };
} // namespace Engine