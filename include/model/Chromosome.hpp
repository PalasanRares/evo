#pragma once

class Chromosome {
private:
    float speed;
    float strength;
    float size;

    Chromosome(float speed, float strength, float size);

public:
    static Chromosome* generate();

    float getSpeed();
    float getStrength();
    float getSize();
};
