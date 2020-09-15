#ifndef GAMEOFLIFE_GRID_H
#define GAMEOFLIFE_GRID_H

#include "Noncopyable.h"
#include <cassert>

namespace gameOfLife {
    class Pattern;

    class Grid : private Noncopyable {

    public:
        Grid(int width, int height);

        ~Grid();

    public:
        int Width() const { return width_; }

        int Height() const { return height_; }

    public:
        bool Cell(int x, int y) const {
            assert((x >= -1) && (x <= width_) &&
                   (y >= -1) && (y <= height_));
            return rows_[y + 1][x + 1];
        }

        void SetCell(int x, int y, bool value = true) {
            assert((x >= 0) && (x < width_) && (y >= 0) && (y < height_));
            rows_[y + 1][x + 1] = value;
        }

        void SetPattern(int x, int y, const Pattern &pattern);

    public:
        void Reset();

        void Randomize(int densityFactor = 7);

        int NeighbourCount(int x, int y) const;

    public:
        int width_;
        int height_;
        bool* cells_;
        bool** rows_;
    };
}


#endif //GAMEOFLIFE_GRID_H
