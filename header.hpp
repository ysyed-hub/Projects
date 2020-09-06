//
//  header.hpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/5/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef header_hpp
#define header_hpp

class Character { // Sorcerer, Warrior, Ranger
  
    int type;
    int health;
    int attack_damage;
    int magic_damage;
    int gold;
    int exp;
    int level;
    
public:
    int HeroType(void) {return type;}
    int GoldCount(void) {return gold;}
    int CharacterHealth(void) {return health;}
    int CharacterAttack(void) {return (attack_damage > 0 ? attack_damage : magic_damage);}
    void ShowStats(void);
    Character(int w, int x, int y, int z);
    int DamageUpgrade(void);
    int HealthUpgrade(void);
    int ExpGain (int experience_gain);
    int GoldGain (int gold_gain);
    void LevelUp (int type);
    
};

class Enemy { // Goblin, Wolf, Troll, Giant, Dragon
    int health;
    int attack;
    int gold;
    int experience;

public:
    Enemy(int w, int x, int y, int z);
    int EnemyGold(void) {return gold;}
    int EnemyHealth(void) {return health;}
    int EnemyAttack(void) {return attack;}
    int EnemyExperience(void) {return experience;}
};


#endif /* header_hpp */
