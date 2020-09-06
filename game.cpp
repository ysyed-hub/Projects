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
    cout << "\nLevel: " << level_ << endl;
    cout << "Health: " << health_ << endl;
    cout << "Physical Damage: " << attack_damage_ << endl;
    cout << "Magic Damage: " << magic_damage_ << endl;
    cout << "Gold: " << gold_ << endl;
    cout << "Exp: " << exp_ << endl;
}

Character::Character(int w, int x, int y, int z) {
    type_ = w;
    health_ = x;
    attack_damage_ = y;
    magic_damage_ = z;
    gold_ = 0;
    exp_ = 0;
    level_ = 1;
}

int Character::DamageUpgrade(void) {
    gold_ -= 50;
    if (attack_damage_ == 0) {
        magic_damage_ += 20;
        return magic_damage_;
    }
    attack_damage_ += 20;
    return attack_damage_;
}

int Character::HealthUpgrade(void) {
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

Enemy::Enemy(int x, int y, int z, int w) {
    health_ = x;
    attack_ = y;
    gold_ = z;
    experience_ = w;
}
