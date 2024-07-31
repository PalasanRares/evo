#include "model/Chromosome.hpp"

#include <cstdlib>

Chromosome* Chromosome::generate() {
    float speed = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float strength = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float size = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * SIZE_MODIFIER;
    float multiplicity = static_cast <float> ((rand())) / static_cast <float> (RAND_MAX);
    bool isPredator = rand() % 2 == 1 ? true : false;

    Chromosome* result = new Chromosome();
    result->speed = speed;
    result->strength = strength;
    result->size = size;
    result->multiplicity = multiplicity;
    result->isPredator = isPredator;
    result->generateColor();

    return result;
}

// TODO Change this not to be secvential
Chromosome* Chromosome::crossover(Chromosome* other) {
    bool predator = isPredator && other->isPredator;
    
    Chromosome* result = new Chromosome();
    result->speed = speed;
    result->strength = other->strength;
    result->size = size;
    result->multiplicity = other->multiplicity;
    result->isPredator = predator;
    result->generateColor();

    return result;
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
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < MUTATION_CHANCE) {
        if (rand() % 2 == 0) {
            multiplicity += 0.1;
        } else {
            multiplicity -= 0.1;
        }
    }
    if (static_cast <float> (rand()) / static_cast <float> (RAND_MAX) < MUTATION_CHANCE) {
        isPredator = !isPredator;
    }
}

void Chromosome::generateColor() {
    color.r = speed * 255;
    color.g = size * 255 / SIZE_MODIFIER;
    color.b = size * 255;
}
