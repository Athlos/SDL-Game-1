// 717310 C++ SDL Framework
#ifndef __GAME_H__
#define __GAME_H__



// Forward Declarations
class BackBuffer;
class InputHandler;
class Sprite;

#include "fmod.hpp";
#include "label.h";

#include <vector>;

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

	void Pause(bool pause);
	bool IsPaused();
	
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
	Label* m_testLabel;

	// Simulation Counters:
	float m_elapsedSeconds;
	float m_lag;
	float m_executionTime;
	int m_lastTime;
	int m_frameCount;
	int m_FPS;
	int m_numUpdates;
	bool m_drawDebugInfo;


	
	bool m_paused;

	

	//GAME ENTITIES


	//AUDIO
	FMOD::System *system;
	FMOD_RESULT result;
	FMOD::Channel* channel;
	FMOD::Channel* m_musicChannel;

	

private:

};

#endif // __GAME_H__
