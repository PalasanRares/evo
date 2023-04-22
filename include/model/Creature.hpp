#pragma once

#include "model/Chromosome.hpp"

class Creature {
private:
    float x;
    float y;
    Chromosome* chromosome;

    bool alive;

    float foodNeeded;
    float foodConsumed;

    float xTowards;
    float yTowards;

    void generatePointTowards();
    void bindCreatureToArea(int width, int height);

public:
    // Constructors
    Creature(float x, float y);
    Creature(float x, float y, Chromosome* chromosome);
    ~Creature();

    // Getters
    float getX();
    float getY();
    Chromosome* getChromosome();
    float getFoodNeeded();
    float getFoodConsumed();

    bool isAlive();
    void kill();

    // Setters
    void setX(float x);
    void setY(float y);
    
    void update(int width, int height);
    void consumeFood();
};
