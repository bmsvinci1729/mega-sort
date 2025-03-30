#ifndef megasort_h
#define megasort_h

#include <vector>
#include <string>
#include <thread>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <chrono>
#include <cmath>

using namespace std;

void sort_parallel(vector<string>::iterator it1, vector<string>::iterator it2, int n, int depth) {
    int dist = distance(it1, it2);
    int x = pow(2, depth);
    if (dist <= n / x) {
        // Base case: sort directly
        sort(it1, it2);
        return;
    }

    auto mid = it1 + dist / 2;

    thread left_thread(sort_parallel, it1, mid, n, depth);
    thread right_thread(sort_parallel, mid, it2, n, depth);

    left_thread.join();
    right_thread.join();

    inplace_merge(it1, mid, it2);
}

template <typename T>
void megasort(vector<T> &v) {
    int n = v.size();
    int depth = 5;
    int c = 0;
    for(int j = 1;j<=1;j++){
    auto start = chrono::high_resolution_clock::now();

    sort_parallel(v.begin(), v.end(), n, depth);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Sorting completed in " << duration << " ms for a depth of " << pow(2, depth) << endl;}
}

#endif
