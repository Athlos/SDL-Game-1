#ifndef __LABEL_H__
#define __LABEL_H__

#include "entity.h"
#include "sprite.h"
#include "backbuffer.h"
#include "texture.h"
#include <cassert>

using namespace std;

class Label : public Entity
{
public:
	Label();
	~Label();

	//Set the text image, if the text is the same it returns, you can call this in the process loop safely
	void SetText(string, BackBuffer& backBuffer);
	//only changes the string, does not make new image
	void SetText(string textOnScreen);
	//standard draw
	void Draw(BackBuffer& backBuffer);
	//set the bounds of your text, and the words will be constrained to this window
	void SetBounds(int x, int y, int w, int h);
	//Set the colour, default is black already, set this before you set the text
	void SetColour(int r, int g, int b, int a);
	//get the string of text stored
	string GetText();
	//get the collision bounds
	SDL_Rect GetBounds();

	//Member Data:
public:

protected:
	string m_text;
	SDL_Texture* m_textTexture;
	SDL_Rect m_bounds;
	SDL_Color m_colour;
	bool m_requiredUpdate;

private:
};

#endif //__LABEL_H__
