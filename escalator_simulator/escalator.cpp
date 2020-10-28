//
//  escalator.cpp
//  escalator_simulator
//
//  Created by Yunus Syed on 10/26/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include "escalator.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

void Escalator::ReadInputs(std::ifstream &escalator_info) {
    while(!escalator_info.eof()) {      // Fill up the list of people
        std::string name;
        int time;
        escalator_info >> name >> time;
        Person new_person(name, time);
        people.push_back(new_person);
    }
    
    for (int i = 0; i < people.size(); i++) {   // Enter list of ENTER events
        Event new_event(ENTER, people[i].GetPersonName(), people[i].GetPersonEntryTime());
        events.push(new_event);
    }
}

void Escalator::RunEscalator(std::ifstream &escalator_info) {
    ReadInputs(escalator_info);
    
    while(events.size() > 0) {
        Event next_event = events.top();
        switch (next_event.GetEventType()) {
            case ENTER:
                Enter(next_event.GetEventName(), next_event.GetEventTime());
                break;
            case EXIT:
                Exit(next_event.GetEventName(), next_event.GetEventTime());
                break;
            default:
                break;
        }
        events.pop();
    }
    
    std::cout << "No more passengers." << std::endl;
    DisplayMax();
    return;
}

void Escalator::Enter(std::string name, int time) {
    Person next_passenger(name, time);
    current_passengers.push(next_passenger);
    max_passengers = max_passengers > current_passengers.size() ? max_passengers : current_passengers.size();
    
    Event new_event(EXIT, name, time + 3);
    events.push(new_event);
}

void Escalator::Exit(std::string name, int time) {
    current_passengers.pop();
    std::cout << name << " left escalator at " << time << "." << std::endl;
}

void Escalator::DisplayMax() {
    std::cout << "The maximum number of passengers is " << max_passengers << "." << std::endl;
}
