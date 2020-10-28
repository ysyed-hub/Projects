//
//  main.cpp
//  escalator_simulator
//
//  Created by Yunus Syed on 10/26/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include "escalator.hpp"
#include <fstream>


int main(int argc, const char * argv[]) {
    
    if (argc < 2) {
        std::cout << "No input file detected." << std::endl;
        return 1;
    }
    
    std::ifstream escalator_info(argv[1]);
    
    Escalator escalator;
    escalator.RunEscalator(escalator_info);
    
    return 0;
}
