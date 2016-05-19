#ifndef __MAPTILE_H__
#define __MAPTILE_H__

#include "sprite.h"
#include "backbuffer.h"

enum TileType
{
	FOREST,
	UNDERGROUND,
	CASTLE,
	OTHERWORLD,
	BLANK
};

class MapTile : public Sprite
{
	//Member Functions
public:
	MapTile();
	~MapTile();
	bool Initialise(BackBuffer& backBuffer, char tileRepresentation);
	void Draw(BackBuffer &backBuffer);
	Sprite* GetSprite();
protected:
private:
	//Member Data
public:
protected:
private:
	Sprite* m_tileSprite;
};

#endif // !__MAPTILE_H__
