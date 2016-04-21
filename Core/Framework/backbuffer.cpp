// 717310 C++ SDL Framework

// This include:
#include "backbuffer.h"

// Local includes:
#include "logmanager.h"
#include "texturemanager.h"
#include "sprite.h"
#include "texture.h"
#include "SDL_image.h"
#include "animatedsprite.h"

// Library includes:
#include <SDL.h>
#include <cassert>
#include <SDL_ttf.h>
#include <string>

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0xFF)
, m_clearGreen(0xFF)
, m_clearBlue(0xFF)
{

}

BackBuffer::~BackBuffer()
{
	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;
	delete m_pTextureManager;
	IMG_Quit();
	SDL_Quit();
}

bool 
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("SDL Supported Framework", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED); 

			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
				else
				{
					int ttfResult = TTF_Init();
					if (ttfResult != 0)
					{
						LogSDLError();
						return (false);
					}
				}
			}
		}
	}

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	//Grab a surface for labels
	m_surface = SDL_GetWindowSurface(m_pWindow);

	//Initialise true type font, and load up a default font
	TTF_Init();
	m_font = TTF_OpenFont("assets/currentfont.TTF", 48);

	return (true);
}

void 
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void
BackBuffer::DrawAnimatedSprite(AnimatedSprite& sprite, int frameX, int frameY)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = 32;
	dest.h = 32;

	SDL_Rect* r = new SDL_Rect;

	r->x = frameX;
	r->y = frameY;
	r->w = 32;
	r->h = 32;

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), r, &dest);
}

void 
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest);
}

void
BackBuffer::DrawRectangle(int x1, int y1, int x2, int y2)
{
	SDL_Rect fillRect;
	
	fillRect.x = x1;
	fillRect.y = y1;
	fillRect.w = x2;
	fillRect.h = y2;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void 
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite* 
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pSprite);
}

void 
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}


void
BackBuffer::RenderTexture(SDL_Texture* texture, int x, int y, int width, int height)
{
	SDL_Rect fillRect;
	fillRect.x = x;
	fillRect.y = y;
	fillRect.w = width;
	fillRect.h = height;
	SDL_RenderCopy(m_pRenderer, texture, NULL, &fillRect);
}

AnimatedSprite*
BackBuffer::CreateAnimatedSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	AnimatedSprite* pAnimSprite = new AnimatedSprite();
	if (!pAnimSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite Failed to Create!");
	}

	return (pAnimSprite);
}


void BackBuffer::DrawText(SDL_Texture* textOnScreen, SDL_Rect bounds) 
{
	//Basic render of the texture of the label
	SDL_RenderCopy(m_pRenderer, textOnScreen, 0, &bounds);

}

SDL_Texture* BackBuffer::CreateText(std::string text, SDL_Color colour) 
{
	//Grab a surface
	m_surface = SDL_GetWindowSurface(m_pWindow);

	//create text and save into surface, then use surface to create a texture we can render
	m_surface = TTF_RenderText_Solid(m_font, text.c_str(), colour);
	SDL_Texture* tTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_surface);
	//Clean up surface, we grab a new one each time - need to look into why I do that
	SDL_FreeSurface(m_surface);

	return tTexture;

}