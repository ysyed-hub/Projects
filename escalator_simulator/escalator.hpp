//
//  escalator.hpp
//  escalator_simulator
//
//  Created by Yunus Syed on 10/26/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef escalator_hpp
#define escalator_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>



class Person {
    std::string name;
    int enter_time;
public:
    Person(std::string name, int time) : name(name), enter_time(time) {}
    const std::string GetPersonName() {return name;}
    const int GetPersonEntryTime() {return enter_time;}
};

enum Action {ENTER, EXIT};

class Event {
    Action type;
    std::string name;
    int time;
public:
    Event(Action type, std::string name, int time) : type(type), name(name), time(time) {}
    const Action GetEventType() {return type;}
    const std::string GetEventName() {return name;}
    const int GetEventTime() {return time;}
    bool operator< (const Event& second_event) const {
        return (this -> time > second_event.time);
    }
    
};

class Escalator {
    std::vector<Person> people;
    std::priority_queue<Event> events;
    std::queue<Person> current_passengers;
    int max_passengers;
public:
    Escalator() : max_passengers(0) {};
    void ReadInputs(std::ifstream &escalator_info);
    void RunEscalator(std::ifstream &escalator_info);
    void Enter(std::string name, int time);
    void Exit(std::string name, int time);
    void DisplayMax();
};


#endif /* escalator_hpp */
