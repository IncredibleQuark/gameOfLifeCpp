//
// Created by lukasz on 28/9/20.
//

#include "Simulation.h"
#include "Grid.h"
#include "Display.h"
#include "GridDrawer.h"
#include "Pattern.h"

#include <utility>

using namespace std;

namespace gameOfLife {
    Simulation::Simulation(int cellsWide, int cellsHigh, int cellWidth, int cellHeight) :
            grid1_(new Grid(cellsWide, cellsHigh)),
            grid2_(new Grid(cellsWide, cellsHigh)),
            activeGrid_(nullptr),
            temporaryGrid_(nullptr),
            display_(new gameOfLife::Display(cellsWide, cellsHigh, cellWidth, cellHeight)),
            drawer_(new GridDrawer()) {

        activeGrid_ = grid1_;
        temporaryGrid_ = grid2_;
    }

    Simulation::~Simulation() {
        delete drawer_;
        delete display_;
        delete grid2_;
        delete grid1_;
    }

    void Simulation::Reset() {
        activeGrid_ = grid1_;
        temporaryGrid_ = grid2_;

        activeGrid_->Reset();
        temporaryGrid_->Reset();

        Draw();
    }

    void Simulation::Reset(const Pattern &pattern) {
        activeGrid_ = grid1_;
        temporaryGrid_ = grid2_;
        activeGrid_->Reset();
        temporaryGrid_->Reset();

        activeGrid_->SetPattern((activeGrid_->Width() - pattern.Width()) / 2,
                                (activeGrid_->Height() - pattern.Height()) / 2, pattern);
        Draw();
    }

    void Simulation::Randomize(int densityFactor) {
        activeGrid_ = grid1_;
        temporaryGrid_ = grid2_;

        activeGrid_->Randomize(densityFactor);
        temporaryGrid_->Reset();

        Draw();
    }

    bool Simulation::Cell(int x, int y) const {
        return activeGrid_->Cell(x, y);
    }

    void Simulation::SetCell(int x, int y, bool cell) {
        activeGrid_->SetCell(x, y, cell);
    }

    void Simulation::SetPattern(int x, int y, const Pattern &pattern) {
        activeGrid_->SetPattern(x, y, pattern);
    }

    void Simulation::Draw() {
        drawer_->Draw(*display_, *activeGrid_);
    }

    void Simulation::Step() {
        ProcessCells();
        SwapGrids();
        Draw();
    }

    void Simulation::ProcessCells() {
        for (int x = 0; x < activeGrid_->Width(); ++x) {
            for (int y = 0; y < activeGrid_->Height(); ++y) {
                const bool c = activeGrid_->Cell(x, y);
                const int nc = activeGrid_->NeighbourCount(x, y);

                if (c && (nc == 2 || nc == 3))
                    temporaryGrid_->SetCell(x, y, true);
                else if (!c && nc == 3)
                    temporaryGrid_->SetCell(x, y, true);
                else
                    temporaryGrid_->SetCell(x, y, false);
            }
        }
    }

    void Simulation::SwapGrids() {
        std::swap(activeGrid_, temporaryGrid_);
    }
}
