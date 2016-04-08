// 717310 C++ SDL Framework
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <string>
#include "SDL_ttf.h"
#include <SDL.h>   // All SDL App's need this
using namespace std;

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
struct SDL_Window;
struct SDL_Renderer;



class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();
	void UpdatePaused(bool paused);

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawSprite(Sprite& sprite);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);
	Sprite* CreateSprite(const char* pcFilename);
	void DrawAnimatedSprite(AnimatedSprite& sprite, int x, int width);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);
	void SetGameState(bool state);
	void SetMouse(int x, int y);
	void SetMouseLock(bool lock);

	void DrawText(SDL_Texture* textOnScreen, SDL_Rect bounds);

	SDL_Texture* CreateText(string text, SDL_Color colour);

	
protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	//Member Data:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	SDL_Surface* m_surface;
	TTF_Font* m_font;

	bool m_paused;
	bool m_gameOver;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;
	
private:

};

#endif // __BACKBUFFER_H__
