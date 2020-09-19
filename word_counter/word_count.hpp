//
//  word_count.hpp
//  word_count
//
//  Created by Yunus Syed on 9/18/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef word_count_hpp
#define word_count_hpp

#include <stdio.h>
#include <fstream>
#include <map>

class WordCount {
  
    std::ifstream *file_name;
    
public:
    WordCount(std::ifstream *file) : file_name(file) {}
    std::map<std::string, int> PrintWordsAndCount();
    
};

#endif /* word_count_hpp */
