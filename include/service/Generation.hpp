#pragma once

#include "model/Creature.hpp"
#include "model/Food.hpp"

class Generation {
private:
    Creature** creaturePool;
    Food** foodSources;
    int noCreatures;
    int noFoodSources;

public:
    Generation(int width, int height, int noCreatures, int noFoodSources);

    Creature** getCreaturePool();
    Food** getFoodSources();
    int getNoCreatures();
    int getNoFoodSources();
};