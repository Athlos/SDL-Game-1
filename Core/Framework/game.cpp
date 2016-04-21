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
#include "physics.h"
#include "entity.h"
#include "label.h"

// Library includes:
#include <cassert>
#include <SDL.h>
#include <iostream>
//Box2D includes:
#include <Box2D\box2d.h>

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
, m_velocityIterations(0)
, m_positionIterations(0)
, m_timeStep(0.0f)
, m_gravity()
, m_toggleDebug(false)
//, m_world(m_gravity)
{
	//m_world = b2World(m_gravity);
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

	//Health Sprites
	m_HealthSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart.png");
	m_HealthLostSprite = m_pBackBuffer->CreateSprite("Assets\\Health_Heart_Depleted.png");
	m_HealthSprite->SetWidth(64);
	m_HealthSprite->SetHeight(64);
	m_HealthLostSprite->SetWidth(64);
	m_HealthLostSprite->SetHeight(64);

	//Set up player
	PlayerSpriteInit();
	m_Player = new Player();
	m_Player->Initialise(m_playerAnim);
	m_Player->SetCurrentHealth(5);
	m_Player->SetMaxHealth(5);

	//Box2D world setup
	//velocityIterations 
	m_velocityIterations = 10;
	m_positionIterations = 10;
	//timeStep = 1.0f / 60.0f;

	//b2Vec2 gravity(0.0f, -10.0f);
	//world.SetGravity(gravity);

	//TESTING LABELS
	testLabel = new Label("test label");

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
		//Box2D simulation loop
		//world.Step(timeStep, velocityIterations, positionIterations);
	}
	m_Player->Process(deltaTime);
}

void 
Game::Draw(BackBuffer& backBuffer)
{
	++m_frameCount;

	backBuffer.Clear();

	int x = 1850;
	for (int i = 0; i < m_Player->GetMaxHealth(); i++)
	{
		
		if (i < m_Player->GetCurrentHealth()) 
		{
			m_HealthSprite->SetX(x);
			m_HealthSprite->SetY(0);
			m_HealthSprite->Draw(backBuffer);
		}
		else
		{
			m_HealthLostSprite->SetX(x);
			m_HealthLostSprite->SetY(0);
			m_HealthLostSprite->Draw(backBuffer);
		}
		
		x -= 70;
	}
	m_Player->Draw(backBuffer);

	//Draw test label
	testLabel->Draw(backBuffer);

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

void
Game::PlayerSpriteInit()
{
	//will add in more sprites later
	m_playerAnim = m_pBackBuffer->CreateAnimatedSprite("Assets//character.png");

	//Default load of sprite sheet
	m_playerAnim->LoadFrames(64);
	m_playerAnim->StartAnimating();
}

void
Game::UpdatePlayer(Direction direction)
{
	//for multiple sprites, sprites will change
	//move the player sprite on screen
	switch (direction)
	{
	case UP:
		m_Player->SetVerticalVelocity(-100.0f);
		break;
	case DOWN:
		m_Player->SetVerticalVelocity(100.0f);
		break;
	case LEFT:
		m_Player->SetHorizontalVelocity(-100.0f);
		break;
	case RIGHT:
		m_Player->SetHorizontalVelocity(100.0f);
		break;
	case STOP:
		m_Player->SetVerticalVelocity(0.0f);
		m_Player->SetHorizontalVelocity(0.0f);
		break;
	case RESET://Debug, reset position to middle of screen
		m_Player->SetVerticalVelocity(0.0f);
		m_Player->SetHorizontalVelocity(0.0f);
		m_Player->SetPositionX(m_width/2);
		m_Player->SetPositionY(m_height /2);
		break;
	}
}

void
Game::ToggleDebug()
{
	m_toggleDebug = !m_toggleDebug;
	if (m_toggleDebug)
	{
		SDL_Log("Debug on");
	}
	else
	{
		SDL_Log("Debug off");
	}
}