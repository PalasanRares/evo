#include "RenderWindow.hpp"

#include <iostream>

void RenderWindow::drawCreature(Creature* creature) {

	float radius = creature->getChromosome()->getSize();

	float x = radius;
	float y = 0;
	float err = 0;

	Color creatureColor = creature->getChromosome()->getColor();
	SDL_SetRenderDrawColor(renderer, creatureColor.r, creatureColor.g, creatureColor.b, 255);

	while (x >= y) {
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() + x, creature->getY() + y);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() + y, creature->getY() + x);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() - y, creature->getY() + x);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() - x, creature->getY() + y);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() - x, creature->getY() - y);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() - y, creature->getY() - x);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() + y, creature->getY() - x);
		SDL_RenderDrawLineF(renderer, creature->getX(), creature->getY(), creature->getX() + x, creature->getY() - y);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		} else {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

RenderWindow::RenderWindow(const char* title, int width, int height) : window(nullptr), renderer(nullptr), width(width), height(height) {
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << "Window failed to initialize. Error " << SDL_GetError() << endl;
	}
	else {
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			cout << "Renderer failed to initialize. Error " << SDL_GetError() << endl;
		}
	}
}

RenderWindow::~RenderWindow() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void RenderWindow::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 125, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}

void RenderWindow::renderGeneration(Generation* generation) {
	Creature** creaturePool = generation->getCreaturePool();
	for (int i = 0; i < generation->getNoCreatures(); i++) {
		creaturePool[i]->update(this->width, this->height);
		this->drawCreature(creaturePool[i]);
	}
}