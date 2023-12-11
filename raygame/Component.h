#pragma once
class Actor; //this is called a forward declaration. basically means like this is something that exists and for now don't worry about it. this is not actually included at this point.
//

class Component
{
public:

	virtual void start() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void end() {};
	
	virtual void onCollision() {};

	virtual void onDestroy() {};

	const char* getName() { return m_name; }


private:
	const char* m_name;
	Actor* m_owner;




};

