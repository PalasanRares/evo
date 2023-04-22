#pragma once

class Creature {
private:
    float x;
    float y;
    float speed;

    float xTowards;
    float yTowards;

    void generatePointTowards();

public:
    // Constructors
    Creature(float x, float y, float speed);

    // Getters
    float getX();
    float getY();
    float getSpeed();

    // Setters
    void setX(float x);
    void setY(float y);
    void setSpeed(float speed);

    void update();
};
