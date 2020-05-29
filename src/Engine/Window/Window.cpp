#include "Window.h"

namespace Engine
{
    Window::Window() : m_win(sf::VideoMode(1280, 720), "Chess", sf::Style::Default), m_currentScene(), m_isSceneChanged(true)
    {
        m_win.setFramerateLimit(120);
        //m_win.setMouseCursorGrabbed(true);
    }

    void Window::switchScene(Scene &newScene)
    {
        m_currentScene.clear();
        m_currentScene = newScene;
        m_isSceneChanged = true;
    }

    void Window::close()
    {
        m_win.close();
    }

    void Window::startGameLoop()
    {
        sf::Event mainEvent;

        while (m_win.isOpen())
        {

            if (m_isSceneChanged == true)
            {
                m_currentScene.start();
                m_isSceneChanged = false;
            }

            while (m_win.pollEvent(mainEvent))
            {
                if (mainEvent.type == sf::Event::Closed)
                {
                    m_win.close();
                }

                if (mainEvent.type == sf::Event::MouseButtonPressed)
                {
                    m_currentScene.onMouseDown(mainEvent);
                }

                if (mainEvent.type == sf::Event::MouseButtonReleased)
                {
                    m_currentScene.onMouseUp(mainEvent);
                }

                if (mainEvent.type == sf::Event::MouseMoved)
                {
                    m_currentScene.onMouseMove(mainEvent);
                }

                if (mainEvent.type == sf::Event::Resized)
                {
                    sf::FloatRect visibleArea(0, 0, mainEvent.size.width, mainEvent.size.height);
                    m_win.setView(sf::View(visibleArea));
                }
            }
            m_currentScene.update();

            m_win.clear(sf::Color(42, 75, 124));
            for (int i = 0; i < m_currentScene.getObjPool().size(); ++i)
            {
                m_win.draw(*m_currentScene.getObjPool()[i]);
            }
            m_win.display();
        }
    }

    Window Window::m_instance;
} // namespace Engine