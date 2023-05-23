#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <cstdlib>

#include "RenderWindow.hpp"
#include "model/Creature.hpp"
#include "service/Generation.hpp"

using namespace std;

int main(int argc, char** argv) {
	const char* title = "Evo 0.0.5";
	const int width = 1000;
	const int height = 500;
	RenderWindow* window = new RenderWindow(title, width, height);
	bool running = true;

	SDL_Event event;

	Generation* generation = new Generation(width, height, 20, 10);

	while (running) {
		Uint64 start = SDL_GetPerformanceCounter();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		window->clear();

		window->renderGeneration(generation);

		window->display();

		Uint64 end = SDL_GetPerformanceCounter();
		float elapsedTime = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
		SDL_Delay(floor(33.333f - elapsedTime));
	}

	delete window;
	return 0;
}
