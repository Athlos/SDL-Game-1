#include "gamemap.h"
#include "maptile.h"
#include "mapobject.h"

#include <cassert>
#include <sstream>
#include <fstream>
#include <vector>
#include <SDL.h>

GameMap::GameMap()
: m_mapHeight(0)
, m_mapWidth(0)
{
}

GameMap::~GameMap()
{
}

void
GameMap::Initialise(const char* mapFileLocation, const char* objectFileLocation)
{
	m_mapFileLocation = mapFileLocation;
	m_objectFileLocation = objectFileLocation;
	std::ifstream inputFile(mapFileLocation, std::ifstream::in);
	char tile = inputFile.get();
	m_mapHeight = 0;
	m_mapWidth = 0;
	bool endOfWidth = false;
	while (inputFile.good())
	{
		if (!endOfWidth)
		{
			if (tile == 'F' || tile == 'O' || tile == 'U' || tile == 'C')
			{
				m_mapWidth++;
			}
		}
		if (tile == '\n')
		{
			endOfWidth = true;
			++m_mapHeight;
		}
		else if (tile == '/')
		{
			++m_mapHeight;
			break;
		}
		tile = inputFile.get();
	}
	inputFile.close();
	m_tileContainer.resize(m_mapHeight);
	m_objectContainer.resize(m_mapHeight);
	for (int i = 0; i < m_mapHeight; i++)
	{
		m_tileContainer[i].resize(m_mapWidth);
		m_objectContainer[i].resize(m_mapWidth);
	}

}

void
GameMap::GenerateMap(BackBuffer& backBuffer, b2World& m_world)
{	 
	std::ifstream mapFile(m_mapFileLocation, std::ifstream::in);
	char tile = mapFile.get();
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			MapTile mapTile = MapTile();
			if (tile == ',' || tile == '\n')
			{
				tile = mapFile.get();
			}
			if (tile == '/')
			{
				break;
			}
			if (tile == 'F' || tile == 'O' || tile == 'U' || tile == 'C')
			{
				if (!mapTile.Initialise(backBuffer, tile))
				{
					break;
				}
				else
				{
					mapTile.SetPositionX(j * mapTile.GetSprite()->GetWidth());
					mapTile.SetPositionY(i * mapTile.GetSprite()->GetHeight());
					m_tileContainer[i][j] = mapTile;
				}
			}
			tile = mapFile.get();
		}
	}
	mapFile.close();
	//object setup
	std::ifstream objectFile(m_objectFileLocation, std::ifstream::in);
	char object = objectFile.get();
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			MapObject* mapObject = new MapObject();
			if (object == ',' || object == '\n')
			{
				object = objectFile.get();
			}
			if (object == '/')
			{
				break;
			}
			if (object == 'B' || object == 'E' || object == 'C')
			{
				if (!mapObject->Initialise(backBuffer, object))
				{
					break;
				}
				else
				{
					if (object != 'E')
					{
						mapObject->SetPositionX(j * mapObject->GetSprite()->GetWidth());
						mapObject->SetPositionY(i * mapObject->GetSprite()->GetHeight());
						mapObject->SetupCollision(m_world);
					}
					m_objectContainer[i][j] = mapObject;
				}
			}
			object = objectFile.get();
		}
	}
	objectFile.close();
}

void
GameMap::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			m_tileContainer[i][j].Draw(backBuffer);
			if (m_objectContainer[i][j]->GetTileReprensentation() != 'E')
			{
				m_objectContainer[i][j]->Draw(backBuffer);
			}
			/*Debug Code
			if (m_objectContainer.at(i)->at(j).GetTileReprensentation() == 'B')
			{
				std::string objectPosition = "Pos X: " + std::to_string(m_objectContainer.at(i)->at(j).GetObjectBodyDef().position.x) +
					"Pos Y: " + std::to_string(m_objectContainer.at(i)->at(j).GetObjectBodyDef().position.y);
				SDL_Log(objectPosition.c_str());
			}*/
		}
	}
}

void
GameMap::Process(float deltaTime)
{
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			m_objectContainer[i][j]->Process(deltaTime);
		}
	}
}
MapObject&
GameMap::GetMapObjectAtPosition(float x, float y)
{
	int tileRow = 0;
	int tileCol = 0;
	if (x == 0)
	{
		tileRow = 0;
	}
	else
	{
		tileRow = x / 64.0f;
		tileRow = x / 64.0f;
	}
	if (y == 0)
	{
		tileCol = 0;
	}
	else
	{
		tileCol = y / 64.0f;
	}
	if ((m_objectContainer[tileCol][tileRow]->GetTileReprensentation() == 'B'))
	{
		return *(m_objectContainer[tileCol][tileRow]);
	}
	else
	{
		MapObject* m = new MapObject();
		return (*m);
	}
}