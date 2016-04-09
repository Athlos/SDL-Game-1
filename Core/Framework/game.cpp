// This includes:
#include "game.h"

// Local includes:
#include "backbuffer.h"
#include "inputhandler.h"
#include "logmanager.h"
#include "sprite.h"
#include "texture.h"
#include "animatedsprite.h"
#include "player.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <iostream>

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
, m_width(0)
, m_height(0)
{
	
}

Game::~Game()
{
	delete m_pBackBuffer;
	delete m_pInputHandler;
	m_pBackBuffer = 0;
}

bool 
Game::Initialise()
{
	m_width = 1920;
	m_height = 1080;

	m_pBackBuffer = new BackBuffer();
	if (!m_pBackBuffer->Initialise(m_width, m_height))
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

	m_HealthSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart.png");

	//Set up player
	m_Player = new Player();
	m_Player->SetCurrentHealth(5);
	m_Player->SetMaxHealth(5);



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
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	int x = 1780;
	for (int i = 0; i < m_Player->GetCurrentHealth(); i++)
	{
		m_HealthSprite->SetX(x);
		m_HealthSprite->SetY(0);
		m_HealthSprite->Draw(backBuffer);
		x -= 150;
	}

	backBuffer.Present();
}

void 
Game::Quit()
{
	m_looping = false;
}

void Game::UpdatePlayerHealth(int amount)
{
	m_Player->UpdatePlayerHealth(amount);

}