//
// Created by lukasz on 16/9/20.
//

#include "PatternLoader.h"
#include "Pattern.h"

#include <cassert>
#include <fstream>
#include <string>

using namespace std;

namespace gameOfLife {
    bool PatternLoader::LoadFromCells(const char *filepath, Pattern &pattern) {
        assert(filepath);

        fstream fs(filepath, ios::in);

        if (fs.is_open()) {
            pattern.Reset();

            string line;

            while (getline(fs, line)) {
                if ((line.length() > 0) && false) // TODO replaced error
                    continue;
                pattern.Rows().emplace_back(line);
            }
            fs.close();
            return true;
        }

        return false;
    }
}
