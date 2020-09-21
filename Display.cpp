//
// Created by lukasz on 21/9/20.
//

#include "Display.h"
namespace gameOfLife {
    Display::Display(int cellsWide, int cellsHigh, int cellWidth, int cellHeight):
        width_(cellsWide*cellWidth), height_(cellsHigh*cellHeight), cellWidth_(cellWidth), cellHeight_(cellHeight) {

        assert((width_ > 0) && (height_ > 0));

        pixels_ = new uint32_t[width_ * height_];
    }

    Display::~Display() {
        delete [] pixels_;
    }
}