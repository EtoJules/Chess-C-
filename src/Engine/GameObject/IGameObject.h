#pragma once
#include <SFML/Graphics.hpp>
#include "ObjBehaviour.h"

namespace Engine
{
    class IGameObject : public sf::Drawable, public sf::Transformable, public ObjBehaviour
    {
    private:
        bool m_isActive;

    public:
        bool isActive() { return m_isActive; }
        void setActive(bool isActive) { m_isActive = isActive; }

    public:
        //call's every frame
        virtual void update() {}
        //call's on scene load
        virtual void start() {}
        virtual void onMouseDown(sf::Event) {}
        virtual void onMouseUp(sf::Event) {}
        virtual void onMouseMove(sf::Event) {}

    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {}

    public:
        IGameObject() : m_isActive(true) {}
    };
} // namespace Engine