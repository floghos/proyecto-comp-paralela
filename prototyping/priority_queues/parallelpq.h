#include <queue>
#include <vector>
#include <map>

#ifndef PARALLELPQ_H
#define PARALLELPQ_H

struct Coord {
    int x, y;
};
using namespace std;

typedef pair<double, pair<int,int> > pdp; // pair double-pair
typedef pair<double, int> pdi; // pair double-int

class ParallelPQ {
private:
    priority_queue<pdi, vector<pdi>, greater<pdi>> mManager;
    vector<priority_queue<pdp, vector<pdp>, greater<pdp>>> mPQ_array;
    map<Coord, int> mMap;

public:

    ParallelPQ(int level);
    Coord top();
    void push();
    void pop();
    int size();
    bool empty();
};

#endif
