//
//  elevator.hpp
//  elevator_simulator
//
//  Created by Yunus Syed on 10/10/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#ifndef elevator_hpp
#define elevator_hpp

#include <stdio.h>
#include <iostream>
#include <queue>
#include <fstream>

struct Person {
    std::string name;
    std::string time_start_wait;
    int floor_entered;
    int floor_left;
    bool going_up; // false = person going down, true = person going up
    
    friend bool operator<(Person &first_person, Person &second_person);
};

struct Event {
    int type; // 1 = call elevator, 2 = enter elevator, 3 = exit elevator
    Person person;
    int floor;
    std::string time;
    
    friend bool operator<(Event &first_event, Event &second_event);
}

struct FloorPress {
    int floor_pressed;
    bool going_up; // false = person going down, true = person going up
}

class Elevator {
    int current_floor;
    std::string current_time;
    std::vector<FloorPress> floors_pressed;
    std::priority_queue<Person> all_people;
    std::vector<Person> current_passengers;
    std::priority_queue<Event> elevator_actions;
    bool going_up; // false = elevator going down, true = elevator going up
    
public:
    Elevator() : current_floor(1), going_up(true) {}
    int GetNextPerson();
    void RemovePeople(std::string time);
    void DisplayCurrentFloor();
    void DisplayPassengersAtTime(std::string time);
    void DisplayFloorsPressed();
    void DisplayCurrentTime();
    void AddPerson(Person new_person);
    // void OrganizeAllPeople();
    void OrganizeCurrentPassengers();
    void RunElevator(std::ifstream &elevator_info);
    std::string AddTime(std::string time, int seconds);
    int SubtractTime(std::string start_time, std::string end_time);
    bool ElevatorDirection() {return going_up;}
    void ChangeDirection(bool direction);
    int ComputeTravelTime(int start_floor, int end_floor);
    void AddEvent(int type, Person person, int floor, std::string time);
    
};


#endif /* elevator_hpp */
