#ifndef _DRAWING_UTILS_HPP_
#define _DRAWING_UTILS_HPP_

#include "SDL3/SDL_render.h"

void SDL_DrawCircle(SDL_Renderer* renderer, float x, float y, float radius);

void SDL_FillCircle(SDL_Renderer* renderer, float x, float y, float radius);

#endif
