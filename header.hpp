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
    Enemy(int health, int attack, int gold, int experience) : health_(health), attack_(attack), gold_(gold), experience_(experience) {};
    int EnemyGold() {return gold_;}
    int EnemyHealth() {return health_;}
    int EnemyAttack() {return attack_;}
    int EnemyExperience() {return experience_;}
};


class Character { // Sorcerer, Warrior, Ranger
  
    int type_;
    int health_;
    int physical_damage_;
    int magic_damage_;
    int gold_;
    int exp_;
    int level_;
    string name_;
    
public:
    void SetName(string username);
    void SetType(int user_type);
    void SetPhysicalDamage(int user_physical_damage);
    void SetMagicDamage(int user_magic_damage);
    void SetHealth(int user_health);
    int HeroType() {return type_;}
    int GoldCount() {return gold_;}
    int CharacterHealth() {return health_;}
    int CharacterAttack() {return (physical_damage_ > 0 ? physical_damage_ : magic_damage_);}
    void ShowStats();
    Character(int type, int health, int physical_damage, int magic_damage);
    int DamageUpgrade();
    int HealthUpgrade();
    int ExpGain (int experience_gain);
    int GoldGain (int gold_gain);
    void LevelUp (int type_);
    void InitializeUser();
    int Menu();
    void Upgrade();
    int UpgradeMenu();
    bool Adventure();
    int AdventureMenu();
    void Battle(Enemy enemy_fought, string enemy_type);
    bool BattleBoss(Enemy enemy_fought);
    void PlayGame();
    
};


#endif /* header_hpp */
