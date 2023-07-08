#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

#include "SDL.h"

struct Transform {
    SDL_Point position;

    float rotation;

    SDL_Point scale;

    Transform(
        const SDL_Point& position = {0, 0}, 
        float rotation = 0.0f, 
        const SDL_Point& scale = {1, 1}
    ) : position(position), rotation(rotation), scale(scale) {}
}

#endif
