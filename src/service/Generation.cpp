#include "service/Generation.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool Generation::sortByFoodConsumed(Creature* creature1, Creature* creature2) {
    return creature1->getFoodConsumed() > creature2->getFoodConsumed();
}

Generation::Generation(int width, int height, int noCreatures, int noFoodSources) : noCreatures(noCreatures), noFoodSources(noFoodSources) {
    this->creaturePool = new Creature*[noCreatures];
    for (int i = 0; i < noCreatures; i++) {
        this->creaturePool[i] = new Creature(rand() % width, rand() % height);
    }

    this->foodSources = new Food*[noFoodSources];
    for (int i = 0; i < noFoodSources; i++) {
        this->foodSources[i] = new Food(rand() % width, rand() % height, 100);
    }
    startTime = SDL_GetPerformanceCounter();
}

Generation::Generation(int width, int height, int noCreatures, int noFoodSources, Creature** creaturePool) : noCreatures(noCreatures), noFoodSources(noFoodSources), creaturePool(creaturePool) {
    foodSources = new Food*[noFoodSources];
    for (int i = 0; i < noFoodSources; i++) {
        foodSources[i] = new Food(rand() % width, rand() % height, 100);
    }
    startTime = SDL_GetPerformanceCounter();
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

float Generation::getElapsedTime() {
    return this->elapsedTime / 1000;
}

void Generation::updateElapsedTime() {
    Uint64 endTime = SDL_GetPerformanceCounter();
	elapsedTime = (endTime - startTime) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}

Generation* Generation::createNewGeneration(int width, int height) {
    vector<Creature*> newCreaturePool;
    // sort creatures by food consumed
    vector<Creature*> creatures(creaturePool, creaturePool + noCreatures);
    sort(creatures.begin(), creatures.end(), sortByFoodConsumed);

    // filter surviving creatures
    size_t survivingNumber = noCreatures * SURVIVING_CREATURES;
    if (survivingNumber % 2 == 1) {
        survivingNumber += 1;
    }
    vector<Creature*> survivingCreatures(creatures.begin(), creatures.begin() + survivingNumber);

    // // crossover their genes
    for (int index = 0; index < survivingNumber - 1; index += 2) {
        Chromosome* newChromosome = Chromosome::crossover(survivingCreatures.at(index)->getChromosome(), survivingCreatures.at(index + 1)->getChromosome());
        // mutate offspring genes
        newChromosome->mutate();
        newCreaturePool.push_back(new Creature(rand() % width, rand() % height, newChromosome));
    }
    Creature** newCreaturePoolArray;
    copy(newCreaturePool.begin(), newCreaturePool.end(), newCreaturePoolArray);
    return new Generation(width, height, newCreaturePool.size(), noFoodSources, newCreaturePoolArray);
}