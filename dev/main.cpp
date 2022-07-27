#include <stdlib.h>
#include <iostream>
#include <float.h>
#include <queue>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include "./metrictime2.hpp"
#include "Graph.h"

using namespace std;

bool operator==(const Coord& lhs, const Coord& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

typedef pair<double, Coord> p_dc;

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

bool is_in_pq(Coord const v, vector<vector<bool>> const &pqTracker) {
    /*
    Checks if a given Coord element is present in the openSet PQ
    */
    if (pqTracker[v.x][v.y] == true) return true;
    return false;
}



void a_star_search(Coord _start, Coord _goal, Graph graph) {
    if (graph.n == 0 || graph.m == 0) return;
    // priority_queue<p_dc, vector<p_dc>, greater<p_dc> > openSet;
    // replaced the pair<double, coord> PQ for this one cuz I couldn't make the former work
    // cerr << "creating PQ" << endl;
    priority_queue<pdp, vector<pdp>, greater<pdp>> openSet;
    vector<vector<bool>> pqTracker(graph.n, vector<bool> (graph.m, false)); // keeps track of which nodes have been added to the openSet PQ

    //inserting first element to the PQ (starting node)
    // cerr << "pushing starting point in PQ" << endl;
    pair<int, int> s = make_pair(_start.x, _start.y);
    openSet.push(make_pair(0.f, s));
    pqTracker[_start.x][_start.y] = true;

    //map used to reconstruct path after reaching goal.
    vector<vector<Coord>> cameFrom(graph.n, vector<Coord> (graph.m, {-1, -1}));
    // We'll say that the starting cell's parent is itself
    // This fact is used in the recreation of the path to stop the loop.
    cameFrom[_start.x][_start.y] = _start;

    //need to initialize these to max double
    // gScore saves the minimum cost required to reach each cell
    vector<vector<double>> gScore(graph.n, vector<double> (graph.m, DBL_MAX));
    gScore[_start.x][_start.y] = 0;

    // fScore saves the sum of each node's gScore + h value
    vector<vector<double>> fScore(graph.n, vector<double> (graph.m, DBL_MAX));
    fScore[_start.x][_start.y] = graph.h(_start);


    while (!openSet.empty()) {
        pair<int, int> aux = openSet.top().second;
        Coord current = {aux.first, aux.second};
        openSet.pop();
        pqTracker[aux.first][aux.second] = false;

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

                if (!is_in_pq(neighbor, pqTracker)) {
                    pair<int, int> crds = make_pair(neighbor.x, neighbor.y);
                    openSet.push(make_pair(fScore[neighbor.x][neighbor.y], crds));
                    pqTracker[neighbor.x][neighbor.y] = true;
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
    TIMERSTART(aStar_avnc2);
    a_star_search(s, g, graph);
    TIMERSTOP(aStar_avnc2);
    return 0;
}
