// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include "direction.h"
#include <vector>
#include <box2d.h>
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

class Game
{
	//Member Methods:
public:
	static Game& GetInstance();
	static void DestroyInstance();
	~Game();
	bool Initialise();
	bool DoGameLoop();
	void Quit();

	//Player update methods, for input mainly
	void UpdatePlayerHealth(int amount);
	void UpdatePlayer(Direction direction);
	void UpdateGold(int amount);

	//Spawn & Debug functions
	void ToggleDebug();
	void CheckForCollision();
	void MoveTestObject(Direction direction);

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

	Entity* m_testEntity;
	Sprite* m_testSprite;

	Entity* m_ballEntity;
	Sprite* m_ballSprite;

	//Collision Listener
	CollisionListener m_collisionListener;
private:

};

#endif // __GAME_H__