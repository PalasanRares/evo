#ifndef _CHROMOSOME_HPP_
#define _CHROMOSOME_HPP_

#include "utils/Color.hpp"

#define SIZE_MODIFIER 25
#define MUTATION_CHANCE 0.1

struct Chromosome {
    float speed;
    float strength;
    float size;
    float multiplicity;

    bool isPredator;

    Color color;

    static Chromosome* generate();

    Chromosome* crossover(Chromosome* other);

    void mutate();
    void generateColor();
};

#endif
