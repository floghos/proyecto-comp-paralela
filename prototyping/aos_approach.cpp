#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <vector>


using namespace std;

struct mynode {
    int id;
    int x;
    int y;
    // mynode* parent;
    bool goal;
    double cost;
    bool visited;
};

bool operator<(const mynode &lhs, const mynode &rhs) {
    return lhs.cost < rhs.cost;
}

// function reconstruct_path(cameFrom, current)
//     total_path := {current}
//     while current in cameFrom.Keys:
//         current := cameFrom[current]
//         total_path.prepend(current)
//     return total_path

double h(mynode n, mynode g) {
    return sqrt((pow((n.x - g.x), 2) + pow((n.y - g.y), 2)));
}


int main(int argc, char const *argv[]) {
    int n = 10;
    // map<int, mynode> v;
    vector<mynode> v;
    for (int i = 0; i < n-1; i++) {
        mynode new_mynode;
        new_mynode.x = i;
        new_mynode.y = 0;
        new_mynode.goal = false;
        v[i] = new_mynode;
    }


    //last mynode is goal
    mynode last_node;
    last_node.x = n;
    last_node.y = 0;
    last_node.goal = true;
    v[n-1] = last_node;


    priority_queue<mynode, vector<mynode>, less<mynode>> openSet;
    openSet.push(v[0]);

    vector<int> cameFrom;

    // For mynode n, gScore[n] is the cost of the cheapest path from start to n
    // currently known.
    vector<double> gScore;
    for (int i = 0; i < n; i++) {
        gScore[0] = DBL_MAX;
    }
    gScore[0] = 0;

    // For mynode n, fScore[n] := gScore[n] + h(n). fScore[n] represents our
    // current best guess as to how short a path from start to finish can be if
    // it goes through n.
    vector<double> fScore;
    for (int i = 0; i < n; i++) {
        fScore[0] = DBL_MAX;
    }
    fScore[0] = gScore[0] + h(v[0], v[n-1]);

    while (!openSet.empty()) {
        current = openSet.top();
        if (current.goal) {
            //return reconstruct_path();
            return 0;
        }
        openSet.pop();
        /*
        for each neighbor of current
            // d(current,neighbor) is the weight of the edge from current to neighbor
            // tentative_gScore is the distance from start to the neighbor through current
            tentative_gScore := gScore[current] + d(current, neighbor)
            if tentative_gScore < gScore[neighbor]
                // This path to neighbor is better than any previous one. Record it!
                cameFrom[neighbor] := current
                gScore[neighbor] := tentative_gScore
                fScore[neighbor] := tentative_gScore + h(neighbor)
                if neighbor not in openSet
                    openSet.add(neighbor)
        */
    }

    return 0;
}
