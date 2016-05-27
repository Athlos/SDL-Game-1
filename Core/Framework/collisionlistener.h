#ifndef __COLLISIONLISTENERS_H__
#define __COLLISIONLISTENERS_H__

#include "Box2D.h"

class CollisionListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact) override;
	virtual void EndContact(b2Contact* contact) override;
protected: 
private:
};


#endif // !1

