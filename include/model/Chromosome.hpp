#pragma once

#include "utils/Color.hpp"

#define SIZE_MODIFIER 5
#define MUTATION_CHANCE 0.1

class Chromosome {
private:
    float speed;
    float strength;
    float size;
    float multiplicity;
    Color color;

    void generateColor();

    Chromosome(float speed, float strength, float size, float multiplicity);

public:
    static Chromosome* generate();
    static Chromosome* crossover(Chromosome* first, Chromosome* second);

    float getSpeed();
    float getStrength();
    float getSize();
    float getMultiplicity();
    Color getColor();

    void mutate();
};
