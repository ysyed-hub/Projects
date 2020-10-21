//
//  test.cpp
//  
//
//  Created by Yunus Syed on 9/18/20.
//

#include <stdio.h>
#include "game.hpp"

void SetName(string username);
void SetType(int user_type);
void SetPhysicalDamage(int user_physical_damage);
void SetMagicDamage(int user_magic_damage);
void SetHealth(int user_health);
int HeroType() const {return type_;}
int GoldCount() const {return gold_;}
int CharacterHealth() const {return health_;}
int CharacterAttack() const {return (physical_damage_ > 0 ? physical_damage_ : magic_damage_);}
void ShowStats() const;
Character(int type, int health, int physical_damage, int magic_damage);
int DamageUpgrade();
int HealthUpgrade();
int ExpGain (int experience_gain);
int GoldGain (int gold_gain);
void LevelUp (int type_);
void Initialize();
int Menu();
void Upgrade();
int UpgradeMenu() const;
bool Adventure();
int AdventureMenu() const;
void Battle(Enemy enemy_fought, string enemy_type);
bool BattleFinalBoss(Enemy enemy_fought) const;
void PlayGame();

void TestSetName();
void TestSetType();
void TestSetPhysicalDamage();
void TestSetMagicDamage();
void TestSetHealth();
void 

int main() {
    
}
