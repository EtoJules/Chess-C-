#pragma once

#include "TextureLoader.h"
#include "IGameObject.h"
#include "Window.h"
#include "Scene.h"
#include <string>

#include "AssetPath.h"

class ChangeSceneButton : public Engine::IGameObject
{
private:
    sf::RectangleShape m_buttonBackground;
    sf::Text m_TextButton;
    sf::Font m_font;
    sf::Color m_defaultColor;
    sf::Color m_hoverColor;

private:
    std::string m_buttonName;
    int m_buttonSize;

private:
    sf::Vector2f m_mousePosition;
    Engine::Scene m_changeToScene;
    bool m_isMouseOnButton;

public:
    void setChangeToScene(Engine::Scene &);

public:
    void start();
    void onMouseMove(sf::Event);
    void onMouseUp(sf::Event);

public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    ChangeSceneButton(std::string = "Default", int = 50);
};
