#include "Scene.h"

namespace Engine
{
    std::vector<std::shared_ptr<IGameObject>> &Scene::getObjPool()
    {
        return m_objectPool;
    }

    void Scene::clear()
    {
        m_objectPool.clear();
    }

    void Scene::update()
    {
        for (int i = 0; i < m_objectPool.size(); ++i)
        {
            if (m_objectPool[i]->isActive() == false)
                continue;

            m_objectPool[i]->update();
        }
    }

    void Scene::start()
    {
        for (int i = 0; i < m_objectPool.size(); ++i)
        {
            m_objectPool[i]->start();
        }
    }

    void Scene::onMouseDown(sf::Event event)
    {
        for (int i = 0; i < m_objectPool.size(); ++i)
        {
            if (m_objectPool[i]->isActive() == false)
                continue;

            m_objectPool[i]->onMouseDown(event);
        }
    }

    void Scene::onMouseUp(sf::Event event)
    {
        for (int i = 0; i < m_objectPool.size(); ++i)
        {
            if (m_objectPool[i]->isActive() == false)
                continue;

            m_objectPool[i]->onMouseUp(event);
        }
    }

    void Scene::onMouseMove(sf::Event event)
    {
        for (int i = 0; i < m_objectPool.size(); ++i)
        {
            if (m_objectPool[i]->isActive() == false)
                continue;

            m_objectPool[i]->onMouseMove(event);
        }
    }

    void Scene::addObject(IGameObject *gameObject)
    {
        m_objectPool.push_back(std::shared_ptr<IGameObject>(gameObject));
    }
} // namespace Engine