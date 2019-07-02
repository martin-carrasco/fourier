#include "algorithms/hough.h"
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

bool in_line(pair<int, int> coords, const vector<pair<int, int>>& scores) {
    for (const auto& [x, y] : scores) {
        if (x == coords.first && y == coords.first) return true;
    }
    return false;
}

void inc_line_value(vector<pair<int, int>> line, vector<LineScore>& scores) {
    auto it = find(scores.begin(), scores.end(), line);
    if (it == scores.end()) {
        LineScore ls{line, 1};
        scores.push_back(ls);
    } else
        it->score += 1;
}
vector<pair<int, int>> hough_transform(vector<vector<int>> vec) {
    int height = vec.size();
    int width = vec[0].size();

    vector<vector<int>> line_scores((max(height, width) * 2) + 2,
                                    vector<int>(180, 0));

    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            for (int theta = 1; theta <= 180; theta++) {
                int r = floor(x * cos(theta) + y * sin(theta));
                line_scores[r + height + 1][theta] =
                    line_scores[r + height + 1][theta] + 1;
            }
        }
    }
    cutoff_min(line_scores);
    return lines;
}
void cutoff_min(vector<vector<int>>& mat) {
    std::vector<std::pair<int, int>> lines;

    for (int x = 0; x < mat.size(); x++) {
        for (int y = 0; y < mat[0].size(); y++) {
            mat[x][y] = mat[x][y] > 5 ? 1 : 0;
        }
    }
}
