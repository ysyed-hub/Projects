//
//  main.cpp
//  elevator_simulator
//
//  Created by Yunus Syed on 10/10/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "elevator.hpp"

int main(int argc, const char * argv[]) {
    
    
    if (argc == 1) {
        std::cout << "No input file detected" << std::endl;
        return 0;
    }
    
    Elevator elevator;
    std::ifstream elevator_info (argv[1]);
    elevator.RunElevator(elevator_info);
    
    return 0;
}
