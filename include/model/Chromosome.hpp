#pragma once

#include "utils/Color.hpp"

class Chromosome {
private:
    float speed;
    float strength;
    float size;
    Color color;

    void generateColor();

    Chromosome(float speed, float strength, float size);

public:
    static Chromosome* generate();

    float getSpeed();
    float getStrength();
    float getSize();
    Color getColor();
};
