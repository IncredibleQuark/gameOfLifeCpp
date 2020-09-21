//
// Created by lukasz on 21/9/20.
//

#ifndef GAMEOFLIFE_DISPLAY_H
#define GAMEOFLIFE_DISPLAY_H

#include "Noncopyable.h"

#include <cassert>
#include <cstdint>
#include <utility>

namespace gameOfLife {
    class Display : private Noncopyable {
    public:
        Display(int cellsWide, int cellsHigh, int cellWidth, int cellHeight);

        ~Display();

    public:
        int Width() const { return width_; }

        int Height() const { return height_; }

        int CellsWide() const { return width_ / cellWidth_; }

        int CellHigh() const { return height_ / cellHeight_; }

        int CellWidth() const { return cellWidth_; }

        int CellHeight() const { return cellHeight_; }

        const uint32_t *Pixels() const { return pixels_; }

    public:
        void Clear(uint32_t argb);

        void DrawPixel(int x, int y, uint32_t argb);

        void DrawHLine(int x1, int x2, int y, uint32_t argb);

        void DrawVLine(int x, int y1, int y2, uint32_t argb);

        void FillRect(int x, int y, int w, int h, uint32_t argb);

    private:
        int width_;
        int height_;
        int cellWidth_;
        int cellHeight_;
        uint32_t *pixels_;


    };

    inline void Display::Clear(uint32_t argb) {
        int n = width_ * height_;
        uint32_t *pixels = pixels_;

        while (n--)
            *pixels++ = argb;
    }

    inline void Display::DrawPixel(int x, int y, uint32_t argb) {
        assert((x >= 0) && (x < width_) && (y >= 0) && (y < height_));

        pixels_[y * width_ + x] = argb;
    }

    inline void Display::DrawHLine(int x1, int x2, int y, uint32_t argb) {
        assert((x1 >= 0) && (x1 < width_) && (x2 >= 0) && (x2 < width_) && (y >= 0) && (y < height_));

        if (x1 > x2)
            std::swap(x1, x2);

        uint32_t offset = y*width_ + x1;
        uint32_t* pixels = pixels_;

        pixels += offset;

        int n = x2 - x1 + 1;

        while(n--)
            *pixels++ = argb;
    }

    inline void Display::DrawVLine(int x, int y1, int y2, uint32_t argb) {

        assert((x >= 0) && (x < width_) && (y1 >= 0) && (y1 < height_) && (y2 >= 0) && (y2 < height_));

        if (y1>y2)
            std::swap(y1, y2);

        uint32_t offset = y1*width_ + x;
        uint32_t* pixels = pixels_;

        pixels += offset;

        int n = y2 - y1 + 1;
        while (n--) {
            *pixels = argb;
            pixels += (uint32_t)width_;
        }
    }

    inline void Display::FillRect(int x, int y, int w, int h, uint32_t argb) {
        for(const int y2=y+h; y<y2; y++)
            DrawHLine(x, x+w-1, y, argb);
    }
}


#endif //GAMEOFLIFE_DISPLAY_H
