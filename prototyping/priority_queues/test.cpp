#include "mypq.hpp"
#include <iostream>
#include <map>

using namespace std;

bool operator < (const pair<int, char>& lhs, const pair<int, char>& rhs) {
    return lhs.first < rhs.first;
}

int main() {
    MyPQ<int, char> pq;
    pair<int, char> x = pq.top();
    cout << x.first << x.second << endl;

    pq.push(5, 'b');
//     pq.push(3, 'c');
//     pq.push(2, 'x');
//     pq.push(1, 'f');
    pq.push(4, 'g');
    pq.push(8, 'v');
//     pq.push(0, 'z');

    x = pq.top();
    cout << x.first << x.second << endl;
}
