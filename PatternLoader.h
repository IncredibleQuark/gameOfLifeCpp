//
// Created by lukasz on 16/9/20.
//

#ifndef GAMEOFLIFE_PATTERNLOADER_H
#define GAMEOFLIFE_PATTERNLOADER_H

namespace gameOfLife {

    class Pattern;

    class PatternLoader {
    public:
        static bool LoadFromCells(
                const char* filepath,
                Pattern &pattern
        );
    };
}


#endif //GAMEOFLIFE_PATTERNLOADER_H
