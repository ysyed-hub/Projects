//
//  word_count.cpp
//  word_count
//
//  Created by Yunus Syed on 9/18/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include "word_count.hpp"
#include <iostream>
#include <map>
#include <iterator>

std::map<std::string, int> WordCount::PrintWordsAndCount() {
    std::map<std::string, int> words_and_count;
    
    std::string word_read;
    std::map<std::string, int>::iterator itr;
    while (*file_name >> word_read) {
        bool word_duplicate = false;
        for (itr = words_and_count.begin(); itr != words_and_count.end(); itr++) {
            if (word_read == itr -> first) {
                (itr->second++);
                word_duplicate = true;
                break;
            }
        }
        
        if (!word_duplicate)
            words_and_count.insert(std::pair<std::string, int> (word_read, 1));
    }
    
    for (itr = words_and_count.begin(); itr != words_and_count.end(); itr++) {
        std::cout << itr->first + " " << itr->second << std::endl;
    }
    return words_and_count;
}
