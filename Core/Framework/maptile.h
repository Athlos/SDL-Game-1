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

class MapTile
{
	//Member Functions
public:
	MapTile();
	~MapTile();
	bool Initialise(BackBuffer& backBuffer, char tileRepresentation);
	void Draw(BackBuffer &backBuffer);
	Sprite* GetSprite();

	void SetPositionX(int x);
	void SetPositionY(int y);

	int GetPositionX();
	int GetPositionY();

protected:
private:
	//Member Data
public:
protected:
private:
	Sprite* m_tileSprite;
	int m_x;
	int m_y;
};

#endif // !__MAPTILE_H__
