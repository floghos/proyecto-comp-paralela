#include <queue>
#include <vector>
#include <map>

#include <iostream>

#ifndef MYPQ_H
#define MYPQ_H


template <class K, class V>
class MyPQ {
    /* This is a min-heap, <key, value> based priority queue.
     * It sorts items putting first the one with the lowest "key".
     * I chose to use pairs of template classes instead of just one template class that allows for pairs.
     * This is so I can then look for an element using only the "value", since for my purposes this "value" is the ID of the element,
     * while the "key" is just the priority around which the element is sorted.
     * Maybe I should rename the template classes?
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
    std::map<V, unsigned int> mMap;

    void swap(unsigned int idx_a, unsigned int idx_b) {
        std::pair<K, V> aux = mArray[idx_a];
        mArray[idx_a] = mArray[idx_b];
        mArray[idx_b] = aux;

        mMap[mArray[idx_a].second] = idx_a;
        mMap[mArray[idx_b].second] = idx_b;
    }

public:

    MyPQ() {
        mArray.push_back(std::pair<K, V>());
    }

    std::pair<K, V> top() {
        return mArray[1];
    }

    void push(K key, V id) {
        unsigned int n = mArray.size()-1;
        n++;

        std::pair<K, V> newEntry = std::make_pair(key, id);
        mArray.push_back(newEntry);
        mMap[id] = n;
        unsigned int i = n;
        while (i > 1) {
            if (mArray[i].first < mArray[i/2].first) {
                swap(i, i/2);
                i = i/2;
            } else {
                break;
            }
        }
    }
    void push(std::pair<K, V> p) {
        push(p.first, p.second);
    }

    std::pair<K, V> pop() {
        if (size() == 0) return std::pair<K, V>();

        std::pair<K, V> ans = mArray[1];
        unsigned int n = mArray.size()-1;

        mMap.erase(mArray[1].second);
        mArray[1] = mArray[n];
        mArray.pop_back();
        mMap[mArray[1].second] = 1;
        n--;
        unsigned int i = 1;
        while (2*i <= n) {
            if ((2*i+1 > n) || (mArray[2*i].first < mArray[2*i+1].first)) {
                if (mArray[i].first > mArray[2*i].first) {
                    swap(i, 2*i);
                    i = 2*i;
                } else {
                    break;
                }
            } else {
                if (mArray[i].first > mArray[2*i+1].first) {
                    swap(i, 2*i+1);
                    i = 2*i+1;
                } else {
                    break;
                }
            }
        }
        return ans;
    }

    void decreaseKey(V id, K newKey) {
        /* This will only allow for keys to be decreased, taking the element up the heap.
         * It should be easy enough to generalize this function into going up or down
         */
        unsigned int i = mMap[id];
        if (mArray[i].first > newKey) {
            mArray[i].first = newKey;
            while (i > 1) {
                if (mArray[i].first < mArray[i/2].first) {
                    swap(i, i/2);
                    i = i/2;
                } else {
                    break;
                }
            }
        }
    }

    int size() {
        /* It's size()-1 because I am sacrificing mArray[0] to be a useless position,
         * just to make the rest of the work with indices look a bit cleaner
         */
        return mArray.size()-1;
    }

    bool is_in_pq(V id) {
        return mMap.find(id) != mMap.end();
    }

    bool empty() {
        return size() <= 0;
    }

    void show_queue() {
        for (int i = 0; i < mArray.size(); i++) {
            std::cout << i << "(" << mArray[i].first << "," << mArray[i].second << ")" << " ";
        }
        std::cout << std::endl;
    }
};


#endif

