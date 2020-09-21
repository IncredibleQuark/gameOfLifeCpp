//
// Created by lukasz on 21/9/20.
//

#ifndef GAMEOFLIFE_GRIDDRAWER_H
#define GAMEOFLIFE_GRIDDRAWER_H

#include "Noncopyable.h"
#include "Color.h"

#include <cstdint>

namespace gameOfLife {
    class Display;

    class Grid;

    class GridDrawer : public Noncopyable {
    public:
        GridDrawer(int32_t backgroundColor = gameOfLife::black, int32_t cellColor = gameOfLife::white,
                   int32_t gridLineColor = gameOfLife::gray, bool drawGridLines = true);

    public:
        int32_t BackgroundColor() const { return backgroundColor_; }

        void SetBackgroundColor(uint32_t backgroundColor) { backgroundColor_ = backgroundColor; }

        int32_t CellColor() const { return cellColor_; }

        void SettCellColor(uint32_t cellColor) { cellColor_ = cellColor; }

        int32_t GridLineColor() const { return gridLineColor_; }

        void SetGridLineColor(uint32_t gridLineColor) { gridLineColor_ = gridLineColor; }

        bool DrawGridLines() const { return drawGridLines_; }

        void SetDrawGridLines(bool drawGridLines) { drawGridLines_ = drawGridLines; }

    public:
        void Draw(Display &display, const Grid &grid) const;


    private:
        void DrawCells(Display &display, const Grid &grid) const;

        void DrawGridLines(Display &display, const Grid &grid) const;

    private:
        int32_t backgroundColor_;
        int32_t cellColor_;
        int32_t gridLineColor_;
        bool drawGridLines_;
    };
}

#endif //GAMEOFLIFE_GRIDDRAWER_H
