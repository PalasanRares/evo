#pragma once

#include "model/Creature.hpp"

class Generation {
private:
    Creature** creaturePool;
    int noCreatures;

public:
    Generation(int width, int height, int noCreatures);

    Creature** getCreaturePool();
    int getNoCreatures();
};