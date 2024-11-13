#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include <ctime>
#include <cmath>

// circle
void SDL_RenderFillCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    // midpoint circle algorithm
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // Horizontal offset
            int dy = radius - h; // Vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("IMG_Init failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SusHeld Screen Saver",
                                           SDL_WINDOWPOS_CENTERED,
                                           SDL_WINDOWPOS_CENTERED,
                                           0, 0, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    // Load logo image
    SDL_Surface* logoSurface = IMG_Load("logo.png");
    if (!logoSurface) {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_SetWindowIcon(window, logoSurface);
    SDL_FreeSurface(logoSurface);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return 1;
    }

    std::srand(std::time(0));

    // Screen saver parameters
    int x = std::rand() % 1920;
    int y = std::rand() % 1080;
    int dx = (std::rand() % 2 == 0) ? 1 : -1;
    int dy = (std::rand() % 2 == 0) ? 1 : -1;
    int radius = 50;

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // bouncing circle
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillCircle(renderer, x, y, radius);

        // Update the position of the circle
        x += dx;
        y += dy;

        // Bounce the circle off the walls { Hardcoded for 1080p }
        if (x - radius < 0 || x + radius > 1920) {
            dx = -dx;
        }
        if (y - radius < 0 || y + radius > 1080) {
            dy = -dy;
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    
    return 0;
}
