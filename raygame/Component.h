#pragma once
class Actor; //this is called a forward declaration. basically means like this is something that exists and for now don't worry about it. this is not actually included at this point.
//

class Component
{
public:

	Component();
	Component(Actor* owner, const char* name);
	virtual ~Component();

	/// <summary>
	/// Called before the first update.
	/// </summary>
	virtual void start() {};

	/// <summary>
	/// called every time the game loops.
	/// </summary>
	/// <param name="deltaTime">amount of time that has passed between this frame and the previous</param>
	virtual void update(float deltaTime) {};

	/// <summary>
	/// called after update in order to update visuals.
	/// </summary>
	virtual void draw() {};

	/// <summary>
	/// called when the scenen ends or when an Actor is removed from the scene.
	/// </summary>
	virtual void end() {};

	/// <summary>
	/// called when the attacted actor overlaps with another.
	/// </summary>
	/// <param name="other">the actor the owner overlapped</param>
	virtual void onCollision(Actor* other) {};

	/// <summary>
	/// called right before the actor is going to be destroyed.
	/// </summary>
	virtual void onDestroy() {};

	
	/// <returns>gets the name of this component. Is usually the type name.</returns>
	const char* getName() { return m_name; }

	
	/// <returns>Gets the actor this component is attached to.</returns>
	Actor* getOwner() { return m_owner; }

private:
	const char* m_name;
	Actor* m_owner; //so this works since it is a referrence the computer knows how much space a memory address requires. 
					//if it was an Actor value type it wouldn't know since it only has a forward declaration in the Component class.




};

