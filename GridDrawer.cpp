//
// Created by lukasz on 21/9/20.
//

#include "GridDrawer.h"
#include "Display.h"
#include "Grid.h"

#include <cassert>

namespace gameOfLife {
    GridDrawer::GridDrawer(int32_t backgroundColor, int32_t cellColor, int32_t gridLineColor, bool drawGridLines)
            : backgroundColor_(backgroundColor), cellColor_(cellColor), gridLineColor_(gridLineColor),
              drawGridLines_(drawGridLines) {}

    void GridDrawer::Draw(Display &display, const Grid &grid) const {
        display.Clear(backgroundColor_);

        DrawCells(display, grid);

        if (drawGridLines_)
            DrawGridLines(display, grid);
    }

    void GridDrawer::DrawCells(Display &display, const Grid &grid) const {
        for (int x=0; x<grid.Width(); ++x)
            for(int y=0; y<grid.Height(); ++y)
                if(grid.Cell(x,y))
                    display.FillRect(x*display.CellWidth(), y*display.CellHeight(), display.CellWidth(), display.CellWidth(), cellColor_); // TODO 2 x width?!
    }

    void GridDrawer::DrawGridLines(Display& display, const Grid& grid) const {
        for (int y=0; y<display.Height(); y+=display.CellHeight())
            display.DrawHLine(0, display.Width()-1, y, gridLineColor_);

        for(int x =0; x<display.Width(); x+=display.CellWidth())
            display.DrawVLine(x, 0, display.Height()-1, gridLineColor_);
    }
}