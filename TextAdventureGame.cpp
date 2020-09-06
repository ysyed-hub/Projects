
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
using namespace std;

int Introduction(string *p);
int Menu(void);
void Upgrade(Character *p);
int UpgradeMenu(void);
bool Adventure(Character *p);
int AdventureMenu(void);
void Battle(Character *p, Enemy q, string enemy_type);
bool BattleBoss(Character *p, Enemy q);
Enemy Goblin(50, 20, 100, 50);
Enemy Wolf(250, 70, 250, 200);
Enemy Troll(1000, 200, 800, 500);
Enemy Giant(5500, 1000, 1500, 1000);
Enemy Dragon(12000, 2000, 0, 0);

int main(int argc, const char * argv[]) {
    string char_name;
    string *p = &char_name;
    int char_type = Introduction(p);
    int x, y, z;
    if (char_type == 1) {
        
        x = 200;
        y = 0;
        z = 100;
    }
    if (char_type == 2) {
        x = 250;
        y = 70;
        z = 0;
    }
    if (char_type == 3) {
        x = 150;
        y = 120;
        z = 0;
    }
    
    Character User(char_type, x, y ,z);
    Character *p_user = &User;
    bool final_boss = false; // Final boss has not been defeated
    bool leave_game = false;
    
    while (final_boss == false && leave_game == false) {
        
        int user_choice = Menu();
        switch (user_choice) {
            case 1:
                final_boss = Adventure(p_user);
                break;
            case 2:
                Upgrade(p_user);
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

int Menu(void) {
    cout << "\n1: Go on adventure" << endl;
    cout << "2: Upgrade equipment" << endl;
    cout << "3: Show character stats" << endl;
    cout << "4: Leave game\n" << endl;
    cout << "Enter the number of the option you choose: ";
    string x;
    cin >> x;
    while (x != "1" && x != "2" && x != "3" && x != "4") {
        cout << "\nImproper input, please choose either 1, 2, 3 or 4: ";
        cin >> x;
    }
    if (x == "1")
        return 1;
    if (x == "2")
        return 2;
    if (x == "3")
        return 3;
    return 4;
}

bool Adventure(Character *p) {
    bool game_complete = false;
    int adventure_choice = AdventureMenu();
    switch (adventure_choice) {
        case 1:
            Battle(p, Goblin, "goblins");
            break;
        case 2:
            Battle(p, Wolf, "wolves");
            break;
        case 3:
            Battle(p, Troll, "trolls");
            break;
        case 4:
            Battle(p, Giant, "giant");
            break;
        case 5:
            game_complete = BattleBoss(p, Dragon);
            break;
    }
    p -> LevelUp(p -> HeroType());
    return game_complete;
}

int AdventureMenu(void) {
    cout << "\nWhat type of adventure do you plan on going on?\n" << endl;
    cout << "1) Fight the goblins that reside in the northern caves." << endl;
    cout << "2) Destroy the pack of wolves in the forest" << endl;
    cout << "3) Takeout the trolls in the valley." << endl;
    cout << "4) Challenge a giant." << endl;
    cout << "5) Defeat the great dragon\n" << endl;
    cout << "Enter the number of the option you wish to choose: ";
    string x;
    cin >> x;
    while (x != "1" && x != "2" && x != "3" && x != "4" && x != "5") {
        cout << "\nImproper input, please choose either 1, 2, 3, 4 or 5: ";
        cin >> x;
    }
    if (x == "1")
        return 1;
    if (x == "2")
        return 2;
    if (x == "3")
        return 3;
    if (x == "4")
        return 4;
    return 5;
}

void Upgrade(Character *p) {
    cout << "\n";
    if (p -> GoldCount() < 50) {
        cout << "Not enough gold to make any upgrades." << endl;
        return;
    }
    int upgrade_choice;
    while ((upgrade_choice = UpgradeMenu()) != 3) {
        
        if (upgrade_choice == 1) {
            cout << "Your health has been increased to " << p -> HealthUpgrade() << "." << endl;
        }
        if (upgrade_choice == 2) {
            cout << "Your damage has been increased to " << p -> DamageUpgrade() << "." << endl;
        }
        p -> GoldGain(-50);
        if (p -> GoldCount() < 50) {
            cout << "\nNot enough gold to make any additional upgrades." << endl;
            return;
        }
    }
    cout << "Thank you for coming!\n";
}

int UpgradeMenu(void) {
    cout << "You can increase your maximum health by 40 or increase your attack by 20 for 50 gold." << endl;
    cout << "Enter 1 to increase health, 2 to increase attack or 3 to leave: ";
    string x;
    cin >> x;
    while (x != "1" && x != "2" && x != "3") {
        cout << "\nImproper input, please choose either 1, 2, or 3: ";
        cin >> x;
    }
    if (x == "1")
        return 1;
    if (x == "2")
        return 2;
    return 3;
}

bool BattleBoss(Character *p, Enemy q) {
    int user_health = p -> CharacterHealth();
    int user_attack = p -> CharacterAttack();
    int enemy_health = q.EnemyHealth();
    int enemy_attack = q.EnemyAttack();
    while (user_health > 0 && enemy_health > 0) {
        user_health -= enemy_attack;
        enemy_health -= user_attack;
    }
    if (user_health > 0) {
        cout << "\nYou have defeated the dragon!" << endl;
        return true;
    }
    cout << "\nYou have been defeated by the dragon, please come back once you have become stronger." << endl;
    return false;
}

void Battle(Character *p, Enemy q, string enemy_type) {
    int user_health = p -> CharacterHealth();
    int user_attack = p -> CharacterAttack();
    int enemy_health = q.EnemyHealth();
    int enemy_attack = q.EnemyAttack();
    int experience = q.EnemyExperience();
    int gold = q.EnemyGold();
    while (user_health > 0 && enemy_health > 0) {
        user_health -= enemy_attack;
        enemy_health -= user_attack;
    }
    if (user_health > 0) {
        cout << "\nYou have defeated the " << enemy_type << "!" << endl;
        cout << "You are rewarded " << gold << " gold and " << experience << " experience." << endl;
        p -> GoldGain(gold);
        p -> ExpGain(experience);
        return;
    }
    cout << "\nYou have been defeated by the " << enemy_type << ", please come back once you have become stronger." << endl;
    return;
}



int Introduction(string *p) {
    cout << "Welcome to my text adventure game." << endl;
    cout << "Enter your name: ";
    string s;
    cin >> s;
    *p = s;
    cout << "\nWelcome " << *p << ", you are assigned the task of defeating the great dragon that wreaks havoc on the lands.\n" << endl;
    cout << "At the moment, you are far too weak to defeat the dragon." << endl;
    cout << "Strengthen yourself by defeating monsters and upgrading your equipment." << endl;
    cout << "Before heading out, you must choose from one of the three character types:\n" << endl;
    cout << "1. Sorcerer, HP: 200 + 25 per level, Magic Damage: 100 + 10 per level" << endl;
    cout << "2. Warrior, HP: 250 + 40 per level, Physical Damage: 70 + 7 per level" << endl;
    cout << "3. Ranger, HP: 150 + 20 per level, Physical Damage: 120 + 12 per level\n" << endl;
    cout << "Enter the number representing your choice of character type: ";
    string x;
    cin >> x;
    
    while (x != "1" && x != "2" && x != "3") {
        cout << "\nImproper input, please choose either 1, 2, or 3: ";
        cin >> x;
    }
    if (x == "1")
        return 1;
    if (x == "2")
        return 2;
    return 3;
    
}
