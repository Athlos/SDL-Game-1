#include "gamemap.h"
#include "maptile.h"
#include "mapobject.h"

#include <cassert>
#include <sstream>
#include <fstream>

GameMap::GameMap()
: m_mapHeight(0)
, m_mapWidth(0)
{
}

GameMap::~GameMap()
{
}

void
GameMap::Initialise(const char* m_mapFileLocation, const char* objectFileLocation)
{
	std::ifstream inputFile(m_mapFileLocation, std::ifstream::in);
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
	for (int i = 0; i < m_mapHeight; i++)
	{
		m_tileContainer.push_back(new std::vector <MapTile>);
		m_objectContainer.push_back(new std::vector <MapObject>);
	}
}

void
GameMap::GenerateMap(BackBuffer& backBuffer)
{
	std::ifstream mapFile;
	
	mapFile.open(m_mapFileLocation, std::ifstream::in);
	char tile = mapFile.get();
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			MapTile* mapTile = new MapTile();
			if (tile == ',' || tile == '\n')
			{
				tile = mapFile.get();
			}
			if (tile == '/')
			{
				break;
			}
			//if (tile == 'F' || tile == 'O' || tile == 'U' || tile == 'C')
			//{
				mapTile->Initialise(backBuffer, tile);
				m_tileContainer.at(i)->push_back(*mapTile);
				//debugging code
				//if (!m_tileContainer.at(i)->at(j).CheckIfInsulated())
				//{
				//SDL_Log("Successfully made a tile");
				//std::string index1 = std::to_string(i);
				//std::string index2 = std::to_string(j);
				//std::string indexNum = "Index Number: " + index1 + ", " + index2 + ", " + std::to_string(m_tileContainer.at(i)->at(j).GetTileType());
				//SDL_Log(indexNum.c_str());
				//}
			//}
			tile = mapFile.get();
		}
	}
	mapFile.close();
	/*
	std::ifstream objectFile;
	SDL_Log("checking object  file");
	objectFile.open(m_objectFileLocation, std::ifstream::in);
	if (!objectFile)
	{
		SDL_Log("text file error!, please check the name");
	}
	char object = objectFile.get();
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			MapObject* t = new MapObject();
			if (object == ',' || object == '\n')
			{
				object = objectFile.get();
			}
			if (object == '/')
			{
				break;
			}
			if (object == 'C' || object == 'B' || object == 'E')
			{
				if (!t->Initialise(backBuffer,object))
				{
					break;
				}
				else
				{
					m_objectContainer.at(i)->push_back(*t);
					//debugging code
					//if (!m_objectContainer.at(i)->at(j).GetIfHarvested())
					//{
					//SDL_Log("Successfully made a tile");
					//std::string index1 = std::to_string(i);
					//std::string index2 = std::to_string(j);
					//std::string indexNum = "Index Number: " + index1 + ", " + index2 + ", " + std::to_string(m_objectContainer.at(i)->at(j).GetTileType());
					//SDL_Log(indexNum.c_str());
					//}
				}
			}
			object = objectFile.get();
		}
	}
	objectFile.close();*/
}

void
GameMap::Draw(BackBuffer &backBuffer)
{
	for (int i = 0; i < m_mapHeight; i++)
	{
		for (int j = 0; j < m_mapWidth; j++)
		{
			m_tileContainer.at(i)->at(j).GetSprite()->SetX((j * m_tileContainer.at(i)->at(j).GetSprite()->GetWidth()));
			m_tileContainer.at(i)->at(j).GetSprite()->SetY((i * m_tileContainer.at(i)->at(j).GetSprite()->GetHeight()));
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
			m_objectContainer.at(i)->at(j).Process(deltaTime);;
		}
	}
}