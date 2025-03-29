#ifndef file_h
#define file_h

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

template <typename T>
void read(T s, vector<string> &words){ // string for file path enclosed in ""
    
    ifstream ifile(s);

    if(!ifile){
        cout << "Error operning file\n";
    }

    string x;
    while(ifile >> x){
        words.push_back(x);
    }

    ifile.close();

}

template <typename T>
void write(T s, vector<string> words){
    ofstream ofile(s);
    
    for(auto i:words){
        ofile << i << endl;
    }
    cout << "Sorted and saved to sorted.txt" << endl;
}

#endif