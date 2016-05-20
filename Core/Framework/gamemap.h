#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include <vector>

//forward declarations
class BackBuffer;
class MapObject;
class MapTile;



class GameMap
{
	//Member Functions
public:
	GameMap();
	~GameMap();
	void Initialise(const char* mapFileLocation, const char* objectFileLocation);
	void GenerateMap(BackBuffer& backBuffer);
	void Draw(BackBuffer &backBuffer);
	void Process(float deltaTime);
protected:
private:
	//Member Data
public:
protected:
private:
	const char* m_mapFileLocation;
	const char* m_objectFileLocation;
	std::vector<std::vector<MapTile>*> m_tileContainer;
	std::vector<std::vector<MapObject>*> m_objectContainer;
	int m_mapHeight;
	int m_mapWidth;
};
#endif // !__GAMEMAP_H__