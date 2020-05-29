#pragma once
#include <SFML/Graphics.hpp>

namespace Engine
{
    class ObjBehaviour
    {
    public:
        //call's every frame
        virtual void update() {}
        //call's on scene load
        virtual void start() {}
        virtual void onMouseDown(sf::Event) {}
        virtual void onMouseUp(sf::Event) {}
        virtual void onMouseMove(sf::Event) {}
    };
} // namespace Engine