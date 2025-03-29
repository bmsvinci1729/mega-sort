#include <iostream>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    fstream file("input.txt");

    if(!file){
        cout << "Error operning file\n";
    }

    vector<string> words;
    string word;

    while(file >> word){
        words.push_back(word);
    }

    sort(words.begin(), words.end());

    cout << "Sorted words: " << endl;

    for(auto i:words){
        cout << i << endl; 
    }

    return 0;
}
