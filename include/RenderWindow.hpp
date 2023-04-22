#pragma once
#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"

#include "model/Creature.hpp"
#include "service/Generation.hpp"

#include <string>

using namespace std;

class RenderWindow {
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TTF_Font* font;

	SDL_Texture* preyTexture;
	SDL_Texture* hunterTexture;

	int width;
	int height;

	void drawCircle(float x, float y, float radius);
	void drawCreature(Creature* creature);
	void drawFoodSource(Food* foodSource);

	void drawText(const string& message, const float& x, const float& y);

	void checkCollision(Generation* generation);
	void checkCreaturesCollision(Generation* generation);

public:
	RenderWindow(const char* title, int width, int height);
	~RenderWindow();

	void clear();
	void display();

	void renderGeneration(Generation* generation);
};
