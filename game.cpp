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
#include "game.hpp"

using namespace std;

void Character::PlayGame () {
    
    enum MenuOptions {kGoOnAdventure = 1, kUpgradeUser, kShowUserStats, kLeaveGame};
    
    bool final_boss = false; // Final boss has not been defeated
    bool leave_game = false;
       
    while (final_boss == false && leave_game == false) {
           
        switch (Menu()) {
            case kGoOnAdventure:
                final_boss = Adventure();
                break;
            case kUpgradeUser:
                Upgrade();
                break;
            case kShowUserStats:
                ShowStats();
                break;
            case kLeaveGame:
                leave_game = true;
                break;
        }
    }
       
    if (final_boss == true) {
        // ending credits
    }
    cout << "\nThanks for playing!\n" << endl;
}

void Character::ShowStats () const {
    cout << "\nLevel: " << level_ << endl;
    cout << "Health: " << health_ << endl;
    cout << "Physical Damage: " << physical_damage_ << endl;
    cout << "Magic Damage: " << magic_damage_ << endl;
    cout << "Gold: " << gold_ << endl;
    cout << "Exp: " << exp_ << endl;
}

Character::Character(int type, int health, int physical_damage, int magic_damage) : type_(type), health_(health), physical_damage_(physical_damage), magic_damage_(magic_damage), gold_(0), exp_(0), level_(1) {}

int Character::DamageUpgrade() {
    gold_ -= 50;
    if (physical_damage_ == 0) {
        magic_damage_ += 20;
        return magic_damage_;
    }
    physical_damage_ += 20;
    return physical_damage_;
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
    enum characterType {Sorcerer = 1, Warrior, Ranger};
    double x = 100 * pow(1.1, level_);
    int level_up_exp = x;
    while (exp_ > level_up_exp) {
        switch (type_) {
            case Sorcerer:
                health_ += 25;
                magic_damage_ += 10;
            case Warrior:
                health_ += 40;
                physical_damage_ += 5;
            case Ranger:
                health_ += 20;
                physical_damage_ += 12;
        }
       
        exp_ -= level_up_exp;
        level_++;
        level_up_exp *= 1.1;
    }
    cout << "\nCongrats! You have leveled up to level " << level_ << "." << endl;
}


bool Character::BattleFinalBoss(Enemy enemy_fought) const {
    int user_health = CharacterHealth();
    int user_attack = CharacterAttack();
    int enemy_health = enemy_fought.health;
    int enemy_attack = enemy_fought.attack;
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
    int enemy_health = enemy_fought.health;
    int enemy_attack = enemy_fought.attack;
    int experience = enemy_fought.experience;
    int gold = enemy_fought.gold;
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
    
    enum EnemyType {kEnemyGoblin = 1, kEnemyWolf, kEnemyTroll, kEnemyGiant, kEnemyDragon};
    const Enemy Goblin = {50, 20, 100, 50};
    const Enemy Wolf = {250, 70, 250, 200};
    const Enemy Troll = {1000, 200, 800, 500};
    const Enemy Giant = {5500, 1000, 1500, 1000};
    const Enemy Dragon = {12000, 2000, 0, 0};
    
    bool game_complete = false;
    switch (AdventureMenu()) {
        case kEnemyGoblin:
            Battle(Goblin, "goblins");
            break;
        case kEnemyWolf:
            Battle(Wolf, "wolves");
            break;
        case kEnemyTroll:
            Battle(Troll, "trolls");
            break;
        case kEnemyGiant:
            Battle(Giant, "giant");
            break;
        case kEnemyDragon:
            game_complete = BattleFinalBoss(Dragon);
            break;
    }
    LevelUp(HeroType());
    return game_complete;
}

int Character::AdventureMenu() const {
    cout << "\nWhat type of adventure do you plan on going on?\n" << endl;
    cout << "1) Fight the goblins that reside in the northern caves." << endl;
    cout << "2) Destroy the pack of wolves in the forest" << endl;
    cout << "3) Takeout the trolls in the valley." << endl;
    cout << "4) Challenge a giant." << endl;
    cout << "5) Defeat the great dragon\n" << endl;
    cout << "Enter the number of the option you wish to choose: ";
    string adventure_choice;
    cin >> adventure_choice;
    while (adventure_choice != "1" && adventure_choice != "2" && adventure_choice != "3" && adventure_choice != "4" && adventure_choice != "5") {
        cout << "\nImproper input, please choose either 1, 2, 3, 4 or 5: ";
        cin >> adventure_choice;
    }
    if (adventure_choice == "1") // Fight goblins
        return 1;
    if (adventure_choice == "2") // Fight wolves
        return 2;
    if (adventure_choice == "3") // Fight trolls
        return 3;
    if (adventure_choice == "4") // Fight giant
        return 4;
    return 5;                    // Fight dragon
}

void Character::Upgrade() {
    
    enum UpgradeOption {kHealthUpgrade = 1, kDamageUpgrade, kLeave};
    
    cout << "\n";
    if (GoldCount() < 50) {
        cout << "Not enough gold to make any upgrades." << endl;
        return;
    }
    int upgrade_choice;
    while ((upgrade_choice = UpgradeMenu()) != kLeave) {
        
        if (upgrade_choice == kHealthUpgrade) {
            cout << "Your health has been increased to " << HealthUpgrade() << "." << endl;
        }
        if (upgrade_choice == kDamageUpgrade) {
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

int Character::UpgradeMenu() const {
    cout << "You can increase your maximum health by 40 or increase your attack by 20 for 50 gold." << endl;
    cout << "Enter 1 to increase health, 2 to increase attack or 3 to leave: ";
    string upgrade_menu_choice;
    cin >> upgrade_menu_choice;
    while (upgrade_menu_choice != "1" && upgrade_menu_choice != "2" && upgrade_menu_choice != "3") {
        cout << "\nImproper input, please choose either 1, 2, or 3: ";
        cin >> upgrade_menu_choice;
    }
    if (upgrade_menu_choice == "1") // Upgrade health
        return 1;
    if (upgrade_menu_choice == "2") // Upgrade attack
        return 2;
    return 3;                       // Leave upgrade shop
}



void Character::Initialize() {
    cout << "Welcome to my text adventure game." << endl;
    cout << "Enter your name: ";
    string username;
    cin >> username;
    SetName(username);
    cout << "\nWelcome " << username << ", you are assigned the task of defeating the great dragon that wreaks havoc on the lands.\n" << endl;
    cout << "At the moment, you are far too weak to defeat the dragon." << endl;
    cout << "Strengthen yourself by defeating monsters and upgrading your equipment." << endl;
    cout << "Before heading out, you must choose from one of the three character types:\n" << endl;
    cout << "1. Sorcerer, HP: 200 + 25 per level, Magic Damage: 100 + 10 per level" << endl;
    cout << "2. Warrior, HP: 250 + 40 per level, Physical Damage: 70 + 7 per level" << endl;
    cout << "3. Ranger, HP: 150 + 20 per level, Physical Damage: 120 + 12 per level\n" << endl;
    cout << "Enter the number representing your choice of character type: ";
    string user_type;
    cin >> user_type;
    
    while (user_type != "1" && user_type != "2" && user_type != "3") {
        cout << "\nImproper input, please choose either 1, 2, or 3: ";
        cin >> user_type;
    }
    
    int user_health, user_physical_damage, user_magic_damage;
    
    enum CharacterType {kSorcerer = 1, kWarrior, kRanger};
    
    if (user_type == "1") { // Sorcerer
        SetType(kSorcerer);
        user_health = 200;
        user_physical_damage = 0;
        user_magic_damage = 100;
    }
    if (user_type == "2") { // Warrior
        SetType(kWarrior);
        user_health = 250;
        user_physical_damage = 70;
        user_magic_damage = 0;
    }
    if (user_type == "3") { // Ranger
        SetType(kRanger);
        user_health = 150;
        user_physical_damage = 120;
        user_magic_damage = 0;
    }
    
    SetHealth(user_health);
    SetPhysicalDamage(user_physical_damage);
    SetMagicDamage(user_magic_damage);

    
}

void Character::SetName(string username) {
    name_ = username;
}

void Character::SetType(int user_type) {
    type_ = user_type;
}

void Character::SetPhysicalDamage(int user_physical_damage) {
    physical_damage_ = user_physical_damage;
}

void Character::SetMagicDamage(int user_magic_damage) {
    magic_damage_ = user_magic_damage;
}

void Character::SetHealth(int user_health) {
    health_ = user_health;
}

int Character::Menu() {
    cout << "\n1: Go on adventure" << endl;
    cout << "2: Upgrade equipment" << endl;
    cout << "3: Show character stats" << endl;
    cout << "4: Leave game\n" << endl;
    cout << "Enter the number of the option you choose: ";
    string menu_choice;
    cin >> menu_choice;
    while (menu_choice != "1" && menu_choice != "2" && menu_choice != "3" && menu_choice != "4") {
        cout << "\nImproper input, please choose either 1, 2, 3 or 4: ";
        cin >> menu_choice;
    }
    if (menu_choice == "1") // Go on adventure
        return 1;
    if (menu_choice == "2") // Upgrade equipment
        return 2;
    if (menu_choice == "3") // Show character status
        return 3;
    return 4;     // Leave game
}


