#include "maptile.h"
#include <cassert>

MapTile::MapTile()
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