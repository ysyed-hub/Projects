
//
//  Text Adventure Game.cpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "header.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    
    Character User(1, 0, 0, 0);
    User.InitializeUser();
    User.PlayGame();
    
   
    return 0;
}

