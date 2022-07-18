#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <float.h>
#include <queue>
#include <map>
#include <string>
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

// A class to represent a graph object
class Graph {
public:
    // a vector of vectors to represent an adjacency list
    int n = 0;
    int m = 0;
    //vector<vector<Cell>> grid;
    vector<vector<char>> grid;


    Coord goal;
    // int GOAL_X_COR;
    // int GOAL_Y_COR;

    // Graph Constructor
    Graph(vector<vector<char>> const &map) {
        n = map.size();
        m = map[0].size();
        grid = map;

//         print_matrix(grid);
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

                if (grid[_x][_y] == '.') { // used to be grid[_x][_y].wall == false
                    neighbors.push_back(Coord {_x, _y});
                    //neighbors.push_back(grid[_x][_y].pos); //let's see if I don't need to use .pos
                }
            }
        }
        return neighbors;
    }

    double h(Coord cell) {
        // cerr << "calculating H of " << cell.x << "," << cell.y << endl;
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

void print_matrix(vector<vector<char>> const &matrix) {
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

}

void reconstruct_path(Coord current, vector<vector<Coord>> const &cameFrom, Graph graph) {
    vector<Coord> path;
    path.push_back(current);

    while (!(cameFrom[current.x][current.y] == current)) {
        current = cameFrom[current.x][current.y];
        path.push_back(current);
    }

    vector<vector<char>> sol = graph.grid; // sol is shor for solution
//     cout << "Path found:";
    for (int i = path.size()-1; i >= 0; i--) {
        if (i == path.size()-1) {
            sol[path[i].x][path[i].y] = 's';
        } else if (i == 0) {
            sol[path[i].x][path[i].y] = 'g';
        } else {
            sol[path[i].x][path[i].y] = 'o';
        }
//         cout << " --> " << path[i].x << "," << path[i].y;
    }
//     cout << endl;

//     print_matrix(sol);

    ofstream out_file;
    out_file.open("solution.txt");

    for (int i = 0; i < graph.n; i++) {
        for (int j = 0; j < graph.m; j++) {
            out_file << sol[i][j] << " ";
        }
        out_file << endl;
    }
    out_file.close();

}




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
    // cerr << "creating PQ" << endl;
    priority_queue<pdp, vector<pdp>, greater<pdp>> openSet;

    //inserting first element to the PQ (starting node)
    // cerr << "pushing starting point in PQ" << endl;
    pair<int, int> s = make_pair(_start.x, _start.y);
    openSet.push(make_pair(0.f, s));

    //map used to reconstruct path after reaching goal.
    // cerr << "allocating memory for auxiliary vectors" << endl;

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
    // int forceQuit = 0;

    while (!openSet.empty()) {
        // forceQuit++;

        pair<int, int> aux = openSet.top().second;
        Coord current = {aux.first, aux.second};
        openSet.pop();
        // cerr << aux.first << "," << aux.second << endl;
        if (current == graph.goal) {
            cerr << "goal reached, recreating path" << endl;
            reconstruct_path(current, cameFrom, graph);
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
//     ifstream file("testmap.txt");
//     ifstream file("asciimap.txt");
    string filepath;
    if (argc == 1) {
        cout << "Please provide a file path containing the map\n";
        return 0 ;
    }
    filepath = argv[1];
    ifstream file(filepath);

    file >> n >> m;

    vector<vector<char>> map(n, vector<char> (m, '.'));
    Coord s, g;

    cerr << "Reading input" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            file >> map[i][j];
            if (map[i][j] == 's') {
                s = {i, j};
                map[i][j] = '.';
            }
            if (map[i][j] == 'g') {
                g = {i, j};
                map[i][j] = '.';
            }
        }
    }

    cerr << "Creating graph" << endl;
    Graph graph(map);
    graph.setGoal(g);

    cerr << "Running a_star..." << endl;
    a_star_search(s, g, graph);

    return 0;
}
