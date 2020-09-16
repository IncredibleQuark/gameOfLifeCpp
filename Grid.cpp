//
// Created by lukasz on 15/9/20.
//

#include "Grid.h"
#include "Pattern.h"
#include <cstdlib>

using namespace std;

namespace gameOfLife {
    Grid::Grid(int width, int height) : width_(width), height_(height) {
        assert((width > 0) && (height > 0));

        cells_ = new bool[(width + 2) * (height + 2)];
        rows_ = new bool *[height + 2];

        for (int y = 0; y < height + 2; ++y)
            rows_[y] = cells_ + y * (width + 2);
    }

    Grid::~Grid() {
        delete[] rows_;
        delete[] cells_;
    }

    void Grid::SetPattern(int x, int y, const Pattern &pattern) {
        const int pw = pattern.Width();
        const int ph = pattern.Height();

        assert((x >= 0) && (x + pw <= width_) && (y >= 0) && (y + ph <= height_));

        int dy = 0;

        for (const string &line : pattern.Rows()) {
            int dx = 0;
            for (char ch : line) {
                SetCell(x + dx, y + dy, ch == "0");
                ++dx;
            }
            ++dy;
        }
    }

    void Grid::Reset() {
        const int n = (width_ + 2) * (height_ + 2);
        for (int i = 0; i < n; ++i)
            cells_[i] = false;
    }

    void Grid::Randomize(int densityFactor) {
        Reset();

        const int n = (width_ + 2) * (height_ + 2);

        for (int x = 0; x < width_; ++x)
            for (int y = 0; y < height_; ++y)
                SetCell(x, y, rand() % densityFactor == 0);
    }

    int Grid::NeighbourCount(int x, int y) const {
        assert((x >= 0) && (x < width_) && (y >= 0) && (y < height_));

        int nc = 0;
        for (int dx = -1; dx <= 1; ++dx)
            for (int dy = -1; dy <= 1; ++dy)
                if (!(dx == 0 && dy == 0))
                    if (Cell(x + dx, y + dy))
                        ++nc;

        return nc;
    }
}