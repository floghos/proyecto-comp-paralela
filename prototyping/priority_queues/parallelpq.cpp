#include "parallelpq.h"

unsigned int ParallelPQ :: hash(int id) {

    uint64_t h = murmur64((uint64_t) id);
    uint64_t mask = (1 << mBits) - 1;
    unsigned int idx = (unsigned int) h & mask;
    return (unsigned int)(idx);
}

ParallelPQ :: ParallelPQ(int bits) {
    mBits = bits;
    unsigned int arraySize = 1 << (bits);
    for (unsigned int i = 0; i < arraySize; i++) {
        mPQArray.push_back(priority_queue<pdi, vector<pdi>, greater<pdi>>());
    }
    lock = (omp_lock_t *) malloc(arraySize*sizeof(omp_lock_t));

    for (unsigned int i = 0; i < arraySize; i++) {
        omp_init_lock(&(lock[i]));
    }

}

void ParallelPQ :: push(double fScore, unsigned int cell_id) {
    unsigned int idx = hash(cell_id);

    omp_set_lock(&(lock[idx]));
    //record lowest previous to the insert
    pdi oldLowest = mPQArray[idx].top();
    //insert new element
    mPQArray[idx].push(pdi{fScore, cell_id});
    //check new lowest element
    pdi newLowest = mPQArray[idx].top();
    // If the lowest element in the PQ hasn't changed, we are done.
    // Otherwise, we need to update the key of the corresponding PQ in the
    // manaager PQ
    if (oldLowest.second != newLowest.second) {
        mManager.decreaseKey(idx, newLowest.first);
    }
    omp_unset_lock(&(lock[idx]));

}

std::pair<double, int> ParallelPQ :: top() {
    // ask the manager which PQ has the lowest item WITHOUT removing it
    unsigned int idx = mManager.top().second;
    // Take a peek of said item from the corresponding PQ
    pdi answer = mPQArray[idx].top();
    return answer;
}

void ParallelPQ :: pop() {
    // ask the manager which PQ has the lowest item and remove it
    unsigned int idx = mManager.top().second;
    // EXTRACT said item from the corresponding PQ
    mPQArray[idx].pop();
    // Give manager new lowest item of the current PQ
    auto temp = mPQArray[idx].top();
    mManager.push(temp.first, idx);
}

double find(unsigned int cell_id) {
    return double(-1);
}

int ParallelPQ :: size() {
    int count = 0;
    for (int i = 0; i < mPQArray.size(); i++) {
        count += mPQArray[i].size();
    }
    return int();
}

bool ParallelPQ :: empty() {
    for (int i = 0; i < mPQArray.size(); i++) {
        if (!mPQArray[i].empty()) return false;
    }
    return true;
}
