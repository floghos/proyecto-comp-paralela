#include <stdlib.h>
#include <iostream>
#include <queue>
#include <map>
#include <vector>
// #include <bits/stdc++.h>

using namespace std;

struct Coord {
    int x, y;
};

bool operator==(const Coord& lhs, const Coord& rhs) {
    return (lhs.x == rhs.x && lhs.y == rhs.y);
}

typedef pair<int, Coord> p_dc;
typedef pair<int, int> pi;

//
void printPQ(priority_queue<int> pq) {
    while (!pq.empty()) {
        int check = pq.top();
        cout << check << " ";
        //if (check == v) return true;
        pq.pop();
    }
    cout << endl;
    cout << "size after print in func: " << pq.size() << endl;
}

void printPQpi(priority_queue<pi> pq) {
    while (!pq.empty()) {
        int check = pq.top().second;
        cout << check << " ";
        //if (check == v) return true;
        pq.pop();
    }
    cout << endl;
    cout << "size after print in func: " << pq.size() << endl;
}

// void printPQpdc(priority_queue<p_dc, vector<p_dc>, greater<p_dc> > pq) {
//     while (!pq.empty()) {
//         Coord check = pq.top().second;
//         cout << check.x << "," << check.y << " ";
//         //if (check == v) return true;
//         pq.pop();
//     }
//     cout << endl;
//     cout << "size after print in func: " << pq.size() << endl;
// }

// bool is_in_pq(Coord v, priority_queue<p_dc, vector<p_dc>, greater<p_dc> > pq) {
//     while (!pq.empty()) {
//         Coord check = pq.top().second;
//         if (check == v) return true;
//         pq.pop();
//     }
//     return false;
// }

void printPQppq(priority_queue<pair<int, pair<int,int>>> pq) {
    while (!pq.empty()) {
        pair<int,int> check = pq.top().second;
        cout << check.first << "," << check.second << " ";
        //if (check == v) return true;
        pq.pop();
    }
    cout << endl;
    cout << "size after print in func: " << pq.size() << endl;
}

int main(int argc, char const *argv[]) {
    // priority_queue<int> pq;


    // priority_queue<p_dc> pq;
    // pq.push(make_pair(3, Coord {3, 4}));
    // pq.push(make_pair(5, Coord {5, 6}));
    // pq.push(make_pair(1, Coord {1, 2}));
    // pq.push(make_pair(4, Coord {4, 5}));
    // pq.push(make_pair(2, Coord {2, 3}));


    //
    // priority_queue<pi> pq;
    // pq.push(make_pair(3, 4));
    // pq.push(make_pair(5, 6));
    // pq.push(make_pair(1, 2));
    // pq.push(make_pair(4, 5));
    // pq.push(make_pair(2, 3));


    priority_queue<pair<int, pair<int,int> >> ppq;
    // ppq.push(make_pair(3, Coord {3, 4}));
    ppq.push(make_pair(3, make_pair(3, 3)));
    ppq.push(make_pair(5, make_pair(5, 1)));
    ppq.push(make_pair(1, make_pair(2, 3)));
    ppq.push(make_pair(4, make_pair(1, 5)));
    ppq.push(make_pair(2, make_pair(2, 2)));
    printPQppq(ppq);

    // printPQpi(pq);
    // cout << "size after print in main: " << pq.size() << endl;


    return 0;
}
