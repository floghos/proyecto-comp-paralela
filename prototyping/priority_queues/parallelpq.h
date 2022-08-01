#include <queue>
#include <vector>
#include <map>
#include "murmurhash.hpp"
#include "mypq.hpp"


#ifndef PARALLELPQ_H
#define PARALLELPQ_H

using namespace std;

 #include <omp.h>

typedef std::pair<double, int> pdi; // pair double-pair
// typedef pair<double, int> pdi; // pair double-int

class ParallelPQ {
private:
// Members
    // bits determines the size of the mPQArray, as in mPQArray.size() = 2^mBits,
    // indexes of the array will go from 0 to 2^mBits-1
    unsigned int mBits;
    MyPQ<double, unsigned int> mManager;
    omp_lock_t *lock;
    vector<priority_queue<pdi, vector<pdi>, greater<pdi>>> mPQArray;
    unsigned int hash(int id);
//     map<unsigned int, double> mMap; //keeps track which cells have entered the PQ and with which fScores.

// Methods

public:
// Methods
    ParallelPQ(int bits);
    std::pair<double, int> top();
    void push(double fScore, unsigned int cell_id);
    void pop();
    double find(unsigned int cell_id);
    int size();
    bool empty();
};

#endif
