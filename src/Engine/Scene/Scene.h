#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "IGameObject.h"
#include <vector>
#include <memory>

namespace Engine
{
    class Scene : public ObjBehaviour
    {
    private:
        std::vector<std::shared_ptr<IGameObject>> m_objectPool;

    public:
        std::vector<std::shared_ptr<IGameObject>> &getObjPool();

    public:
        void clear();

    public:
        void update();
        void start();
        void onMouseDown(sf::Event);
        void onMouseUp(sf::Event);
        void onMouseMove(sf::Event);

    public:
        void addObject(IGameObject *);
    };
} // namespace Engine