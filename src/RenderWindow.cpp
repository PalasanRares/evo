#include "RenderWindow.hpp"

#include <iostream>
#include <cmath>

void RenderWindow::drawCircle(float x, float y, float radius) {
	float x0 = radius;
	float y0 = 0;
	float err = 0;

	while (x0 >= y0) {
		SDL_RenderLine(renderer, x, y, x + x0, y + y0);
		SDL_RenderLine(renderer, x, y, x + y0, y + x0);
		SDL_RenderLine(renderer, x, y, x - y0, y + x0);
		SDL_RenderLine(renderer, x, y, x - x0, y + y0);
		SDL_RenderLine(renderer, x, y, x - x0, y - y0);
		SDL_RenderLine(renderer, x, y, x - y0, y - x0);
		SDL_RenderLine(renderer, x, y, x + y0, y - x0);
		SDL_RenderLine(renderer, x, y, x + x0, y - y0);

		if (err <= 0) {
			y0 += 1;
			err += 2 * y0 + 1;
		} else {
			x0 -= 1;
			err -= 2 * x0 + 1;
		}
	}
}

void RenderWindow::drawCreature(Creature* creature) {
	Color creatureColor = creature->getChromosome()->getColor();
	SDL_FRect creatureArea = { creature->getX() - creature->getChromosome()->getSize(), creature->getY() - creature->getChromosome()->getSize(), creature->getChromosome()->getSize() * 2, creature->getChromosome()->getSize() * 2 };

	if (creature->getChromosome()->getPredator()) {
		SDL_SetTextureColorMod(hunterTexture, creatureColor.r, creatureColor.g, creatureColor.b);
		SDL_RenderTexture(renderer, hunterTexture, nullptr, &creatureArea);
	} else {
		SDL_SetTextureColorMod(preyTexture, creatureColor.r, creatureColor.g, creatureColor.b);
		SDL_RenderTexture(renderer, preyTexture, nullptr, &creatureArea);
	}
}

void RenderWindow::drawFoodSource(Food* foodSource) {
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 10);

	drawCircle(foodSource->getX(), foodSource->getY(), foodSource->getCapacity());
}

void RenderWindow::drawText(const string& message, const float& x, const float& y) {
	SDL_Color white = { 255, 255, 255 };
	
	SDL_Surface* messageSurface = TTF_RenderUTF8_Solid(font, message.c_str(), white);
	SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
	SDL_FRect messageArea = { x, y, (float) messageSurface->w, (float) messageSurface->h };

	SDL_RenderTexture(renderer, messageTexture, nullptr, &messageArea);

	SDL_DestroySurface(messageSurface);
	SDL_DestroyTexture(messageTexture);
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

void RenderWindow::checkCreaturesCollision(Generation* generation) {
	for (int i = 0; i < generation->getNoCreatures() - 1; i++) {
		Creature* creature1 = generation->getCreaturePool()[i];
		for (int j = i + 1; j < generation->getNoCreatures(); j++) {
			Creature* creature2 = generation->getCreaturePool()[j];
			if (distanceBetweenTwoPoints(creature1->getX(), creature1->getY(), creature2->getX(), creature2->getY()) <= creature1->getChromosome()->getSize() + creature2->getChromosome()->getSize()) {
				if (creature1->getChromosome()->getPredator() && creature1->getChromosome()->getStrength() > creature2->getChromosome()->getStrength()) {
					creature1->consumeFood();
					generation->killCreature(j);
				} else if (creature2->getChromosome()->getPredator() && creature2->getChromosome()->getStrength() > creature1->getChromosome()->getStrength()) {
					creature2->consumeFood();
					generation->killCreature(i);
				}
			}
		}
	}
}

RenderWindow::RenderWindow(const char* title, int width, int height) : window(nullptr), renderer(nullptr), width(width), height(height) {
	window = SDL_CreateWindow(title, width, height, 0);
	if (window == nullptr) {
		cout << "Window failed to initialize. Error " << SDL_GetError() << endl;
	}
	else {
		renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) {
			cout << "Renderer failed to initialize. Error " << SDL_GetError() << endl;
		} else if (TTF_Init() == -1) {
			cout << "Failed to initialize TTF. Error " << TTF_GetError() << endl;
		} else {
			font = TTF_OpenFont("res/ui_font.ttf", 16);
			if (font == nullptr) {
				cout << "Failed to load font. Error " << TTF_GetError() << endl;
			}
		}
		if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
			cout << "Failed to initialize IMG. Error " << SDL_GetError() << endl;
		} else {
			preyTexture = IMG_LoadTexture(renderer, "res/prey.png");
			hunterTexture = IMG_LoadTexture(renderer, "res/hunter.png");
		}
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
}

RenderWindow::~RenderWindow() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_Quit();
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
		if (creaturePool[i]->isAlive()) {
			creaturePool[i]->update(this->width, this->height);
			this->drawCreature(creaturePool[i]);
		}
	}

	Food** foodSources = generation->getFoodSources();
	for (int i = 0; i < generation->getNoFoodSources(); i++) {
		this->drawFoodSource(foodSources[i]);
	}
	this->checkCollision(generation);
	this->checkCreaturesCollision(generation);

	string populationSize = "Population: " + to_string(generation->getNoCreatures());
	string generationNumber = "Generation: " + to_string(generation->getGenerationNumber());
	string elapsedTime = "Elapsed time: " + to_string(generation->getElapsedTime());

	drawText(populationSize, 15, 15);
	drawText(generationNumber, 15, 30);
	drawText(elapsedTime, 15, 45);

	generation->updateElapsedTime();
}