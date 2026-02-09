
#include <iostream>
#include <SDL.h>

int main(int argc, char **argv) {
    std::cout << "hello world!" << std::endl;

    if (::SDL_Init(SDL_INIT_VIDEO) < 0) {
        ::std::cout << "SDL_Init Error: " << ::SDL_GetError() << ::std::endl;
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("Xmake Cross Platform", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

    if (!window) {
        return -1;
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;
        }
        
        // 简单的清屏，证明程序在跑
        SDL_Surface* screen = SDL_GetWindowSurface(window);
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 100, 149, 237));
        SDL_UpdateWindowSurface(window);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
