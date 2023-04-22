#pragma once

#include "model/Creature.hpp"
#include "model/Food.hpp"

#include "SDL.h"

#include <cstdlib>

class Generation {
private:
    int generationNumber;
    Creature** creaturePool;
    Food** foodSources;
    int noCreatures;
    int noFoodSources;

    Uint64 startTime;
    int elapsedTime;

    static bool sortByFoodConsumed(Creature* creature1, Creature* creature2);

public:
    Generation(int width, int height, int noCreatures, int noFoodSources);
    Generation(int width, int height, int noCreatures, int noFoodSources, Creature** creaturePool, int generationNumber);

    ~Generation();

    int getGenerationNumber();
    Creature** getCreaturePool();
    Food** getFoodSources();
    int getNoCreatures();
    int getNoFoodSources();
    int getElapsedTime();

    void updateElapsedTime();
    void killCreature(int index);

    Generation* createNewGeneration(int width, int height);
};