#include "RenderWindow.hpp"

#include <iostream>
#include <cmath>

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

void RenderWindow::drawFoodSource(Food* foodSource) {

	float radius = foodSource->getCapacity();

	float x = radius;
	float y = 0;
	float err = 0;

	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 10);

	while (x >= y) {
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() + x, foodSource->getY() + y);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() + y, foodSource->getY() + x);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() - y, foodSource->getY() + x);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() - x, foodSource->getY() + y);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() - x, foodSource->getY() - y);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() - y, foodSource->getY() - x);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() + y, foodSource->getY() - x);
		SDL_RenderDrawLineF(renderer, foodSource->getX(), foodSource->getY(), foodSource->getX() + x, foodSource->getY() - y);

		if (err <= 0) {
			y += 1;
			err += 2 * y + 1;
		} else {
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

float distanceBetweenTwoPoints(float x1, float y1, float x2, float y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void RenderWindow::checkCollision(Generation* generation) {
	for (int i = 0; i < generation->getNoCreatures(); i++) {
		Creature* creature = generation->getCreaturePool()[i];
		for (int j = 0; j < generation->getNoFoodSources(); j++) {
			Food* foodSource = generation->getFoodSources()[j];
			if (distanceBetweenTwoPoints(creature->getX(), creature->getY(), foodSource->getX(), foodSource->getY()) <= creature->getChromosome()->getSize() + foodSource->getCapacity()) {
				creature->consumeFood();
				foodSource->decreaseCapacity();
			}
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
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
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

	Food** foodSources = generation->getFoodSources();
	for (int i = 0; i < generation->getNoFoodSources(); i++) {
		this->drawFoodSource(foodSources[i]);
	}
	this->checkCollision(generation);

	// Creature* c = creaturePool[0];
	// Food* f = foodSources[0];
	// cout << distanceBetweenTwoPoints(c->getX(), c->getY(), f->getX(), f->getY()) << endl;
	// cout << c->getChromosome()->getSize() + f->getCapacity() << endl;

}