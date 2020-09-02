#include <SDL2/SDL.h>

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <utility>
#include <iostream>

#if defined(_WIN32) && defined(_DEBUG)
#include <crtdbg.h>
#endif

constexpr int displayWidth = 640;
constexpr int displayHeight = 480;
constexpr int cellWidth = 10;
constexpr int cellHeight = 10;
constexpr int cellsWide = displayWidth / cellWidth;
constexpr int cellsHigh = displayHeight / cellHeight;

constexpr Uint32 black = 0xFF000000;
constexpr Uint32 gray = 0xFF101010;
constexpr Uint32 white = 0xFFFFFFFF;

void SetCell(bool cells[cellsWide + 2][cellsHigh + 2], int x, int y, bool value = true) {
    assert(x >= 0 && x < cellsWide + 1);
    assert(y >= 0 && y < cellsHigh + 1);

    cells[x + 1][y + 1] = value;
}

void ResetCells(bool cells[cellsWide + 2][cellsHigh + 2], bool value = false) {
    for (int x = 0; x < cellsWide + 2; ++x) {
        for (int y = 0; y < cellsHigh + 1; ++y) {
            cells[x][y] = value;
        }
    }
}

int AliveNeighbourCount(int x, int y, bool cells[cellsWide + 2][cellsHigh + 2]) {
    int nc = 0;

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (!(dx == 0 && dy == 0)) {
                if (cells[x + dx][y + dy]) {
                    ++nc;
                }
            }
        }
    }

    return nc;
}

void ProcessCells(bool cells[cellsWide + 2][cellsHigh + 2], bool cells2[cellsWide + 2][cellsHigh + 2]) {
    for (int x = 1; x <= cellsWide; ++x) {
        for (int y = 1; y <= cellsHigh; ++y) {
            const int nc = AliveNeighbourCount(x, y, cells);

            if (cells[x][y] && (nc == 2 || nc == 3)) {
                cells2[x][y] = true;
            } else if (!cells[x][y] && nc == 3) {
                cells2[x][y] = true;
            } else {
                cells2[x][y] = false;
            }
        }
    }
}

void RandomizeCells(bool cells[cellsWide + 2][cellsHigh + 2]) {
    for (int x = 0; x <= cellsWide; ++x) {
        for (int y = 0; y <= cellsHigh; ++y) {
            SetCell(cells, x, y, (rand() % 3 == 0 ? true : false));
        }
    }
}

inline void Clear(Uint32 *pixels, Uint32 argb) {
    assert(pixels);

    int i = displayWidth * displayHeight;

    while (i--)
        *pixels++ = argb;
}

inline void DrawPixel(Uint32 *pixels, int x, int y, Uint32 argb) {
    assert(pixels);
    assert(x >= 0 && x < displayWidth && y >= 0 && y < displayHeight);

    pixels[y * displayWidth + x] = argb;
}

inline void DrawHLine(Uint32 *pixels, int x1, int x2, int y, int argb) {
    assert(pixels);
    assert(x1 >= 0 && x1 < displayWidth && x2 >= 0 && x2 < displayWidth && y >= 0 && y < displayHeight);

    if (x1 > x2)
        std::swap(x1, x2);

    Uint32 offset = y * displayWidth + x1;
    pixels += offset;

    int i = x2 - x1 + 1;

    while (i--)
        *pixels++ = argb;
}

inline void DrawVLine(Uint32 *pixels, int x, int y1, int y2, int argb) {
    assert(pixels);
    assert(x >= 0 && x < displayWidth && y1 >= 0 && y1 < displayHeight && y2 >= 0 && y2 < displayHeight);

    if (y1 > y2)
        std::swap(y1, y2);

    Uint32 offset = y1 * displayWidth + x;
    pixels += offset;

    int i = y2 - y1 + 1;

    while (i--) {
        *pixels = argb;
        pixels += (Uint32) displayWidth;
    }
}

void FillRect(Uint32 *pixels, int x, int y, int w, int h, Uint32 argb) {
    for (const int y2 = y + h; y < y2; ++y) {
        DrawHLine(pixels, x, x + w - 1, y, argb);
    }
}

void DrawGrid(Uint32 *pixels, Uint32 argb) {
    for (int y = 0; y < displayHeight; y += cellHeight) {
        DrawHLine(pixels, 0, displayWidth - 1, y, argb);
    }
    for (int x = 0; x < displayWidth; x += cellWidth) {
        DrawVLine(pixels, x, 0, displayHeight - 1, argb);
    }
}

void DrawCells(Uint32 *pixels, bool cells[cellsWide + 2][cellsHigh + 2], Uint32 argb) {
    for (int x = 0; x < cellsWide; ++x) {
        for (int y = 0; y < cellsHigh; ++y) {
            if (cells[x + 1][y + 1]) {
                FillRect(pixels, x * cellWidth, y * cellHeight, cellWidth, cellHeight, argb);
            }
        }
    }
}

extern "C" int main(int argc, char *argv[]) {
    std::cout << "Game started!" << std::endl;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

    SDL_Window *window =
            SDL_CreateWindow("Game of life",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             displayWidth,
                             displayHeight,
                             SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer =
            SDL_CreateRenderer(window,
                               -1,
                               SDL_RENDERER_ACCELERATED);
    SDL_Texture *texture =
            SDL_CreateTexture(renderer,
                              SDL_PIXELFORMAT_ARGB8888,
                              SDL_TEXTUREACCESS_STATIC,
                              displayWidth,
                              displayHeight);

    Uint32 *pixels = new Uint32[displayWidth * displayHeight];

    SDL_bool quit = SDL_FALSE;
    SDL_Event event = {0};
    int fps = 60;

    bool cells1[cellsWide + 2][cellsHigh + 2];
    bool cells2[cellsWide + 2][cellsHigh + 2];

    ResetCells(cells1);
    ResetCells(cells2);

    RandomizeCells(cells1);

    Uint32 cellColor = white;
    bool stop = false;
    bool drawGrid = true;
    int step = 0;

    while (!quit) {
        Uint32 start = SDL_GetTicks();

        Clear(pixels, black);

        if (stop) {
            DrawCells(pixels, cells1, cellColor);
        } else {
            if ((step % 2) == 0) {

                ResetCells(cells2);
                ProcessCells(cells1, cells2);
                DrawCells(pixels, cells2, cellColor);
            } else {
                ResetCells(cells1);
                ProcessCells(cells2, cells1);
                DrawCells(pixels, cells1, cellColor);
            }
            ++step;
        }

        if (drawGrid) {
            DrawGrid(pixels, gray);
        }

        SDL_UpdateTexture(texture, NULL, pixels, displayWidth * sizeof(Uint32));

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = SDL_TRUE;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_SPACE)
                        stop = SDL_TRUE;
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        quit = SDL_TRUE;
                    break;
                default:
                    break;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);

        Uint32 end = SDL_GetTicks();

        int delay = 1000 / fps - (end - start);

        if (delay > 0) {
            SDL_Delay(delay);
        }
    }

    delete[] pixels;

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    std::cout << "Game over" << std::endl;
    return 0;
}

