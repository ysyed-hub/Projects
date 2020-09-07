
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
    Character Null_User(1, 0, 0, 0);
    cout << "Welcome to my text adventure game." << endl;
    cout << "Enter your name: ";
    string user_name;
    cin >> user_name;
    
    int user_type = Null_User.Introduction(user_name);
    int user_health, user_physical_damage, user_magic_damage;
    if (user_type == 1) {
        user_health = 200;
        user_physical_damage = 0;
        user_magic_damage = 100;
    }
    if (user_type == 2) {
        user_health = 250;
        user_physical_damage = 70;
        user_magic_damage = 0;
    }
    if (user_type == 3) {
        user_health = 150;
        user_physical_damage = 120;
        user_magic_damage = 0;
    }
    
    Character User(user_type, user_health, user_physical_damage, user_magic_damage);
    bool final_boss = false; // Final boss has not been defeated
    bool leave_game = false;
    
    while (final_boss == false && leave_game == false) {
        
        int user_choice = User.Menu();
        switch (user_choice) {
            case 1:
                final_boss = User.Adventure();
                break;
            case 2:
                User.Upgrade();
                break;
            case 3:
                User.ShowStats();
                break;
            case 4:
                leave_game = true;
                break;
        }
    }
    
    if (final_boss == true) {
        // ending credits
    }
    cout << "\nThanks for playing!\n" << endl;
    return 0;
}

