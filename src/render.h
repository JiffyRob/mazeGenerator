#include "SDL2/SDL.h"
#include <vector>
#include <filesystem>
#include "maze.h"
#include "common.h"

using namespace std;

int dumpTexture(SDL_Renderer* renderer, SDL_Texture* &tex, string path) {
    if (tex != nullptr) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
    SDL_Surface* surf = nullptr;
    
    surf = SDL_LoadBMP(path.c_str());
    if (surf == nullptr) {
        printf( "Unable to load surface from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return 0;
    }
    tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (tex == nullptr) {
        printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        return 0;
    }
    SDL_FreeSurface(surf);
    surf = nullptr;
    return 1;
}

int dumpRenderer(SDL_Window* window, SDL_Renderer* &renderer, int index=-1) {
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    renderer = SDL_CreateRenderer(window, index, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        printf("Unable to create renderer at index %s! SDL Error: %s\n", index, SDL_GetError());
        return 0;
    }
    return 1;
}

void dumpFrameRect(SDL_Rect &rect, int index, int frameWidth = 3, int frameHeight = 3, int columns = 16) {
    int row = index / columns;
    int col = index % columns;
    rect.x = col * frameWidth;
    rect.y = row * frameHeight;
    rect.w = frameWidth;
    rect.h = frameHeight;
}

void dumpCellRect(SDL_Rect &rect, int x, int y) {
    rect.w = 3;
    rect.h = 3;
    rect.x = x * 3;
    rect.y = y * 3;
}

class MazeRenderer {
    public:
        MazeRenderer(SDL_Window* window) {
            // mazing
            this->width = 5;
            this->height = 5;
            this->maze = Maze();
            // drawing
            cout << filesystem::current_path();
            this->renderer = nullptr;
            this->mazeTexture = nullptr;
            dumpRenderer(window, this->renderer);
            dumpTexture(this->renderer, this->mazeTexture, "assets/basic_maze.bmp");
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        }

        void reset() {
            height = (rand() % 11 + 1) * 2;
            width = (rand() % 17 + 1) * 3;
            maze.prep(width, height);
        }

        void update() {
            if (maze.generate()) {
                reset();
            }
        }

        void render() {
            SDL_RenderClear(renderer);
            int currentX = maze.getCurrentX();
            int currentY = maze.getCurrentY();
            SDL_Rect srcrect;
            SDL_Rect dstrect;
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    dumpFrameRect(srcrect, maze.getAt(x, y));
                    dumpCellRect(dstrect, x, y);
                    SDL_RenderCopy(renderer, mazeTexture, &srcrect, &dstrect);
                }
            }
            SDL_RenderPresent(renderer);
        }

        void close() {
            cout << "close maze\n";
            maze.close();
            cout << "destroy texture\n";
            SDL_DestroyTexture(mazeTexture);
            mazeTexture = nullptr;
            cout << "destory renderer\n";
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }

    private:
        SDL_Renderer* renderer;
        SDL_Texture* mazeTexture;
        int width;
        int height;
        Maze maze;
};