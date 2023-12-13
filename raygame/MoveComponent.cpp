#include "MoveComponent.h"
#include "Actor.h"
#include "Transform2D.h"

MoveComponent::MoveComponent(float maxSpeed, Actor* owner) : Component(owner, "MoveComponent")
{
	m_maxSpeed = maxSpeed;
}

void MoveComponent::update(float deltaTime)
{
	//store what the current position is.
	MathLibrary::Vector2 position = getOwner()->getTransform()->getLocalPosition();



	//if the celocirt is over the maximium speed...
	if (getVelocity().getMagnitude() > getMaxSpeed())
	{
		//...normalize the velocity and scale it by the max speed to clamp it.
		MathLibrary::Vector2 newVelocity = getVelocity().getNormalized() * getMaxSpeed();
		setVelocity(newVelocity);
	}
	//Increase the current position by the velocity to get the new position
	position = position + getVelocity() * deltaTime;

	//set the transform position to be the new position.
	getOwner()->getTransform()->setLocalPosition(position);

}