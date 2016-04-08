// 717310 C++ SDL Framework

// This include:
#include "inputhandler.h"

// Local includes:
#include "game.h"


// Library includes:
#include <cassert>

InputHandler::InputHandler()
: m_pGameController(0)
, counter(0)
{

}

InputHandler::~InputHandler()
{
	
}

bool 
InputHandler::Initialise()
{
	

	return (true);
}

void 
InputHandler::ProcessInput(Game& game)
{
	// Ex006.2: Receive Input Events below...
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			game.Quit();
		}
		
		
		
		switch (e.type){
			/* Look for a keypress */
		case SDL_KEYDOWN:
			/* Check the SDLKey values and move change the coords */
			switch (e.key.keysym.sym){
			case SDLK_F3:
				game.Quit();
				break;
			default:
				break;
			}
		}
	}
}
