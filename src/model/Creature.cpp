#include "model/Creature.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

#define SPEED_WEIGHT 0.5
#define SIZE_WEIGHT 0.3
#define STRENGTH_WEIGHT 0.2

void Creature::generatePointTowards() {
    xTowards = (rand() % 2 == 0) ? x + rand() % 100 : x - rand() % 100;
    yTowards = (rand() % 2 == 0) ? y + rand() % 100 : y - rand() % 100;
}

void Creature::bindCreatureToArea(int width, int height) {
    if (xTowards < 0) {
        xTowards = 0;
    } else if (xTowards > width) {
        xTowards = width;
    }
    if (yTowards < 0) {
        yTowards = 0;
    } else if (yTowards > height) {
        yTowards = height;
    }
}

// Constructors
Creature::Creature(float x, float y) : x(x), y(y), foodConsumed(0), alive(true) {
    generatePointTowards();
    this->chromosome = Chromosome::generate();
    foodNeeded = chromosome->getSpeed() * SPEED_WEIGHT + chromosome->getSize() * SIZE_WEIGHT / SIZE_MODIFIER + chromosome->getStrength() * STRENGTH_WEIGHT;
}

Creature::Creature(float x, float y, Chromosome* chromosome) : x(x), y(y), foodConsumed(0), chromosome(chromosome), alive(true) {
    generatePointTowards();
    foodNeeded = chromosome->getSpeed() * SPEED_WEIGHT + chromosome->getSize() * SIZE_WEIGHT / SIZE_MODIFIER + chromosome->getStrength() * STRENGTH_WEIGHT;
}

Creature::~Creature() {
    delete chromosome;
}

// Getters
float Creature::getX() {
    return this->x;
}               

float Creature::getY() {
    return this->y;
}

Chromosome* Creature::getChromosome() {
    return this->chromosome;
}

float Creature::getFoodNeeded() {
    return this->foodNeeded;
}

float Creature::getFoodConsumed() {
    return this->foodConsumed;
}

bool Creature::isAlive() {
    return alive;
}

void Creature::kill() {
    x = -100;
    y = -100;
    alive = false;
}

// Setters
void Creature::setX(float x) {
    this->x = x;
}

void Creature::setY(float y) {
    this->y = y;
}

void Creature::update(int width, int height) {
    float dx = xTowards - x;
    float dy = yTowards - y;
    float distance = sqrt(dx * dx + dy * dy);

    float time = distance / chromosome->getSpeed();

    if (abs(x - xTowards) >= 1.0f) {
        x = x + dx / time;
        y = y + dy / time;
    } else {
        generatePointTowards();
        bindCreatureToArea(width, height);
    }
}

void Creature::consumeFood() {
    this->foodConsumed += 0.01;
}