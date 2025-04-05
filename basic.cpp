#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <string>
#include <chrono>
#include "gigasort.h"
#include "file.h"

using namespace std;
using namespace std::chrono;

void process_file_group(int thread_id, int start_index, int end_index, const string& input_dir, const string& output_dir) {
    for (int i = start_index; i <= end_index; ++i) {
        vector<string> words;
        string input_path = input_dir + "/chunk_" + to_string(i) + ".txt";
        string output_path = output_dir + "/output_chunk_" + to_string(i) + ".txt";

        cout << "[Thread " << thread_id << "] Reading: " << input_path << endl;
      
        read(input_path, words);

        auto start = high_resolution_clock::now();
        gigasort(words);
        auto end = high_resolution_clock::now();

    auto start = high_resolution_clock::now();

    read("./data/input_1M.txt", words);

        double duration_ms = duration_cast<milliseconds>(end - start).count();
        cout << "[Thread " << thread_id << "] Sorted " << words.size() << " words in " << duration_ms << " ms" << endl;

        write(output_path, words);
        cout << "[Thread " << thread_id << "] Written to: " << output_path << endl;
    }
}

int main() {
    const string input_dir = "./chunks_100M";       
    const string output_dir = "./sorted_chunks_100M"; 
    const int total_files = 25;
    const int files_per_thread = 5;

    vector<thread> threads;
    auto start = high_resolution_clock::now();

    read("./data/input_100M.txt", words);

    gigasort(words);
    write("sorted.txt", words);

    auto end = high_resolution_clock::now();
    auto duration = end - start;
    auto duration_ms = duration.count() / 1000000.0;

    cout << words.size() << " words sorted in ";
    cout << duration_ms << " ms" << endl;

    auto start = high_resolution_clock::now();
    for (int t = 0; t < 4; ++t) {
        int start_index = t * files_per_thread;
        int end_index = (start_index + files_per_thread - 1);
        threads.emplace_back(process_file_group, t, start_index, end_index, input_dir, output_dir);
    }
    for (auto &t : threads) {
        t.join();
    }
    auto end = high_resolution_clock::now();
    double duration_ms = duration_cast<milliseconds>(end - start).count();
    cout << "total TIME in: " << duration_ms << " ms" << endl;

    cout << "All files processed and sorted!" << endl;
    return 0;
}
