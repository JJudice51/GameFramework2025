#pragma once
#include "Component.h"
#include <Vector2.h>

class Acotr;

class MoveComponent :
    public Component
{
public:
    MoveComponent(float maxSpeed, Actor* owner);

    MathLibrary::Vector2 getVelocity() { return m_velocity; }

    void setVelocity(MathLibrary::Vector2 velocity) {m_velocity = velocity;}
    
    float getMaxSpeed() { return m_maxSpeed; }
    void setMaxSpeed(float maxSpeed) { m_maxSpeed = maxSpeed; }

    void update(float deltaTime) override;

private:
    float m_maxSpeed = 1.0f;
    MathLibrary::Vector2 m_velocity;
};

