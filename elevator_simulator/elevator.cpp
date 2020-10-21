//
//  elevator.cpp
//  elevator_simulator
//
//  Created by Yunus Syed on 10/10/20.
//  Copyright © 2020 Yunus Syed. All rights reserved.
//

#include "elevator.hpp"
#include <algorithm>
#include <fstream>


int Elevator::GetNextPerson() {
    if (all_people.size() > 0) {
        Person next_person = all_people.top();
        all_people.pop();
        current_passengers.push_back(next_person);
        OrganizeCurrentPassengers();
        RemovePeople(next_person.time_entered);
        return 1; //still more people to pick up
    }
    else if (current_passengers.size() > 0) {
        while (current_passengers.size() > 0)
            RemovePeople(current_passengers[0].time_left);
        return 0; //no more people to pick up and current passengers are getting off
    }
    
    return -1; //elevator empty
}

void Elevator::RemovePeople(std::string time) {
    
    std::cout << current_passengers[0].name << std::endl;
    
    while(current_passengers[0].time_left <= time)
        current_passengers.erase(current_passengers.begin());
}

void Elevator::DisplayCurrentFloor() {
    std::cout << current_floor << std::endl;
}

void Elevator::DisplayCurrentTime() {
    std::cout << current_time << std::endl;
}

void Elevator::DisplayPassengersAtTime(std::string time) {
    
}

void Elevator::DisplayFloorsPressed() {
    for (int i = 0; i < floors_pressed.size(); i++)
        std::cout << floors_pressed[i].floor_pressed << " " << floors_pressed[i].going_up << std::endl;
}

void Elevator::AddPerson(Person new_person) {
    all_people.push(new_person);
}


void Elevator::OrganizeCurrentPassengers() {
    for (int i = 0; i < current_passengers.size(); i++) {
        for (int j = 0; j < current_passengers.size() - 1; j++) {
            if (current_passengers[j].time_left < current_passengers[j+1].time_left) {
                Person temp = current_passengers[j];
                current_passengers[j] = current_passengers[j+1];
                current_passengers[j+1] = current_passengers[j];
            }
        }
    }
}

void Elevator::RunElevator(std::ifstream &elevator_info) {
    while (!elevator_info.eof()) {
        Person new_person;
        elevator_info >> new_person.name >> new_person.time_start_wait >> new_person.floor_entered >> new_person.floor_left;
        new_person.going_up = (new_person.floor_entered < new_person.floor_left) ? true : false;
        AddPerson(new_person);
    }
    while (GetNextPerson() != -1)
        ;

}

std::string AddTime(std::string time, int seconds) {
    int seconds_ones = seconds % 10;
    if (time[8] - '0' + seconds_ones >= 10)
        time[7] += 1;
    
    time[8] = (time[8] - '0' + seconds_ones) % 10 + '0';
    seconds_tens = seconds - seconds_ones;
    seconds_tens += time[7] - '0';
    
    int minutes_ones = seconds_tens / 6;
    seconds_tens = seconds_tens % 6;
    time[7] = seconds_tens + '0';
    
    if (time[5] - '0' + minutes_ones >= 10)
        time[4] += 1;
    
    time[5] = (time[5] - '0' + minutes_ones) % 10 + '0';
    int hours_ones = time[4] / 6;
    time[4] = time[4] % 6;
    
    // For simplicity, we assume the elevator does not accept passengers some amount of time prior to 24:00:00.
    
    if (time[2] - '0' + hours_ones >= 10)
        time[1] += 1;
    
    time[2] = (time[2] - '0' + hours_ones) % 10 + '0';
    
}

int SubtractTime(std::string start_time, std::string end_time) {
    int start_time_seconds = start_time[8] + 10 * start_time[7] + 60 * start_time[5] + 600 * start_time[4] + 3600 * start_time[2] + 36000 * start_time[1];
    int end_time_seconds = end_time[8] + 10 * end_time[7] + 60 * end_time[5] + 600 * end_time[4] + 3600 * end_time[2] + 36000 * end_time[1];
    return end_time_seconds - start_time_seconds;
}

void ChangeDirection() {
    going_up = (going_up == true) ? false : true;
}

int ComputeTravelTime(int start_floor, int end_floor) {
    int x = (start_floor =< end_floor) ? (end_floor - start_floor) : (start_floor - end_floor);
    return 7 * x;
}


bool operator<(const Person &first_person, const Person &second_person) {
    return first_person.time_start_wait > second_person.time_start_wait;
}

bool operator<(const Event &first_event, const Event &second_event) {
    return first_event.time > second_event.time;
}
