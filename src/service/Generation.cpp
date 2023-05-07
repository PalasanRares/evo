#include "service/Generation.hpp"

#include <cstdlib>

using namespace std;

Generation::Generation(int width, int height, int noCreatures) : noCreatures(noCreatures) {
    this->creaturePool = new Creature*[noCreatures];
    for (int i = 0; i < noCreatures; i++) {
        this->creaturePool[i] = new Creature(rand() % width, rand() % height);
    }
}

Creature** Generation::getCreaturePool() {
    return this->creaturePool;
}

int Generation::getNoCreatures() {
    return this->noCreatures;
}