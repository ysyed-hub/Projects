//
//  games.hpp
//  
//
//  Created by Yunus Syed on 9/6/20.
//

#ifndef games_hpp
#define games_hpp

#include <stdio.h>
using namespace std;

class Game {
private:
    string username_;
    Character User;
    
public:
    Game(string username, Character Player);
    int Introduction(string &username);
    int Menu();
    void Upgrade(Character *User);
    int UpgradeMenu();
    bool Adventure(Character *User);
    int AdventureMenu();
    void Battle(Character *User, Enemy q, string enemy_type);
    bool BattleBoss(Character *User, Enemy q);
    Character *UserInfo ();
};


#endif /* games_hpp */
