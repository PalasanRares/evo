#include "model/Food.hpp"

Food::Food(float x, float y, float capacity) : x(x), y(y), capacity(capacity) {}

float Food::getX() {
    return this->x;
}

float Food::getY() {
    return this->y;
}

float Food::getCapacity() {
    return this->capacity;
}

void Food::decreaseCapacity() {
    this->capacity -= 1;
}