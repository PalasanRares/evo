#include "service/Generation.hpp"

#include <cstdlib>

using namespace std;

Generation::Generation(int width, int height, int noCreatures, int noFoodSources) : noCreatures(noCreatures), noFoodSources(noFoodSources) {
    this->creaturePool = new Creature*[noCreatures];
    for (int i = 0; i < noCreatures; i++) {
        this->creaturePool[i] = new Creature(rand() % width, rand() % height);
    }

    this->foodSources = new Food*[noFoodSources];
    for (int i = 0; i < noFoodSources; i++) {
        this->foodSources[i] = new Food(rand() % width, rand() % height, 100);
    }
}

Creature** Generation::getCreaturePool() {
    return this->creaturePool;
}

Food** Generation::getFoodSources() {
    return this->foodSources;
}

int Generation::getNoCreatures() {
    return this->noCreatures;
}

int Generation::getNoFoodSources() {
    return this->noFoodSources;
}