//
//  main.cpp
//  word_count
//
//  Created by Yunus Syed on 9/8/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
using namespace std;

void PrintWordsAndCount(ifstream &file);

int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        cout << "error\n";
        return 0;
    }
    
    ifstream file(argv[1]);
    if (!file) {
        cout << "Error opening file." << endl;
        return 0;
    }

    PrintWordsAndCount(file);

    return 0;
}


void PrintWordsAndCount(ifstream &file) {
    
    map<string, int> words_and_count;
    
    string word_read;
    map<string, int>::iterator itr;
    while (file >> word_read) {
        bool word_duplicate = false;
        for (itr = words_and_count.begin(); itr != words_and_count.end(); itr++) {
            if (word_read == itr -> first) {
                (itr->second++);
                word_duplicate = true;
                break;
            }
        }
        
        if (!word_duplicate)
            words_and_count.insert(pair<string, int> (word_read, 1));
    }
    
    for (itr = words_and_count.begin(); itr != words_and_count.end(); itr++) {
        cout << itr->first + " " << itr->second << endl;
    }
    
}
