#include <queue>
#include <vector>
#include <map>

#include <iostream>

#ifndef MYPQ_H
#define MYPQ_H

struct Coord {
    int x, y;
};
// using namespace std;

// typedef pair<double, pair<int,int> > pdp; // pair double-pair
// typedef pair<double, int> pdi; // pair double-int

// template<class K, class V> class MyPQ;  // pre-declare the template class itself
// template<class K, class V>bool operator < (const std::pair<K, V>& lhs, const std::pair<K, V>& rhs);

// bool operator < (const std::pair<int, char>& lhs, const std::pair<int, char>& rhs) {
//     return true;
// }

template <class K, class V>
class MyPQ {
    /* This is a min-heap.
     * It sorts items putting first the one with the lowest "key".
     */

    /*
     * As reference:
     * K is the Key according to which the elements will be sorted in the PQ (fScore, for the case of my A* implementation).
     * V is the Value/ID of the element. (Coord, in the case of my A* implementation)
     *
     *
     * For context, in the case of my manager PQ in my "Parallel-insert capable PQ:
     * K will be the fScore of each entry
     * V will be the ID of the sub-priority queue where the corresponding fScore can be found.
     */

private:
    std::vector<std::pair<K, V>> mArray;
    std::map<std::pair<K, V>, int> mMap;
//     int mSize;

    void swap(int a, int b) {
        std::pair<K, V> aux = mArray[a];
        mArray[a] = mArray[b];
        mArray[b] = aux;

        mMap[mArray[a]] = a;
        mMap[mArray[b]] = b;
    }

public:

    MyPQ() {
        mArray.push_back(std::pair<K, V>());
//         mSize = 0;
    }

    std::pair<K, V> top() {
        return mArray[1];
    }

    void push(K key, V id) {
        int n = mArray.size()-1;
        n++;

        std::pair<K, V> newEntry = std::make_pair(key, id);
        mArray.push_back(newEntry);
        mMap[newEntry] = n;
        int i = n;
        while (i > 1) {
            if (mArray[i] < mArray[i/2]) {
                swap(i, i/2);
                i = i/2;
            } else {
                break;
            }
        }
//         mSize++;
    }

    void pop() {
        /* ... */
//         mSize--;
    }

    void decreaseKey(V id, K newKey) {
        /* ... */
    }

    int size() {
        return mArray.size()-1;
    }

    bool empty() {
        return bool();
    }
};


#endif

