#ifndef WaitRoom_h
#define WaitRoom_h

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <utility>
#include "Patient.h"
#include "CreatePatients.h"

class WaitRoom
{
private:
    double arrivalRate; //the user's given arrival rate of patients per hour
    std::priority_queue<Patient* > wait;
    int numTreated;
    int totalwait;
    int patientNumber; //if it gets to the end, start at the begining -> mod2000
    //CreatePatients *patientList;
public:
    WaitRoom(){
        numTreated = 0;
        totalwait = 0;
        patientNumber = 0;
    }
    
    void setArrivalRate(double rate){
        arrivalRate = rate;
        if (rate < 0)
            throw ("Error, not in range");
    }
    
    
    // add a new patient into the waiting room based on the arrivalRate
    //check map if patient is already made
    void update(int clock){
        double Randomrate = rand() / RAND_MAX;
        if(Randomrate <= arrivalRate){
            //access previously made patients
            //change arrival time
            //Patient *p = patientList->people.find(patientNumber)->second; //getting patient object ??
            Patient *p = new Patient(clock);
            //p->arrival_time = clock; //setting its arrival time
            (patientNumber++) % 2000; //move along the line as you create new patients
            
            //put patients into priority queue based on their random priority value
            wait.push(p);
        }
    }
    
    friend class TreatmentRoom;
    friend class Display;
};

#endif /* WaitRoom_h */
