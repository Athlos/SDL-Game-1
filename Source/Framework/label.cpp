#include "label.h"

using namespace std;


Label::Label()
{
	m_colour = { 0, 0, 0, 0 };
	m_textTexture = NULL;
	m_requiredUpdate = false;
}


Label::~Label()
{
}

string Label::GetText() {
	return m_text;
}

void Label::SetText(string textOnScreen, BackBuffer& backbuffer) {
	if (m_text == textOnScreen) {
		return;
	}
	m_text = textOnScreen;
	m_textTexture = backbuffer.CreateText(textOnScreen, m_colour);

}

void Label::SetText(string textOnScreen) {
	if (m_text == textOnScreen) {
		return;
	}
	m_text = textOnScreen;
	m_requiredUpdate = true;
}

void Label::SetColour(int r, int g, int b, int a) {
	m_colour = { r, g, b, a };
}

void Label::Draw(BackBuffer& backBuffer)
{
	if (m_requiredUpdate) {
		m_requiredUpdate = false;
		m_textTexture = backBuffer.CreateText(m_text, m_colour);
	}
	backBuffer.DrawText(m_textTexture, m_bounds);
}

void Label::SetBounds(int x, int y, int w, int h) {
	m_bounds.x = x;
	m_bounds.y = y;
	m_bounds.w = w;
	m_bounds.h = h;
}

SDL_Rect Label::GetBounds() {
	return m_bounds;
}
