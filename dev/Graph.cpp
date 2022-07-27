#include "./Graph.h"
#include <vector>
#include <cmath>


Graph :: Graph(std :: vector<std :: vector<char>> const &map) {
    n = map.size();
    m = map[0].size();
    grid = map;
}

void Graph :: setGoal(Coord g) {
    goal = g;
}

std :: vector<Coord> Graph :: get_neighbors(Coord node) {
    std :: vector<Coord> neighbors;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int _x, _y;
            _x = node.x + i;
            _y = node.y + j;

            //check if we are off limits
            if (_x < 0 || _x >= n) continue;
            if (_y < 0 || _y >= m) continue;
            //and also avoid self
            if (i == 0 && j == 0) continue;

            if (grid[_x][_y] == '.') {
                neighbors.push_back(Coord {_x, _y});
            }
        }
    }
    return neighbors;
}

double Graph :: h(Coord cell) {
    return sqrt((pow((cell.x - goal.x), 2) + pow((cell.y - goal.y), 2)));
}

double Graph :: d(Coord a, Coord b) {
// returns the distance between nodes

    // Standard euclidian distance:
    // return sqrt((pow((a.x - b.x), 2) + pow((a.y - b.y), 2)));

    // cheaty (and maybe cheaper) way using the assumption that every node is in a square grid
    if (a.x == b.x || a.y == b.y) {
        return 1;
    } else {
        return M_SQRT2; // = sqrt(2), math constant from <cmath>
    }
}
