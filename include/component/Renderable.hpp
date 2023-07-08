#ifndef _RENDERABLE_HPP_
#define _RENDERABLE_HPP_

#include "SDL_image.h"
#include "Transform.hpp"

struct Renderable {
    SDL_Texture* texture;

    Transform* transform;

    Renderable(
        SDL_Texture* texture,
        Transform* transform
    ) : texture(texture), transform(transform) {}
}

#endif