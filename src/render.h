#include "SDL2/SDL.h"
#include <vector>
#include <filesystem>
#include "maze.h"
#include "common.h"

const int BACKGROUND_COLORS[10][3] = { // kinda hacky but whatever
    {0, 0, 0},
    {178, 16, 48},
    {162, 48, 0},
    {255, 162, 0},
    {73, 170, 16},
    {48, 81, 140},
    {97, 16, 172},
    {154, 32, 121},
    {97, 162, 255},
    {121, 65, 0},
}; 

int dumpTexture(SDL_Renderer* renderer, SDL_Texture* &tex, std::string path) {
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

void dumpFrameRect(SDL_Rect &rect, int index, int frameWidth = 3, int frameHeight = 3, int columns = 17) {
    int row = index / columns;
    int col = index % columns;
    rect.x = col * frameWidth;
    rect.y = row * frameHeight;
    rect.w = frameWidth;
    rect.h = frameHeight;
}

class MazeRenderer {
    public:
        MazeRenderer(SDL_Window* window) {
            // mazing
            this->width = 5;
            this->height = 5;
            this->maze = Maze();
            // drawing
            std::cout << std::filesystem::current_path();
            this->color = -1; // on first reset it will be set to 0
            this->renderer = nullptr;
            this->mazeTexture = nullptr;
            this->window = window;
            dumpRenderer(window, this->renderer);
            dumpTexture(this->renderer, this->mazeTexture, "assets/basic_maze.bmp");
        }

        void reset() {
            height = (rand() % 11 + 1) * 2;
            width = (rand() % 17 + 1) * 3;
            maze.prep(width, height);
            color += 1;
            if (color > 9) {
                color = 0;
            }
            SDL_SetRenderDrawColor(renderer, BACKGROUND_COLORS[color][0], BACKGROUND_COLORS[color][1], BACKGROUND_COLORS[color][2], 255);
        }

        void update() {
            if (maze.generate()) {
                reset();
            }
        }

        SDL_Rect cellRect(int x, int y) {
            SDL_Rect rect;
            int screenWidth;
            int screenHeight;
            SDL_GetWindowSize(window, &screenWidth, &screenHeight);
            int cellWidth = screenWidth / width;
            int cellHeight = screenHeight / height;
            rect.x = x * cellWidth;
            rect.y = y * cellHeight;
            rect.w = cellWidth;
            rect.h = cellHeight;
            return rect;
        }

        void render() {
            SDL_RenderClear(renderer);
            int currentX = maze.getCurrentX();
            int currentY = maze.getCurrentY();
            SDL_Rect srcrect;
            SDL_Rect dstrect;
            // draw maze
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    dumpFrameRect(srcrect, maze.getAt(x, y) + (color * 17));
                    SDL_Rect dstrect = cellRect(x, y);
                    SDL_RenderCopy(renderer, mazeTexture, &srcrect, &dstrect);
                }
            }
            // draw current cell
            dumpFrameRect(srcrect, 16 + (color * 17));
            dstrect = cellRect(currentX, currentY);
            SDL_RenderCopy(renderer, mazeTexture, &srcrect, &dstrect);
            SDL_RenderPresent(renderer);
        }

        void close() {
            std::cout << "close maze\n";
            maze.close();
            std::cout << "destroy texture\n";
            if (mazeTexture != nullptr) {
                SDL_DestroyTexture(mazeTexture);
            }
            mazeTexture = nullptr;
            std::cout << "destory renderer\n";
            if (renderer != nullptr) {
                SDL_DestroyRenderer(renderer);
            }
            renderer = nullptr;
        }

    private:
        SDL_Renderer* renderer;
        SDL_Texture* mazeTexture;
        SDL_Window* window;
        int width;
        int height;
        int color;
        Maze maze;
};