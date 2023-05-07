#include "model/Chromosome.hpp"

#include <cstdlib>

using namespace std;

Chromosome::Chromosome(float speed, float strength, float size) : speed(speed), strength(strength), size(size) {}

Chromosome* Chromosome::generate() {
    float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float strength = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float size = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    return new Chromosome(speed, strength, size);
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