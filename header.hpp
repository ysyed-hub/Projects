//
//  header.hpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef header_hpp
#define header_hpp
using namespace std;

class Enemy { // Goblin, Wolf, Troll, Giant, Dragon
    int health_;
    int attack_;
    int gold_;
    int experience_;

public:
    Enemy(int health, int attack, int gold, int experience);
    int EnemyGold(void) {return gold_;}
    int EnemyHealth(void) {return health_;}
    int EnemyAttack(void) {return attack_;}
    int EnemyExperience(void) {return experience_;}
};


class Character { // Sorcerer, Warrior, Ranger
  
    int type_;
    int health_;
    int attack_damage_;
    int magic_damage_;
    int gold_;
    int exp_;
    int level_;
    
public:
    int HeroType(void) {return type_;}
    int GoldCount(void) {return gold_;}
    int CharacterHealth(void) {return health_;}
    int CharacterAttack(void) {return (attack_damage_ > 0 ? attack_damage_ : magic_damage_);}
    void ShowStats(void);
    Character(int type, int health, int attack_damage, int magic_damage);
    int DamageUpgrade(void);
    int HealthUpgrade(void);
    int ExpGain (int experience_gain);
    int GoldGain (int gold_gain);
    void LevelUp (int type_);
    int Introduction(string username);
    int Menu();
    void Upgrade();
    int UpgradeMenu();
    bool Adventure();
    int AdventureMenu();
    void Battle(Enemy enemy_fought, string enemy_type);
    bool BattleBoss(Enemy enemy_fought);
    
};


#endif /* header_hpp */
