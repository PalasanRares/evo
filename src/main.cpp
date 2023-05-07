#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <cstdlib>

#include "RenderWindow.hpp"
#include "model/Creature.hpp"

using namespace std;

int main(int argc, char** argv) {
	const char* title = "Evo 0.0.2";
	const int width = 1000;
	const int height = 500;
	RenderWindow* window = new RenderWindow(title, width, height);
	bool running = true;

	SDL_Event event;

	vector<Creature*> creatures;
	for (int i = 0; i < 18; i++) {
		creatures.push_back(new Creature(rand() % width, rand() % height));
	}

	while (running) {
		uint32_t time = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		window->clear();

		for (int i = 0; i < 18; i++) {
			creatures.at(i)->update();
			window->drawCreature(creatures.at(i));
		}

		window->display();

		if ((SDL_GetTicks() - time) < 10) {
			SDL_Delay(10);
		}
	}

	delete window;
	return 0;
}
