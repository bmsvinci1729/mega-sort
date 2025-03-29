#ifndef megasort_h
#define megasort_h

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

template <typename T>
void megasort(vector<T> &v){
    sort(v.begin(), v.end());
} 

#endif