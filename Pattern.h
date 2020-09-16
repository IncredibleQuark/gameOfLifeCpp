//
// Created by lukasz on 16/9/20.
//

#ifndef GAMEOFLIFE_PATTERN_H
#define GAMEOFLIFE_PATTERN_H

#include "Noncopyable.h"

#include <string>
#include <vector>

namespace gameOfLife {

    class Pattern : private Noncopyable {

        friend class PatternLoader;

    public:
        Pattern() {}
        explicit Pattern(const char **data);

    public:
        int Width() const;

        int Height() const {
            return (int) rows_.size();
        }

        const std::vector<std::string> &Rows()
        const { return rows_; }

    public:
        void Reset() { rows_.clear(); }

        void Reset(const char **data);

    private:
        std::vector<std::string> &Rows() {
            return rows_;
        }

    private:
        std::vector<std::string> rows_;

    };
}


#endif //GAMEOFLIFE_PATTERN_H
