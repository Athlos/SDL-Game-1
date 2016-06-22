// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"
#include "direction.h"

// Library includes:
#include <cassert>
#include <string>
#include "ostream"

InputHandler::InputHandler()
: m_pGameController(0)
{

}

InputHandler::~InputHandler()
{
	if (m_pGameController)
	{
		//SDL_JoystickClose(m_pGameController);
		//m_pGameController = 0;
	}
}

bool 
InputHandler::Initialise()
{
	//int numControllesr = SDL_NumJoysticks();

	//m_pGameController = SDL_JoystickOpen(0);
	//assert(m_pGameController);

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// Ex006.2: Receive Input Events below...
	SDL_Event e;
	SDL_PumpEvents();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	std::string debugString = "";
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			//print the position to command line
			int x, y;
			SDL_GetMouseState(&x, &y);
			debugString = "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
			SDL_Log(debugString.c_str());
			break;
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_1:
				//Damage Player by 1 point
				//game.UpdatePlayerHealth(-1);
				break;
			case SDLK_2:
				//Heal Player by 1 point
				//game.UpdatePlayerHealth(1);
				break;
			case SDLK_3:
				//Add 10 Gold
				//game.UpdateGold(-10);
				break;
			case SDLK_4:
				//Remove 10 Gold
				//game.UpdateGold(10);
				break;
			case SDLK_5:
				//Spawn random pickups
				/*
				for (int i = 0; i < rand() % 10; i++)
				{
					game.SpawnPickup(rand() % 1800, rand() % 1000, HEALTH);
				}*/
				break;
			case SDLK_6:
				{
					//Spawn an enemy
					//int enemyX = rand() % 1800;
					//int enemyY = rand() % 1000;
					//debugString = "Enemy spawned at: " + std::to_string(enemyX) + ", " + std::to_string(enemyY);
					//SDL_Log(debugString.c_str());
				}
				break;
			case SDLK_SPACE:
			{
			}
			break;
			case SDLK_w:
				SDL_Log("up");
				game.UpdatePlayer(Direction::UP);
				break;
			case SDLK_s:
				SDL_Log("down");
				game.UpdatePlayer(Direction::DOWN);
				break;
			case SDLK_a:
				SDL_Log("left");
				game.UpdatePlayer(Direction::LEFT);
				break;
			case SDLK_d:
				SDL_Log("right");
				game.UpdatePlayer(Direction::RIGHT);
				break;
			case SDLK_ESCAPE:
				game.Quit();
				break;
			case SDLK_HOME:
				game.UpdatePlayer(Direction::RESET);
				break;
			case SDLK_INSERT:
				game.ToggleDebug();
				break;
			case SDLK_UP:
				SDL_Log("test");
				game.MoveTestObject(Direction::UP);
				break;
			case SDLK_DOWN:
				SDL_Log("test");
				game.MoveTestObject(Direction::DOWN);
				break;
			case SDLK_LEFT:
				SDL_Log("test");
				game.MoveTestObject(Direction::LEFT);
				break;
			case SDLK_RIGHT:
				SDL_Log("test");
				game.MoveTestObject(Direction::RIGHT);
				break;
			}
			break;
		case SDL_KEYUP:
			switch (e.key.keysym.sym)
			{
			case SDLK_w:
			case SDLK_a:
			case SDLK_d:
			case SDLK_s:
				game.UpdatePlayer(Direction::STOP);
				break;
			case SDLK_RIGHT:
			case SDLK_LEFT:
			case SDLK_DOWN:
			case SDLK_UP:
				game.MoveTestObject(Direction::STOP);
			default:
				break;
			}
		
		default:
			break;
		}
	}
}
