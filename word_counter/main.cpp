//
//  main.cpp
//  word_count
//
//  Created by Yunus Syed on 9/8/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "word_count.hpp"



int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        std::cout << "error\n";
        return 0;
    }
    
    std::ifstream file(argv[1]);
    std::ifstream *fileptr = &file;
    
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return 0;
    }
    WordCount example(fileptr);
    example.PrintWordsAndCount();

    return 0;
}

