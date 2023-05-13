#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "model/Creature.hpp"
#include "service/Generation.hpp"

using namespace std;

class RenderWindow {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	int width;
	int height;

	void drawCreature(Creature* creature);

public:
	RenderWindow(const char* title, int width, int height);
	~RenderWindow();

	void clear();
	void display();

	void renderGeneration(Generation* generation);
};
