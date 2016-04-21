// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include <vector>
#include <Box2D\box2d.h>

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class AnimatedSprite;
class Player;
class Physics;
class Entity;
class Label;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	STOP,
	RESET
};

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

	void UpdatePlayerHealth(int amount);
	void UpdatePlayer(Direction direction);
	void ToggleDebug();
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

	//Player Sprites
	AnimatedSprite* m_playerAnim;

	//Player
	Player* m_Player;

	//Box2D Data
	b2Vec2 m_gravity;
	//b2World m_world;
	int32 m_velocityIterations;
	int32 m_positionIterations;
	float32 m_timeStep;
	//Physics* m_physics();

	Label* testLabel;

private:

};

#endif // __GAME_H__
