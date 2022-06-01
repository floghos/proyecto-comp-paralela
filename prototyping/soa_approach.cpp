#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <vector>
#include <time.h>

using namespace std;

typedef pair<double, int> p_di;

int GOAL_X_COR;
int GOAL_Y_COR;

double h(int x_a, int y_a) {
    return sqrt((pow((x_a - GOAL_X_COR), 2) + pow((y_a - GOAL_Y_COR), 2)));
}

double d(int a, int b) {
    // returns the distance between nodes
    return 1;
}

void reconstruct_path(int current, const vector<int> &cameFrom) {
    vector<int> path;
    path.push_back(current);
    while (cameFrom[current] != current) {
        current = cameFrom[current];
        path.push_back(current);
    }

    //print pathf
    cout << "Path found:";
    for (int i = path.size()-1; i >= 0; i--) {
        cout << " --> " << path[i];
    }
    cout << endl;
}

// The following representation was taken from
// https://www.techiedelight.com/graph-implementation-using-stl/
// Data structure to store a graph edge
struct Edge {
    int src, dest;
};

// A class to represent a graph object
class Graph {
public:
    // a vector of vectors to represent an adjacency list
    vector<vector<int>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges, int n)
    {
        // resize the vector to hold `n` elements of type `vector<int>`
        adjList.resize(n);

        // add edges to the directed graph
        for (auto &edge: edges)
        {
            // insert at the end
            adjList[edge.src].push_back(edge.dest);

            // uncomment the following code for undirected graph
            // adjList[edge.dest].push_back(edge.src);
        }
    }
};

void printGraph(Graph const &graph) {
    int n = graph.adjList.size();
    for (int i = 0; i < n; i++) {
        // print the current vertex number
        cout << i << " ——> ";

        // print all neighboring vertices of a vertex `i`
        for (int v: graph.adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }
}

bool is_in_pq(int v, priority_queue<p_di, vector<p_di>, greater<p_di> > pq) {
    priority_queue<p_di, vector<p_di>, greater<p_di> > pqcopy = pq;
    while (!pqcopy.empty()) {
        int check = pqcopy.top().second;
        if (check == v) return true;
        pqcopy.pop();
    }
    return false;
}

void adj_matrix_from_graph(Graph const &graph) {
    int n = graph.adjList.size();
    vector<vector<int>> adjMatrix = { {0} };
    adjMatrix.resize(n, {0});

    //creating adjacency matrix
    for (int i = 0; i < n; i++) {
        adjMatrix[i].resize(n, 0);

        for (int v: graph.adjList[i]) {
            adjMatrix[i][v] = 1;
        }
    }

    //printing
    for (int i = 0; i < n; i++) {
        int j;
        for (j = 0; j < n-1; j++) {
            cout << adjMatrix[i][j] << ", ";
        }
        cout << adjMatrix[i][j] << endl;
    }
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    // number of vertices
    int n = 20;

    // number of edges
    // should go from 0 to n*(n-1)/2
    int e = n * (n-1) / 8;

    // defining graph by edges
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        int d = (i+1) % n;
        Edge e;
        e = {i, d};
        edges.push_back(e);
    }

    // vector<Edge> edges =
    // {
    //     {0, 1}, {1, 2}, {2, 0}, {2, 1}, {3, 2}, {4, 5}, {5, 4}
    // };

    Graph graph(edges, n);
    printGraph(graph);
    adj_matrix_from_graph(graph);

    // Defining vertices

    vector<int> xcoor;
    vector<int> ycoor;
    // vector<double> cost;
    vector<bool> goal;
    //vector<bool> visited;


    for (int i = 0; i < n; i++) {
        xcoor.push_back(i);
        ycoor.push_back(0);
        goal.push_back(false);
        //visited.push_back(false);
    }

    //selecting goal node
    int g_node = n-1;
    goal[g_node] = true;
    GOAL_X_COR = xcoor[g_node];
    GOAL_Y_COR = ycoor[g_node];

    // creating the governing priority queue for A*
    priority_queue<p_di, vector<p_di>, greater<p_di> > openSet;

    //selecting starting node
    int s_node = 0;

    openSet.push(make_pair(0.0, s_node));

    // This array will be used to reconstruct the path found
    vector<int> cameFrom;
    cameFrom.resize(n, -3);
    cameFrom[s_node] = s_node;

    //test
    // for (int i: cameFrom) {
    //     cout << i;
    // }
    // cout << endl;

    // For mynode n, gScore[n] is the cost of the cheapest path from start to n
    // currently known.
    vector<double> gScore;
    for (int i = 0; i < n; i++) {
        gScore.push_back(DBL_MAX);
    }
    gScore[s_node] = 0;

    // For mynode n, fScore[n] := gScore[n] + h(n). fScore[n] represents our
    // current best guess as to how short a path from start to finish can be if
    // it goes through n.
    vector<double> fScore;
    for (int i = 0; i < n; i++) {
        fScore.push_back(DBL_MAX);
    }
    fScore[s_node] = gScore[s_node] + h(xcoor[s_node], ycoor[s_node]);

    // This vector will store the path found if it exists.
    vector<int> path;

    while (!openSet.empty()) {
        int current = openSet.top().second;
        if (goal[current]) {
            reconstruct_path(current, cameFrom);
            return 0;
        }
        openSet.pop();

        for (int neighbor: graph.adjList[current]) {
            double tentative_gScore = gScore[current] + d(current, neighbor);
            if (tentative_gScore < gScore[neighbor]) {
                cameFrom[neighbor] = current;
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = tentative_gScore + h(xcoor[neighbor], ycoor[neighbor]);
                if (!is_in_pq(neighbor, openSet)) {
                    openSet.push(make_pair(fScore[neighbor], neighbor));
                }
            }
        }
    }

    // if we reach this point, no path was found.
    return 0;
}
