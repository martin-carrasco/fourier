#ifndef __HOUGH_H__
#define __HOUGH_H__

#include <algorithm>
#include <cmath>
#include <vector>

struct LineScore {
    std::vector<std::pair<int, int>> line;
    int score;
    bool operator==(const std::vector<std::pair<int, int>>& ls) {
        for (const auto& p : line) {
            auto it = std::find(ls.begin(), ls.end(), p);
            if (it == ls.end()) return false;
        }
        return true;
    }
};

std::vector<std::pair<int, int>> hough_transform(
    std::vector<std::vector<int>> vec);

bool in_line(std::pair<int, int> coords,
             const std::vector<std::pair<int, int>>& line);

void inc_line_value(std::vector<std::pair<int, int>> line,
                    std::vector<std::vector<std::pair<int, int>>>& scores);

void cutoff_min(std::vector<std::vector<int>>& mat);
#endif
