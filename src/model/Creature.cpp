#include "model/Creature.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

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
Creature::Creature(float x, float y) : x(x), y(y) {
    generatePointTowards();
    this->chromosome = Chromosome::generate();
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

    if (abs(x - xTowards) >= 0.1f) {
        x = x + dx / time;
        y = y + dy / time;
    } else {
        generatePointTowards();
        bindCreatureToArea(width, height);
    }
}