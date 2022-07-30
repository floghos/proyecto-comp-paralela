#include "parallelpq.h"


typedef pair<double, int> pdi; // pair double-int


ParallelPQ :: ParallelPQ(int level) {

}

Coord ParallelPQ :: top() {
    return Coord();
}

void ParallelPQ :: push() {

}

void ParallelPQ :: pop() {
    int first = mManager.top().second;


}

int ParallelPQ :: size() {
    int count = 0;
    for (int i = 0; i < mPQ_array.size(); i++) {
        count += mPQ_array[i].size();
    }
    return int();
}

bool ParallelPQ :: empty() {
    for (int i = 0; i < mPQ_array.size(); i++) {
        if (!mPQ_array[i].empty()) return false;
    }
    return true;
}
