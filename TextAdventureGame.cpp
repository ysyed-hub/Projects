//
//  main.cpp
//  Text Adventure Game
//
//  Created by Yunus Syed on 9/1/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include <iostream>

using namespace std;

class Character { // Sorcerer, Wariror, Ranger
  
    int Health;
    int Attack_Damage;
    int Magic_Damage;
    int Gold;
    int Exp;
    int Level;
    
public:
    void Show_Stats (void) {
        cout << "\nLevel: " << Level << endl;
        cout << "Health: " << Health << endl;
        cout << "Physical Damage: " << Attack_Damage << endl;
        cout << "Magic Damage: " << Magic_Damage << endl;
        cout << "Gold: " << Gold << endl;
        cout << "Exp: " << Exp << endl;

    }
    
    Character(int x, int y, int z) {
        Health = x;
        Attack_Damage = y;
        Magic_Damage = z;
        Gold = 0;
        Exp = 0;
        Level = 1;
    }
    
    int Damage_Upgrade(void) {
        Gold -= 50;
        if (Attack_Damage == 0) {
            Magic_Damage += 20;
            return Magic_Damage;
        }
        Attack_Damage += 20;
        return Attack_Damage;
    }
    
    int Health_Upgrade(void) {
        Health += 40;
        Gold -= 50;
        return Health;
    }
    int Gold_Count(void) {return Gold;}
    int Character_Health(void) {return Health;}
    int Character_Attack(void) {return (Attack_Damage > 0 ? Attack_Damage : Magic_Damage);}
    int Exp_Gain(int experience_gain) {
        Exp += experience_gain;
        return Exp;
    }
    int Gold_Gain(int gold_gain) {
        Gold += gold_gain;
        return Gold;
    }
    
    void Level_Up(int type, int Level_Up_Exp) {
        if (type == 1) {
            Health += 25;
            Magic_Damage += 10;
        }
        if (type == 2) {
            Health += 40;
            Attack_Damage += 5;
        }
        if (type == 3) {
            Health += 20;
            Attack_Damage += 12;
        }
        Level++;
        Exp -= Level_Up_Exp;
    }
    
};

typedef Character *characterptr;

class Enemy { // Goblin, Wolf, Troll, Giant, Dragon
    int Health;
    int Attack;
    int Gold;
    int Experience;
    
public:
    Enemy(int x, int y, int z, int w) {
        Health = x;
        Attack = y;
        Gold = z;
        Experience = w;
    }
    int Enemy_Gold(void) {return Gold;}
    int Enemy_Health(void) {return Health;}
    int Enemy_Attack(void) {return Attack;}
    int Enemy_Experience(void) {return Experience;}
};

typedef Enemy *enemyptr;


int introduction(string *p);
int menu(void);
void upgrade(characterptr p);
int upgrade_menu(void);
bool adventure(characterptr p);
int adventure_menu(void);
void battle(characterptr p, Enemy q, string enemy_type);
bool battle_boss(characterptr p, Enemy q);
Enemy Goblin(50, 20, 100, 50);
Enemy Wolf(250, 70, 250, 200);
Enemy Troll(1000, 200, 800, 500);
Enemy Giant(5500, 1000, 1500, 1000);
Enemy Dragon(12000, 2000, 0, 0);

int main(int argc, const char * argv[]) {
    string Char_Name;
    string *p = &Char_Name;
    int Char_Type = introduction(p);
    int x, y, z;
    if (Char_Type == 1) {
        x = 200;
        y = 0;
        z = 100;
    }
    if (Char_Type == 2) {
        x = 250;
        y = 70;
        z = 0;
    }
    if (Char_Type == 3) {
        x = 150;
        y = 120;
        z = 0;
    }
    
    Character User(x, y ,z);
    characterptr pUser = &User;
    bool Final_Boss = false; // Final boss has not been defeated
    bool Leave_Game = false;
    
    while (Final_Boss == false && Leave_Game == false) {
        
        int User_Choice = menu();
        switch (User_Choice) {
            case 1:
                Final_Boss = adventure(pUser);
                break;
            case 2:
                upgrade(pUser);
                break;
            case 3:
                User.Show_Stats();
                break;
            case 4:
                Leave_Game = true;
                break;
            default:
                cout << "Improper input, please enter your choice again: ";
                break;
        }
    }
    
    if (Final_Boss == true) {
        // ending credits
    }
    
    cout << "Thanks for playing!" << endl;
    
    return 0;
}

int menu(void) {
    cout << "\n1: Go on adventure" << endl;
    cout << "2: Upgrade equipment" << endl;
    cout << "3: Show character stats" << endl;
    cout << "4: Leave game\n" << endl;
    cout << "Enter the number of the option you choose: ";
    int x;
    cin >> x;
    return x;
}

bool adventure(characterptr p) {
    bool game_complete = false;
    int adventure_choice = adventure_menu();
    while (adventure_choice < 1 || adventure_choice > 5) {
        cout << "Invalid input, please enter a valid input: " << endl;
        cin >> adventure_choice;
    }
    switch (adventure_choice) {
        case 1:
            battle(p, Goblin, "goblins");
            break;
        case 2:
            battle(p, Wolf, "wolves");
            break;
        case 3:
            battle(p, Troll, "trolls");
            break;
        case 4:
            battle(p, Giant, "giant");
            break;
        case 5:
            game_complete = battle_boss(p, Dragon);
            break;
    }
    return game_complete;
}

int adventure_menu(void) {
    cout << "\nWhat type of adventure do you plan on going on?\n" << endl;
    cout << "1) Fight the goblins that reside in the northern caves." << endl;
    cout << "2) Destroy the pack of wolves in the forest" << endl;
    cout << "3) Takeout the trolls in the valley." << endl;
    cout << "4) Challenge a giant." << endl;
    cout << "5) Defeat the great dragon\n" << endl;
    cout << "Enter the number of the option you wish to choose: ";
    int x;
    cin >> x;
    return x;
}

void upgrade(characterptr p) {
    if (p -> Gold_Count() < 50) {
        cout << "Not enough gold to make any upgrades." << endl;
        return;
    }
    int upgrade_choice;
    while ((upgrade_choice = upgrade_menu()) != 3) {
        while (upgrade_choice < 1 || upgrade_choice > 3) {
            cout << "Improper input, please enter your choice again: ";
            cin >> upgrade_choice;
        }
        if (upgrade_choice == 1) {
            cout << "Your health has been increased to " << p -> Health_Upgrade() << "." << endl;
        }
        if (upgrade_choice == 2) {
            cout << "Your health has been increased to " << p -> Damage_Upgrade() << "." << endl;
        }
        p -> Gold_Gain(-50);
        if (p -> Gold_Count() < 50) {
            cout << "\nNot enough gold to make any additional upgrades." << endl;
            return;
        }
    }
    cout << "Thank you for coming!\n";
    
    
}

int upgrade_menu(void) {
    cout << "You can increase your maximum health by 40 or increase your attack by 20 for 50 gold." << endl;
    cout << "Enter 1 to increase health, 2 to increase attack or 3 to leave: ";
    int x;
    cin >> x;
    return x;
}

bool battle_boss(characterptr p, Enemy q) {
    int user_health = p -> Character_Health();
    int user_attack = p -> Character_Attack();
    int enemy_health = q.Enemy_Health();
    int enemy_attack = q.Enemy_Attack();
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

void battle(characterptr p, Enemy q, string enemy_type) {
    int user_health = p -> Character_Health();
    int user_attack = p -> Character_Attack();
    int enemy_health = q.Enemy_Health();
    int enemy_attack = q.Enemy_Attack();
    int experience = q.Enemy_Experience();
    int gold = q.Enemy_Gold();
    while (user_health > 0 && enemy_health > 0) {
        user_health -= enemy_attack;
        enemy_health -= user_attack;
    }
    if (user_health > 0) {
        cout << "\nYou have defeated the " << enemy_type << "!" << endl;
        cout << "You are rewarded " << gold << " gold and " << experience << " experience." << endl;
        p -> Gold_Gain(gold);
        p -> Exp_Gain(experience);
        return;
    }
    cout << "\nYou have been defeated by the " << enemy_type << ", please come back once you have become stronger." << endl;
    return;
}



int introduction(string *p) {
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
    int x;
    cin >> x;
    while (x < 1 || x > 3) {
        cout << "Improper input, please choose either 1, 2, or 3: ";
        cin >> x;
    }
    return x;
    
}
