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