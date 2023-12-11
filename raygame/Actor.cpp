#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"

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

/// <summary>
/// </summary>
/// <returns>If the actors start function has been called.</returns>

inline bool Actor::getStarted() { return m_started; }

void Actor::start()
{
    m_started = true;
}

void Actor::onCollision(Actor* other)
{
}

void Actor::update(float deltaTime)
{
    m_transform->updateTransforms();
}

void Actor::draw()
{
}

void Actor::end()
{
    m_started = false;
}

void Actor::onDestroy()
{
    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}