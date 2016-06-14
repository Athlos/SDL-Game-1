// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include "direction.h"
#include "pickup.h"
#include "conversion.h"
#include <vector>
#include <box2d.h>
#include "conversion.h"
#include "collisionlistener.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class AnimatedSprite;
class Player;
class Entity;
class Label;
class GameMap;
class Enemy;
class MainMenu;

enum GameState
{
	MAINMENU,
	INGAME,
	SHOP
};

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();
	bool Initialise();
	void InitialiseData();
	bool DoGameLoop();
	void Quit();

	//Menus
	void OpenMainMenu();
	void MouseClicked(int x, int y);

	//Player update methods, for input mainly
	void UpdatePlayerHealth(int amount);
	void UpdatePlayer(Direction direction);
	void UpdateGold(int amount);

	//Spawn & Debug functions
	void SpawnEnemy(int x, int y);
	void SpawnPickup(int x, int y, PickupType type);
	void ToggleDebug();
	void CheckForCollision();

	//Combat, mainly debugging atm
	void PlayerAttack();

	bool GameOver();
	void RestartGame();
	void SaveGame();
	void LoadGame();

	//Debug
	void WaypointMode();
	void PlaceWaypoint(int x, int y);
	void ChangeSelectedEnemy();
	void SaveCurrentPatrol();
	void LoadPatrol();
	void ClearPatrol();
	void DebugCommand(std::string consoleCommand);
	void DrawDebugConsole(std::string text);
	void ShowDebugConsole(bool open);

	GameState GetGameState();

protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	
private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

	void PlayerSpriteInit();

	//Member Data:
public:

protected:
	static Game* sm_pInstance;
	BackBuffer* m_pBackBuffer;
	InputHandler* m_pInputHandler;
	bool m_looping;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_toggleDebug;
	int m_width;
	int m_height;

	//Game over
	Label* m_gameOver;
	Label* m_restartGame;

	//Sprites
	Sprite* m_HealthSprite;
	Sprite* m_HealthLostSprite;

	//Player Sprites
	AnimatedSprite* m_playerAnim;

	//Player
	Player* m_player;

	//Enemy
	std::vector<Enemy*> m_enemies;

	//Box2D Data world setup
	b2Vec2 m_gravity;
	b2World m_world;
	int32 m_velocityIterations;
	int32 m_positionIterations;
	float32 m_timeStep;

	//Player Gold
	Label* m_goldLabel;
	int m_gold;

	//Pickups
	std::vector<Pickup*> m_pickups;

	//Game Map
	GameMap* m_gameMap;

	//Collision Listener
	CollisionListener m_collisionListener;

	//Menu
	bool m_inMainMenu;
	MainMenu* m_mainMenu;

	//Debug
	bool m_waypointMode;
	Label* m_waypointModeLabel;
	int m_enemySelectedIndex;
	Label* m_enemySelectedLabel;
	int m_pathToLoadCounter;
	int m_pathToSaveCounter;
	bool m_debugConsoleOpen;
	std::string m_debugString;
	Label* m_debugText;

	bool m_isGameRunning;

private:

};

#endif // __GAME_H__
