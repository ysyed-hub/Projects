
//
//  Text Adventure Game.cpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "game.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    
    Character user(1, 0, 0, 0);
    user.Initialize();
    user.PlayGame();
    
   
    return 0;
}

