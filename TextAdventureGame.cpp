//
//  Text Adventure Game.cpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "game.cpp"
#include "header.hpp"
#include "games.cpp"
#include "games.hpp"
using namespace std;


int main(int argc, const char * argv[]) {
    Game Tag;
    string char_name;
    int char_type = Tag.Introduction(&char_name);
    int char_health, char_physical_damage, char_magic_damage;
    if (char_type == 1) {
        char_health = 200;
        char_physical_damage = 0;
        char_magic_damage = 100;
    }
    if (char_type == 2) {
        char_health = 250;
        char_physical_damage = 70;
        char_magic_damage = 0;
    }
    if (char_type == 3) {
        char_health = 150;
        char_physical_damage = 120;
        char_magic_damage = 0;
    }
    
    Tag(char_name, char_type, char_health, char_physical_damage , char_magic_damage);
    bool final_boss = false; // Final boss has not been defeated
    bool leave_game = false;
    Character *Player = Tag.UserInfo;
    
    while (final_boss == false && leave_game == false) {
        
        int user_choice = Tag.Menu();
        switch (user_choice) {
            case 1:
                final_boss = Tag.Adventure(Player);
                break;
            case 2:
                Tag.Upgrade(Player);
                break;
            case 3:
                (Player) -> ShowStats();
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

