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

void Character::ShowStats (void) {
    cout << "\nLevel: " << level << endl;
    cout << "Health: " << health << endl;
    cout << "Physical Damage: " << attack_damage << endl;
    cout << "Magic Damage: " << magic_damage << endl;
    cout << "Gold: " << gold << endl;
    cout << "Exp: " << exp << endl;
}

Character::Character(int w, int x, int y, int z) {
    type = w;
    health = x;
    attack_damage = y;
    magic_damage = z;
    gold = 0;
    exp = 0;
    level = 1;
}

int Character::DamageUpgrade(void) {
    gold -= 50;
    if (attack_damage == 0) {
        magic_damage += 20;
        return magic_damage;
    }
    attack_damage += 20;
    return attack_damage;
}

int Character::HealthUpgrade(void) {
    health += 40;
    gold -= 50;
    return health;
}

int Character::ExpGain(int experience_gain) {
    exp += experience_gain;
    return exp;
}

int Character::GoldGain(int gold_gain) {
    gold += gold_gain;
    return gold;
}

void Character::LevelUp(int type) {
    double x = 100 * pow(1.1, level);
    int level_up_exp = x;
    while (exp > level_up_exp) {
        if (type == 1) {
            health += 25;
            magic_damage += 10;
        }
        if (type == 2) {
            health += 40;
            attack_damage += 5;
        }
        if (type == 3) {
            health += 20;
            attack_damage += 12;
        }
        exp -= level_up_exp;
        level++;
        level_up_exp *= 1.1;
    }
    cout << "\nCongrats! You have leveled up to level " << level << "." << endl;
}

Enemy::Enemy(int x, int y, int z, int w) {
    health = x;
    attack = y;
    gold = z;
    experience = w;
}
