//g++ -std=c++17 -pthread -o merge merge.cpp

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <filesystem>
#include <algorithm>
#include <string>
#include <chrono>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

void merge_two_sorted_files(const string& file1, const string& file2, const string& output_file) {
    ifstream f1(file1), f2(file2);
    ofstream out(output_file);

    string line1, line2;
    bool has1 = static_cast<bool>(getline(f1, line1));
    bool has2 = static_cast<bool>(getline(f2, line2));

    while (has1 && has2) {
        if (line1 <= line2) {
            out << line1 << '\n';
            has1 = static_cast<bool>(getline(f1, line1));
        } else {
            out << line2 << '\n';
            has2 = static_cast<bool>(getline(f2, line2));
        }
    }
    while (has1) {
        out << line1 << '\n';
        has1 = static_cast<bool>(getline(f1, line1));
    }
    while (has2) {
        out << line2 << '\n';
        has2 = static_cast<bool>(getline(f2, line2));
    }

    f1.close(); f2.close(); out.close();
}

vector<string> get_sorted_chunk_files(const string& dir) {
    vector<string> files;
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.path().extension() == ".txt")
            files.push_back(entry.path().string());
    }
    sort(files.begin(), files.end());  // Ensure order
    return files;
}

int main() {
    string input_dir = "./sorted_chunks_100M";  
    string temp_dir = "./merge_100M";      

    vector<string> files = get_sorted_chunk_files(input_dir);
    int round = 0;

    while (files.size() > 1) {
        vector<thread> threads;
        vector<string> next_round_files;

        for (size_t i = 0; i < files.size(); i += 2) {
            if (i + 1 < files.size()) {
                string out_file = temp_dir + "/merged_r" + to_string(round) + "_p" + to_string(i / 2) + ".txt";
                next_round_files.push_back(out_file);
                threads.emplace_back(merge_two_sorted_files, files[i], files[i + 1], out_file);
            } else {
                next_round_files.push_back(files[i]);
            }
        }

        // waiting for all threads to complete 
        for (auto& t : threads) t.join();

        files = next_round_files;
        round++;
        cout << "Merge round " << round << " complete. Files remaining: " << files.size() << endl;
    }

    cout << "\nFinal sorted file: " << files[0] << endl;

    return 0;
}
