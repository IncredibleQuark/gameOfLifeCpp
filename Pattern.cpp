//
// Created by lukasz on 16/9/20.
//

#include "Pattern.h"

#include <algorithm>
#include <cassert>
#include <cstring>

using namespace std;

namespace gameOfLife {
    Pattern::Pattern(const char **data) {
        Reset(data);
    }

    void Pattern::Reset(const char **data) {
        assert(data);

        rows_.clear();

        int dx = 0;
        int dy = 0;

        while (true) {
            if (!*data)
                break;
            rows_.emplace_back(string(*data++));
        }
    }

    int Pattern::Width() const {
        return (int)max_element(
                rows_.begin(),
                rows_.end(),
                [](const string &s1, const string &s2) { return s1.length() < s2.length(); }
        )->length();
    }
}