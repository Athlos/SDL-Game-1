// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"

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
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			//print the position to command line
			int x, y;
			SDL_GetMouseState(&x, &y);
			std::string mousePosition = "X: " + std::to_string(x) + ", Y: " + std::to_string(y);
			SDL_Log(mousePosition.c_str());
		}
		else if (state[SDL_SCANCODE_W])
		{
			SDL_Log("upper left");
			//game.UpdatePlayerSprite(UPPERLEFT);
		}
		else if (state[SDL_SCANCODE_D])
		{
			SDL_Log("upper right");
			//game.UpdatePlayerSprite(UPPERRIGHT);
		}
		else if (state[SDL_SCANCODE_A])
		{
			SDL_Log("lower left");
			//game.UpdatePlayerSprite(LOWERLEFT);
		}
		else if (state[SDL_SCANCODE_S])
		{
			SDL_Log("lower right");
			//game.UpdatePlayerSprite(LOWERRIGHT);
		}
		else if (state[SDL_SCANCODE_ESCAPE])
		{
			game.Quit();
		}
	}
}
