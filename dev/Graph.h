#include <vector>

#ifndef GRAPH_H
#define GRAPH_H

struct Coord {
    int x, y;
};

class Graph {
public:
    int n = 0;
    int m = 0;
    std::vector<std::vector<char>> grid;
    Coord goal;

    Graph(std::vector<std::vector<char>> const &map);
    void setGoal(Coord g);
    std::vector<Coord> get_neighbors(Coord node);
    double h(Coord cell);
    double d(Coord a, Coord b);
};

#endif
