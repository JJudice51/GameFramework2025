#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

void Actor::start()
{
    m_started = true;
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->start();
    }
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->onCollision(other);
    }
}

/// <summary>
/// pass a name of the component you want then if you find that name it returns said component to you
/// </summary>
/// <param name="componentName"></param>
/// <returns></returns>
Component* Actor::getComponent(const char* componentName)
{
    if (!componentName)
        return nullptr;

    for (int i =0; i < m_componentCount; i++)
    {
        if (m_components[i]->getName() == componentName)
            return m_components[i];
    }
    return nullptr;
}


/// <summary>
/// 
/// </summary>
/// <param name="component"></param>
/// <returns></returns>
Component* Actor::addComponent(Component* component)
{
    Actor* owner = component->getOwner();
    
    if (owner /* != nullptr*/ &&owner != this) //if an owner exists and its not this instance of an actor return a nullpointer;
    {
        return nullptr;
    }

    Component** temp = new Component * [m_componentCount + 1];

    for (int i = 0; i < m_componentCount; i++)
    {
        temp[i] = m_components[i];
    }

    delete[] m_components;

    temp[m_componentCount] = component;

    m_components = temp;

    m_componentCount++;

    return component;
}


/// <summary>
/// 
/// </summary>
/// <param name="componentName"></param>
/// <returns></returns>
bool Actor::removeComponent(const char* componentName)
{  
    if (!componentName)
        return false;
    
    bool componentRemoved = false;

    Component** temp = new Component * [m_componentCount - 1];

    int j = 0;

    for (int i = 0; i < m_componentCount; i++)
    {
        //if this component is the one we want to remove.
        if (componentName == m_components[i]->getName())
        {
            //and go to the next iteration of the loop.
            componentRemoved = true;
            continue;
        }
        //otherwise, copy the component to the new array.
        temp[j] = m_components[i];
        j++;
    }
    if (componentRemoved)  
    {
        delete[] m_components;
        m_components = temp;
        m_componentCount--;
    }
    return componentRemoved;
}




void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->update(deltaTime);
    }
}

void Actor::draw()
{
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->draw();
    }
}

void Actor::end()
{
    m_started = false;
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->end();
    }
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());

    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->onDestroy();
    }
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}