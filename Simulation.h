//
// Created by lukasz on 28/9/20.
//

#ifndef GAMEOFLIFE_SIMULATION_H
#define GAMEOFLIFE_SIMULATION_H

#include "Noncopyable.h"
#include <cassert>

namespace gameOfLife {

    class Display;
    class Grid;
    class GridDrawer;
    class Pattern;

    class Simulation: private Noncopyable {
    public:
        Simulation(int cellsWide, int cellsHigh, int cellWidth, int cellHeight);
        ~Simulation();

    public:
        const gameOfLife::Display& Display() const { return *display_;}
        GridDrawer& Drawer() const { return *drawer_; }

    public:
        void Reset();
        void Reset(const Pattern& pattern);
        void Randomize(int densityFactor=7);
        bool Cell(int x, int y) const;
        void SetCell(int x, int y, bool cell);
        void SetPattern(int x, int y, const Pattern& pattern);
        void Draw();
        void Step();

    private:
        void ProcessCells();
        void SwapGrids();

    private:
        Grid* grid1_;
        Grid* grid2_;
        Grid* activeGrid_;
        Grid* temporaryGrid_;
        gameOfLife::Display* display_;
        GridDrawer* drawer_;
    };
}


#endif //GAMEOFLIFE_SIMULATION_H
