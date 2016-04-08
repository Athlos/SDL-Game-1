// 717310 C++ SDL Framework

// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "animatedsprite.h"
#include "fmod.hpp"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <stdio.h>
#include <cmath>
#include <ctime>
#include <vector>
// Static Members:
Game* Game::sm_pInstance = 0;


Game&
Game::GetInstance()
{
	if (sm_pInstance == 0)
	{
		sm_pInstance = new Game();
	}

	assert(sm_pInstance);

	return (*sm_pInstance);
}

void
Game::DestroyInstance()
{
	delete sm_pInstance;
	sm_pInstance = 0;
}

Game::Game()
: m_pBackBuffer(0)
, m_pInputHandler(0)
, m_looping(true)
, m_executionTime(0)
, m_elapsedSeconds(0)
, m_frameCount(0)
, m_FPS(0)
, m_numUpdates(0)
, m_lastTime(0)
, m_lag(0)
, m_paused(0)
{

}

Game::~Game()
{
	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	system->release();
}

bool
Game::Initialise()
{
	//SET UP GRAPHICS AND INPUT
	const int width = 800;
	const int height = 600;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(width, height))
	{
		LogManager::GetInstance().Log("BackBuffer Init Fail!");
		return (false);
	}

	m_pInputHandler = new InputHandler();
	if (!m_pInputHandler->Initialise())
	{
		LogManager::GetInstance().Log("InputHandler Init Fail!");
		return (false);
	}

	
	srand(time(0));

	//SET UP ENTITIES AND VARIABLES

	//Sprite* pPlayerSprite = m_pBackBuffer->CreateSprite("");

	m_testLabel = new Label();
	m_testLabel->SetBounds(500, 0, 200, 40);
	m_testLabel->SetColour(255, 0, 0, 0);
	m_testLabel->SetText("label");
	
	//SET UP AUDIO
	system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	result = system->init(32, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.

	channel = 0;
	m_musicChannel = 0;

	//result = system->createSound("assets\\example.wav", FMOD_DEFAULT, 0, &m_enemyExplodedSound);

	//result = m_noMines->setMode(FMOD_LOOP_OFF);

	m_lastTime = SDL_GetTicks();
	m_lag = 0.0f;

	return (true);
}

bool
Game::DoGameLoop()
{
	const float stepSize = 1.0f / 60.0f;

	assert(m_pInputHandler);
	m_pInputHandler->ProcessInput(*this);

	if (m_looping)
	{
		int current = SDL_GetTicks();
		float deltaTime = (current - m_lastTime) / 1000.0f;
		m_lastTime = current;

		m_executionTime += deltaTime;

		m_lag += deltaTime;

		while (m_lag >= stepSize)
		{
			Process(stepSize);

			m_lag -= stepSize;

			++m_numUpdates;
		}

		Draw(*m_pBackBuffer);
	}

	SDL_Delay(1);

	return (m_looping);
}

void
Game::Process(float deltaTime)
{


	// Count total simulation time elapsed:
	m_elapsedSeconds += deltaTime;

	// Frame Counter:
	if (m_elapsedSeconds > 1)
	{
		m_elapsedSeconds -= 1;
		m_FPS = m_frameCount;
		m_frameCount = 0;
	}

	//If paused, returns out of the loop and nothing updates, make sure any processing occures after this point
	if (m_paused) 
	{
		return;
	}
	m_pBackBuffer->UpdatePaused(m_paused);

	system->update();
}


void
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();
	//m_testLabel->Draw(backBuffer);
	backBuffer.Present();
}

void
Game::Quit()
{
	m_looping = false;
}

void Game::Pause(bool pause) {
	m_paused = pause;
	m_musicChannel->setPaused(pause);
}

bool Game::IsPaused() {
	return (m_paused);
}
