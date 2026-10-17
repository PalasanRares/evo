#include "SDL3/SDL.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <iostream>
#include <cstdlib>

#define SDL_MAIN_USE_CALLBACKS
#include "SDL3/SDL_main.h"

#include "RenderWindow.hpp"
#include "model/Creature.hpp"
#include "service/Generation.hpp"

#define GENERATION_TIME 30

#define MAJOR 0
#define MINOR 1
#define PATCH 0

const char* title = "Evo 0.1.0";
const int width = 1280;
const int height = 720;

RenderWindow* renderWindow;
Generation* generation;

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
	renderWindow = new RenderWindow(title, width, height);

	generation = new Generation(width, height, 20, 10);

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
	Uint64 start = SDL_GetPerformanceCounter();

	renderWindow->clear();

	renderWindow->renderGeneration(generation);

	renderWindow->display();

	if (generation->getElapsedTime() > GENERATION_TIME) {
		Generation* oldGeneration = generation;
		generation = generation->createNewGeneration(width, height);
		delete oldGeneration;
	}

	Uint64 end = SDL_GetPerformanceCounter();
	float elapsedTime = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
	SDL_Delay(SDL_floor(33.333f - elapsedTime));

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    if (event->common.type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result) { 
	delete generation;
	delete renderWindow;
}
