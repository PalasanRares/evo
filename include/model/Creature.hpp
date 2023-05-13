#pragma once

#include "model/Chromosome.hpp"

class Creature {
private:
    float x;
    float y;
    Chromosome* chromosome;

    float xTowards;
    float yTowards;

    void generatePointTowards();
    void bindCreatureToArea(int width, int height);

public:
    // Constructors
    Creature(float x, float y);

    // Getters
    float getX();
    float getY();
    Chromosome* getChromosome();

    // Setters
    void setX(float x);
    void setY(float y);

    void update(int width, int height);
};
