#pragma once

#include "entity.h"
#include "animatedsprite.h"

enum PickupType
{
	HEALTH,
	GOLD
};

class Pickup : public Entity
{
public:
	Pickup();
	~Pickup();

	void Process(float deltaTime);
	void Draw(BackBuffer& backbuffer);
	bool Initialise(AnimatedSprite* p_animSprite);

	void SetPickedUp(bool isPickedUp);
	bool IsPickedUp();

	void SetPickupType(PickupType type);
	PickupType GetPickupType();

	//Variables
public:
protected:
private:
	AnimatedSprite* m_animSprite;

	bool m_isPickedUp;

	PickupType m_type;
	

	//pickup will bob up and down in this range
	int m_bobX;
	int m_bobY;
	int m_rawX;
	int m_rawY;
	bool m_bobUpDown;
	bool m_bobLeftRight;

};

