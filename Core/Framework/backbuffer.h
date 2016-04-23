// 717310 C++ SDL Framework
#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include <SDL_ttf.h>
#include <string>

// Forward Declarations:
class TextureManager;
class Sprite;
struct SDL_Window;
struct SDL_Renderer;
class AnimatedSprite;
class SDL_Image;
class SDL;
class AnimatedSprite;

class BackBuffer
{
	//Member Methods:
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawAnimatedSprite(AnimatedSprite& animSprite, SDL_Rect bounds);
	void DrawSprite(Sprite& sprite);
	void DrawRectangle(int x1, int y1, int x2, int y2);
	void DrawLine(int x1, int y1, int x2, int y2);

	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);

	Sprite* CreateSprite(const char* pcFilename);
	void RenderTexture(SDL_Texture* texture, int xPosition, int yPosition, int width, int height);

	//Create text textures for labels
	SDL_Texture* CreateText(std::string text, SDL_Color colour);
	//Draw text for labels
	void DrawText(SDL_Texture* textOnScreen, SDL_Rect bounds);
	

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

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;
	
private:

};

#endif // __BACKBUFFER_H__
