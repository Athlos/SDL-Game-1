// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"

// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;
class AnimatedSprite;



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
protected:
	void Process(float deltaTime);
	void Draw(BackBuffer& backBuffer);
	
private:
	Game(const Game& game);
	Game& operator=(const Game& game);
	
	Game();

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
	bool m_drawDebugInfo;
	int m_width;
	int m_height;

	AnimatedSprite* m_playerSprite;

private:

};

#endif // __GAME_H__
