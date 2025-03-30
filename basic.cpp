#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "megasort.h"
#include "file.h"
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(){

    vector<string> words;

    // TODO: get from cmd line
    read("./data/input_1B.txt", words);



    auto start = high_resolution_clock::now();
    megasort(words);
    auto end = high_resolution_clock::now();
    auto duration = end - start;
    auto duration_ms = duration.count() / 1000000.0;

    cout << words.size() << " words sorted in ";
    cout << duration_ms << " ms" << endl;

    // TODO: get from cmd line
    // write("sorted.txt", words);

    return 0;
}
