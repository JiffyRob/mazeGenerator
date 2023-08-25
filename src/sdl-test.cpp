#include <iostream>
#include <SDL2/SDL.h>
#include "common.h"
#include "render.h"

using namespace std;

bool init(SDL_Window* &window) {
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if(window == NULL)
    {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    return true;
}

void handleEvents(bool &running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            running = false;
            break;
          }
        }
}

void close(SDL_Window* window) {
    SDL_DestroyWindow( window );
    window = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main() {
    SDL_Window* window = NULL;
    bool running = true;
    int now, elapsed;
    int* mouseX;
    int* mouseY;

    bool inited = init(window);
    if (!inited) {
        return 1;
    }

    srand(time(0));
    MazeRenderer maze = MazeRenderer(window);
    maze.reset();


    // main loop
    while (running) {
        // event handling
        handleEvents(running);
        // updating
        maze.update();
        // rendering
        maze.render();
        // framerate limiting (TODO)
        SDL_Delay(10);
    }
    maze.close();
    close(window);
    return 0;
}