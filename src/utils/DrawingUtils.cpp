#include "DrawingUtils.hpp"

void SDL_DrawCircle(SDL_Renderer* renderer, float x, float y, float radius) {
    float offsetX = 0;
    float offsetY = radius;
    float determinant = radius - 1;

    while (offsetY >= offsetX) {
        SDL_RenderPoint(renderer, x + offsetX, y + offsetY);
        SDL_RenderPoint(renderer, x + offsetY, y + offsetX);
        SDL_RenderPoint(renderer, x - offsetX, y + offsetY);
        SDL_RenderPoint(renderer, x - offsetY, y + offsetX);
        SDL_RenderPoint(renderer, x + offsetX, y - offsetY);
        SDL_RenderPoint(renderer, x + offsetY, y - offsetX);
        SDL_RenderPoint(renderer, x - offsetX, y - offsetY);
        SDL_RenderPoint(renderer, x - offsetY, y - offsetX);

        if (determinant >= 2 * offsetX) {
            determinant -= 2 * offsetX + 1;
            offsetX += 1;
        } else if (determinant < 2 * (radius - offsetY)) {
            determinant += 2 * offsetY - 1;
            offsetY -= 1;
        } else {
            determinant += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}

void SDL_FillCircle(SDL_Renderer* renderer, float x, float y, float radius) {
    float offsetX = 0;
    float offsetY = radius;
    float determinant = radius - 1;

    while (offsetY >= offsetX) {
        SDL_RenderLine(renderer, x - offsetY, y + offsetX, x + offsetY, y + offsetX);
        SDL_RenderLine(renderer, x - offsetX, y + offsetY, x + offsetX, y + offsetY);
        SDL_RenderLine(renderer, x - offsetX, y - offsetY, x + offsetX, y - offsetY);
        SDL_RenderLine(renderer, x - offsetY, y - offsetX, x + offsetY, y - offsetX);

        if (determinant >= 2 * offsetX) {
            determinant -= 2 * offsetX + 1;
            offsetX += 1;
        } else if (determinant < 2 * (radius - offsetY)) {
            determinant += 2 * offsetY - 1;
            offsetY -= 1;
        } else {
            determinant += 2 * (offsetY - offsetX - 1);
            offsetY -= 1;
            offsetX += 1;
        }
    }
}
