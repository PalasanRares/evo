#include "service/Generation.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

bool Generation::sortByFoodConsumed(Creature* creature1, Creature* creature2) {
    return creature1->getFoodConsumed() > creature2->getFoodConsumed();
}

Generation::Generation(int width, int height, int noCreatures, int noFoodSources) : noCreatures(noCreatures), noFoodSources(noFoodSources), generationNumber(0) {
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

Generation::Generation(int width, int height, int noCreatures, int noFoodSources, Creature** creaturePool, int generationNumber) : noCreatures(noCreatures), noFoodSources(noFoodSources), creaturePool(creaturePool), generationNumber(generationNumber) {
    foodSources = new Food*[noFoodSources];
    for (int i = 0; i < noFoodSources; i++) {
        foodSources[i] = new Food(rand() % width, rand() % height, 100);
    }
    startTime = SDL_GetPerformanceCounter();
}

Generation::~Generation() {
    delete[] creaturePool;
    delete[] foodSources;
}

int Generation::getGenerationNumber() {
    return generationNumber;
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

int Generation::getElapsedTime() {
    return this->elapsedTime / 1000;
}

void Generation::updateElapsedTime() {
    Uint64 endTime = SDL_GetPerformanceCounter();
	elapsedTime = (endTime - startTime) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
}

void Generation::killCreature(int index) {
    creaturePool[index]->kill();
}

Generation* Generation::createNewGeneration(int width, int height) {
    vector<Creature*> newCreaturePool;
    // sort creatures by food consumed
    vector<Creature*> creatures(creaturePool, creaturePool + noCreatures);
    sort(creatures.begin(), creatures.end(), sortByFoodConsumed);

    // filter surviving creatures
    vector<Creature*> survivingCreatures;
    copy_if(creatures.begin(), creatures.end(), back_inserter(survivingCreatures), [](Creature* c) {
        return c->getFoodConsumed() > 0;
    });
    size_t survivingNumber = survivingCreatures.size();
    if (survivingNumber % 2 == 1) {
        survivingCreatures.pop_back();
        survivingNumber -= 1;
    }

    // crossover their genes
    for (int index = 0; index < survivingNumber - 1; index += 2) {
        float multiplicityCombined = survivingCreatures.at(index)->getChromosome()->getMultiplicity() / survivingCreatures.at(index + 1)->getChromosome()->getMultiplicity();
        int noOffsprings;
        if (multiplicityCombined < 0.25) {
            noOffsprings = 1;
        } else if (multiplicityCombined < 0.5) {
            noOffsprings = 2;
        } else if (multiplicityCombined < 0.75) {
            noOffsprings = 3;
        } else {
            noOffsprings = 4;
        }
        for (int i = 0; i < noOffsprings; i++) {
            Chromosome* newChromosome = Chromosome::crossover(survivingCreatures.at(index)->getChromosome(), survivingCreatures.at(index + 1)->getChromosome());
            // mutate offspring genes
            newChromosome->mutate();
            newCreaturePool.push_back(new Creature(rand() % width, rand() % height, newChromosome));
        }
    }
    Creature** newCreaturePoolArray = new Creature*[newCreaturePool.size()];
    copy(newCreaturePool.begin(), newCreaturePool.end(), newCreaturePoolArray);
    return new Generation(width, height, newCreaturePool.size(), noFoodSources, newCreaturePoolArray, generationNumber + 1);
}