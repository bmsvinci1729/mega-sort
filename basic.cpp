#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    ifstream ifile("input.txt");

    if(!ifile){
        cout << "Error operning file\n";
    }

    vector<string> words;
    string word;

    while(ifile >> word){
        words.push_back(word);
    }

    ifile.close();

    ofstream ofile("sorted.txt");

    sort(words.begin(), words.end());

    for(auto i:words){
        ofile << i << endl;
    }

    cout << "Sorted and saved to sorted.txt" << endl;

    return 0;
}
