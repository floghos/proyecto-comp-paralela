#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <float.h>
#include <queue>
#include <map>
#include <vector>
#include <time.h>
#include <fstream>
// #include <limits.h>

using namespace std;


struct Coord {
    int x, y;
};

bool operator==(const Coord& lhs, const Coord& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

typedef pair<double, Coord> p_dc;

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
    // I don't know if Coords will be necessary, since they can be calculated
    // based on the index, but it might be faster to just save them.
    // Coord pos; // so far it has been unneeded
    bool wall = false;
    // bool goal = false;
    int w = 1;
    // w stands for weight
    // The idea for this is that walking through this cell has a greater cost
    // in other words, I... LOVE... YOU... *cough* excuse me...
    // in other words, the cost of every incoming edge needs to add w.

    // Seriously considering ditching this struct and make the graph just a
    // matrix of chars
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
    Graph(vector<vector<char>> const &map) {
        // resize the vector to hold `n` elements of type `vector<int>`
        n = map.size();
        m = map[0].size();
        grid.resize(n, vector<Cell> (m));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (map[i][j] == '.') {
                    grid[i][j].wall = false;
                }
                if (map[i][j] == '#') {
                    grid[i][j].wall = true;
                }
                // grid[i][j] = map[i][j];
            }
        }
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
                if (_x < 0 || _x >= n) continue;
                if (_y < 0 || _y >= m) continue;
                //and also avoid self
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
        cerr << "calculating H of " << cell.x << "," << cell.y << endl;
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
    /*
    Checks if a given Coord element is present in the given PQ
    It recieves the PQ as a copy by value and empties it, checking one
    element at a time
    */
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
    cerr << "creating PQ" << endl;
    priority_queue<pdp, vector<pdp>, greater<pdp>> openSet;

    //inserting first element to the PQ (starting node)
    cerr << "pushing starting point in PQ" << endl;
    pair<int, int> s = make_pair(_start.x, _start.y);
    openSet.push(make_pair(0.f, s));

    //map used to reconstruct path after reaching goal.
    cerr << "allocating memory for auxiliary vectors" << endl;

    vector<vector<Coord>> cameFrom(graph.n, vector<Coord> (graph.m, {-1, -1}));
    // We'll say that the starting cell's parent is itself
    // This fact is used in the recreation of the path to stop the loop.
    cameFrom[_start.x][_start.y] = _start;

    //need to initialize these to max double
    vector<vector<double>> gScore(graph.n, vector<double> (graph.m, DBL_MAX));
    gScore[_start.x][_start.y] = 0;
    vector<vector<double>> fScore(graph.n, vector<double> (graph.m, DBL_MAX));
    fScore[_start.x][_start.y] = graph.h(_start);

    // just testing!!! this counter will limit the number of iterations to prevent endless loops
    int forceQuit = 0;

    while (!openSet.empty() && forceQuit < 1000) {
        forceQuit++;

        pair<int, int> aux = openSet.top().second;
        Coord current = {aux.first, aux.second};
        openSet.pop();
        cerr << aux.first << "," << aux.second << endl;
        if (current == graph.goal) {
            cerr << "goal reached, recreating path" << endl;
            reconstruct_path(current, cameFrom);
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
    cout << "No path found" << endl;
}


int main(int argc, char const *argv[]) {
    int n, m;
    // cin >> n >> m;
    ifstream file("testmap.txt");
    file >> n >> m;

    vector<vector<char>> map(n, vector<char> (m, '.'));
    Coord s, g;

    cerr << "reading input" << endl;
    /* read map from std input*/
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> map[i][j];
            if (map[i][j] == 's') {
                s = {i, j};
                map[i][j] == '.';
            }
            if (map[i][j] == 'g') {
                g = {i, j};
                map[i][j] == '.';
            }
        }
    }

    cerr << "creating graph" << endl;
    Graph graph(map);
    graph.setGoal(g);

    cerr << "running a_star" << endl;
    a_star_search(s, g, graph);

    return 0;
}
