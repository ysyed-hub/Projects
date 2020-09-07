//
//  game.cpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cmath>
#include "header.hpp"

using namespace std;

Enemy Goblin(50, 20, 100, 50);
Enemy Wolf(250, 70, 250, 200);
Enemy Troll(1000, 200, 800, 500);
Enemy Giant(5500, 1000, 1500, 1000);
Enemy Dragon(12000, 2000, 0, 0);


void Character::ShowStats () {
    cout << "\nLevel: " << level_ << endl;
    cout << "Health: " << health_ << endl;
    cout << "Physical Damage: " << attack_damage_ << endl;
    cout << "Magic Damage: " << magic_damage_ << endl;
    cout << "Gold: " << gold_ << endl;
    cout << "Exp: " << exp_ << endl;
}

Character::Character(int type, int health, int attack_damage, int magic_damage) : type_(type), health_(health), attack_damage_(attack_damage), magic_damage_(magic_damage), gold_(0), exp_(0), level_(1) {}

int Character::DamageUpgrade() {
    gold_ -= 50;
    if (attack_damage_ == 0) {
        magic_damage_ += 20;
        return magic_damage_;
    }
    attack_damage_ += 20;
    return attack_damage_;
}

int Character::HealthUpgrade() {
    health_ += 40;
    gold_ -= 50;
    return health_;
}

int Character::ExpGain(int experience_gain) {
    exp_ += experience_gain;
    return exp_;
}

int Character::GoldGain(int gold_gain) {
    gold_ += gold_gain;
    return gold_;
}

void Character::LevelUp(int type_) {
    double x = 100 * pow(1.1, level_);
    int level_up_exp = x;
    while (exp_ > level_up_exp) {
        if (type_ == 1) {
            health_ += 25;
            magic_damage_ += 10;
        }
        if (type_ == 2) {
            health_ += 40;
            attack_damage_ += 5;
        }
        if (type_ == 3) {
            health_ += 20;
            attack_damage_ += 12;
        }
        exp_ -= level_up_exp;
        level_++;
        level_up_exp *= 1.1;
    }
    cout << "\nCongrats! You have leveled up to level " << level_ << "." << endl;
}


bool Character::BattleBoss(Enemy enemy_fought) {
    int user_health = CharacterHealth();
    int user_attack = CharacterAttack();
    int enemy_health = enemy_fought.EnemyHealth();
    int enemy_attack = enemy_fought.EnemyAttack();
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

void Character::Battle(Enemy enemy_fought, string enemy_type) {
    int user_health = CharacterHealth();
    int user_attack = CharacterAttack();
    int enemy_health = enemy_fought.EnemyHealth();
    int enemy_attack = enemy_fought.EnemyAttack();
    int experience = enemy_fought.EnemyExperience();
    int gold = enemy_fought.EnemyGold();
    while (user_health > 0 && enemy_health > 0) {
        user_health -= enemy_attack;
        enemy_health -= user_attack;
    }
    if (user_health > 0) {
        cout << "\nYou have defeated the " << enemy_type << "!" << endl;
        cout << "You are rewarded " << gold << " gold and " << experience << " experience." << endl;
        GoldGain(gold);
        ExpGain(experience);
        return;
    }
    cout << "\nYou have been defeated by the " << enemy_type << ", please come back once you have become stronger." << endl;
    return;
}


bool Character::Adventure() {
    bool game_complete = false;
    int adventure_choice = AdventureMenu();
    switch (adventure_choice) {
        case 1:
            Battle(Goblin, "goblins");
            break;
        case 2:
            Battle(Wolf, "wolves");
            break;
        case 3:
            Battle(Troll, "trolls");
            break;
        case 4:
            Battle(Giant, "giant");
            break;
        case 5:
            game_complete = BattleBoss(Dragon);
            break;
    }
    LevelUp(HeroType());
    return game_complete;
}

int Character::AdventureMenu() {
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

void Character::Upgrade() {
    cout << "\n";
    if (GoldCount() < 50) {
        cout << "Not enough gold to make any upgrades." << endl;
        return;
    }
    int upgrade_choice;
    while ((upgrade_choice = UpgradeMenu()) != 3) {
        
        if (upgrade_choice == 1) {
            cout << "Your health has been increased to " << HealthUpgrade() << "." << endl;
        }
        if (upgrade_choice == 2) {
            cout << "Your damage has been increased to " << DamageUpgrade() << "." << endl;
        }
        GoldGain(-50);
        if (GoldCount() < 50) {
            cout << "\nNot enough gold to make any additional upgrades." << endl;
            return;
        }
    }
    cout << "Thank you for coming!\n";
}

int Character::UpgradeMenu() {
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



int Character::Introduction(string username) {
    cout << "\nWelcome " << username << ", you are assigned the task of defeating the great dragon that wreaks havoc on the lands.\n" << endl;
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

int Character::Menu() {
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

Enemy::Enemy(int health, int attack, int gold, int experience) : health_(health), attack_(attack), gold_(gold), experience_(experience) {}

