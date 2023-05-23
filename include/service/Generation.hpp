#pragma once

#include "model/Creature.hpp"
#include "model/Food.hpp"

#include "SDL.h"

#include <cstdlib>

class Generation {
private:
    Creature** creaturePool;
    Food** foodSources;
    int noCreatures;
    int noFoodSources;

    Uint64 startTime;
    float elapsedTime;

    static bool sortByFoodConsumed(Creature* creature1, Creature* creature2);

public:
    Generation(int width, int height, int noCreatures, int noFoodSources);
    Generation(int width, int height, int noCreatures, int noFoodSources, Creature** creaturePool);

    Creature** getCreaturePool();
    Food** getFoodSources();
    int getNoCreatures();
    int getNoFoodSources();
    float getElapsedTime();

    void updateElapsedTime();

    Generation* createNewGeneration(int width, int height);
};