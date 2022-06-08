#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <float.h>
#include <queue>
#include <map>
#include <vector>
#include <time.h>
// #include <limits.h>

using namespace std;


struct Coord {
    int x, y;
};

bool operator==(const Coord& lhs, const Coord& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

typedef pair<double, Coord> p_dc;

void reconstruct_path(int current, vector<int> const &cameFrom) {
    /*
    COPIED FROM soa_approach
    CHECK WHAT NEEDS TO BE REWORKED
    */

    vector<int> path;
void reconstruct_path(Coord current, vector<vector<Coord>> const &cameFrom) {
    vector<Coord> path;
    path.push_back(current);

    while (!(cameFrom[current.x][current.y] == current)) {
        current = cameFrom[current.x][current.y];
        path.push_back(current);
    }

    //print pathf
    cout << "Path found:";
    for (int i = path.size()-1; i >= 0; i--) {
        cout << " --> " << path[i].x << "," << path[i].y;
    }
    cout << endl;
}


struct Cell {
    // int x, y;
    // I don't know if these'll be necessary, since coords can be calculated
    // based on the index, but it might be faster to just save them.
    Coord pos;
    bool wall = false;
    // bool goal = false;
    int w = 0;
    // w stands for weight
    // The idea for this is that walking through this cell has a greater cost
    // in other words, I... LOVE... YOU... *cough* excuse me...
    // in other words, the cost of every incoming edge needs to add w.
};


// A class to represent a graph object
class Graph {
public:
    // a vector of vectors to represent an adjacency list
    int n = 0;
    int m = 0;
    vector<vector<Cell>> grid;

    Coord goal;
    // int GOAL_X_COR;
    // int GOAL_Y_COR;

    // Graph Constructor
    Graph(vector<vector<int>> map) {
        // resize the vector to hold `n` elements of type `vector<int>`
        // n = map.size();
        // m = map[0].size();
        //
        // grid.resize(map.size());
        // add edges to the directed graph

    }

    void setGoal(Coord g) {
        goal = g;
    }

    vector<Coord> get_neighbors(Coord node) {
        vector<Coord> neighbors;

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int _x, _y;
                _x = node.x + i;
                _y = node.y + j;

                //check if we are off limits
                if (_x < 0 || _x > n) continue;
                if (_y < 0 || _y > m) continue;
                //also avoid self
                if (i == 0 && j == 0) continue;

                if (grid[_x][_y].wall == false) {
                    neighbors.push_back(Coord {_x, _y});
                    //neighbors.push_back(grid[_x][_y].pos); //let's see if I don't need to use .pos
                }
            }
        }
        return neighbors;
    }

    double h(Coord cell) {
        return sqrt((pow((cell.x - goal.x), 2) + pow((cell.y - goal.y), 2)));
    }

    double d(Coord a, Coord b) {
        // returns the distance between nodes
        // return sqrt((pow((a.x - b.x), 2) + pow((a.y - b.y), 2)));

        // cheaty (and maybe cheaper) way
        if (a.x == b.x || a.y == b.y) {
            return 1;
        } else {
            return M_SQRT2; // = sqrt(2), math constant from <cmath>
        }
    }
};

typedef pair<double, pair<int,int> > pdp;

bool is_in_pq(Coord v, priority_queue<pdp, vector<pdp>, greater<pdp>> pq) {
    while (!pq.empty()) {
        pair<int, int> t = pq.top().second;
        Coord check = {t.first, t.second};
        if (check == v) return true;
        pq.pop();
    }
    return false;
}



void a_star_search(Coord _start, Coord _goal, Graph graph) {
    if (graph.n == 0 || graph.m == 0) return;
    // priority_queue<p_dc, vector<p_dc>, greater<p_dc> > openSet;
    // replaced the pair<double, coord> PQ for this one cuz I couldn't make the former work
    priority_queue<pdp, vector<pdp>, greater<pdp>> openSet;

    //inserting first element to the PQ (starting node)
    pair<int, int> s = make_pair(_start.x, _start.y);
    openSet.push(make_pair(0.f, s));

    //map used to reconstruct path after reaching goal.
    vector<vector<Coord>> cameFrom(graph.n, vector<Coord> (graph.m, {-1, -1}));

    //need to initialize these to max double
    vector<vector<double>> gScore(graph.n, vector<double> (graph.m, DBL_MAX));
    gScore[_start.x][_start.y] = 0;
    vector<vector<double>> fScore(graph.n, vector<double> (graph.m, DBL_MAX));
    fScore[_start.x][_start.y] = graph.h(_start);

    while (!openSet.empty()) {
        pair<int, int> aux = openSet.top().second;
        Coord current = {aux.first, aux.second};
        if (current == graph.goal) {
            // reconstruct_path(current);
            return;
        }

        vector<Coord> neighbors = graph.get_neighbors(current);
        for (Coord neighbor: neighbors) {
            double tentative_gScore = gScore[current.x][current.y] + graph.d(current, neighbor);
            if (tentative_gScore < gScore[neighbor.x][neighbor.y]) {
                cameFrom[neighbor.x][neighbor.y] = current;
                gScore[neighbor.x][neighbor.y] = tentative_gScore;
                fScore[neighbor.x][neighbor.y] = tentative_gScore + graph.h(neighbor);
                if (!is_in_pq(neighbor, openSet)) {
                    pair<int, int> crds = make_pair(neighbor.x, neighbor.y);
                    openSet.push(make_pair(fScore[neighbor.x][neighbor.y], crds));
                }
            }
        }
    }
}


int main(int argc, char const *argv[]) {
    /* read map from file*/
    int n, m;
    vector<vector<int>> map;
    cerr << "check map vector " << map.size() << endl;


    Coord a, b;

    n = 3;
    m = 5;

    // this was just for testing
    // vector<vector<double>> gScore(n, vector<double> (m, DBL_MAX));
    // cout << "gScore dims: " << gScore.size() << "x" << gScore[0].size() << endl;

    // reading from std input
    // cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            /*TODO: read from input amd save to map*/
            continue;
        }
    }
    Graph graph(map);
    a_star_search(a, b, graph);

    return 0;
}
