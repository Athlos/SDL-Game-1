#include "maptile.h"
#include <cassert>

MapTile::MapTile()
: m_x(0)
, m_y(0)
{
}

MapTile::~MapTile()
{
}

bool
MapTile::Initialise(BackBuffer& backBuffer, char tileRepresentation)
{
	switch (tileRepresentation)
	{
	case 'F':
		m_tileSprite = backBuffer.CreateSprite("Assets//Grass_Tile.png");
		m_tileSprite->SetHeight(64.0f);
		m_tileSprite->SetWidth(64.0f);
		return true;
	case 'U':
		m_tileSprite = backBuffer.CreateSprite("Assets//Underground_Tile.png");
		m_tileSprite->SetHeight(64.0f);
		m_tileSprite->SetWidth(64.0f);
		return true;
	case 'C':
		m_tileSprite = backBuffer.CreateSprite("Assets//Castle_Tile.png");
		m_tileSprite->SetHeight(64.0f);
		m_tileSprite->SetWidth(64.0f);
		return true;
	case 'O':
		m_tileSprite = backBuffer.CreateSprite("Assets//Otherworld_Tile.png");
		m_tileSprite->SetHeight(64.0f);
		m_tileSprite->SetWidth(64.0f);
		return true;
	default:
		return false;
	}
}

void
MapTile::Draw(BackBuffer& backBuffer)
{
	assert(m_tileSprite);
	m_tileSprite->Draw(backBuffer);
}

Sprite*
MapTile::GetSprite()
{
	return m_tileSprite;
}

void
MapTile::SetPositionX(int x)
{
	m_x = x;
	m_tileSprite->SetX(static_cast<float>(m_x));
}

void
MapTile::SetPositionY(int y)
{
	m_y = y;
	m_tileSprite->SetY(static_cast<float>(m_y));
}