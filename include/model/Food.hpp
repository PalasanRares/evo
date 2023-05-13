#pragma once

class Food {
private:
    float x;
    float y;
    float capacity;

public:
    Food(float x, float y, float capacity);

    float getX();
    float getY();
    float getCapacity();

    void decreaseCapacity();
};