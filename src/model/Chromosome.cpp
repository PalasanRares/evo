#include "model/Chromosome.hpp"

#include <cstdlib>

using namespace std;

void Chromosome::generateColor() {
    this->color.r = this->speed * 255;
    this->color.g = this->size * 255 / SIZE_MODIFIER;
    this->color.b = this->strength * 255;
}

Chromosome::Chromosome(float speed, float strength, float size) : speed(speed), strength(strength), size(size) {
    generateColor();
}

Chromosome* Chromosome::generate() {
    float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float strength = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float size = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * SIZE_MODIFIER;
    return new Chromosome(speed, strength, size);
}

Chromosome* Chromosome::crossover(Chromosome* first, Chromosome* second) {
    // speed and size come from first, strength and multiplicity (eventually) come from second
    return new Chromosome(first->getSpeed(), second->getStrength(), first->getSize());
}

float Chromosome::getSpeed() {
    return this->speed;
}

float Chromosome::getStrength() {
    return this->strength;
}

float Chromosome::getSize() {
    return this->size;
}

Color Chromosome::getColor() {
    return this->color;
}

void Chromosome::mutate() {
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < MUTATION_CHANCE) {
        if (rand() % 2 == 0) {
            speed += 0.1;
        } else {
            speed -= 0.1;
        }
    }
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < MUTATION_CHANCE) {
        if (rand() % 2 == 0) {
            strength += 0.1;
        } else {
            strength -= 0.1;
        }
    }
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < MUTATION_CHANCE) {
        if (rand() % 2 == 0) {
            size += 0.1;
        } else {
            size -= 0.1;
        }
    }
}