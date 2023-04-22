#include "model/Creature.hpp"

#include <cstdlib>
#include <cmath>
#include <iostream>

void Creature::generatePointTowards() {
    xTowards = (rand() % 2 == 0) ? x + rand() % 100 : x - rand() % 100;
    yTowards = (rand() % 2 == 0) ? y + rand() % 100 : y - rand() % 100;
}

// Constructors
Creature::Creature(float x, float y, float speed) : x(x), y(y), speed(speed) {
    generatePointTowards();
}

// Getters
float Creature::getX() {
    return this->x;
}               

float Creature::getY() {
    return this->y;
}

float Creature::getSpeed() {
    return this->speed;
}

// Setters
void Creature::setX(float x) {
    this->x = x;
}

void Creature::setY(float y) {
    this->y = y;
}

void Creature::setSpeed(float speed) {
    this->speed = speed;
}

void Creature::update() {
    float dx = xTowards - x;
    float dy = yTowards - y;
    float distance = sqrt(dx * dx + dy * dy);

    float time = distance / speed;

    if (abs(x - xTowards) >= 0.1f) {
        x = x + dx / time;
        y = y + dy / time;
    } else {
        generatePointTowards();
    }
}