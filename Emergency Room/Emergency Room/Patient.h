#ifndef Patient_h
#define Patient_h

#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>

/** A patient has attributes to keep track of
 1. When they arrived
 2. Their priority level
 3. When their treatment is finished
 */

struct Patient
{
    std::string name;
    int priority;
    int arrival_time;
    int treatment_start;
    int treatment_time;
    int discharge_time;
    int numVisits;
    //std::vector<int> pastPriority;
    Patient(int clock){
        this->name = "Janell";
        priority = prioritySet();
        arrival_time = clock;
        treatment_time = -1;
        discharge_time = -1;
        treatment_start = -1;
        numVisits = 1;
       //pastPriority[0] = this->priority;
    }
    
    //setting priority to 1-10 70%, 11-15 20%, and 16-20 10% of the time
    int prioritySet(){
        double rate = rand() / RAND_MAX;
        if (rate < .7)
             return ((rand() % 10) + 1);
        if(.7 < rate < .9)
            return ((rand() % 5) + 11);
        else
            return ((rand() % 5) + 16);
    }
    
    bool operator <=(const Patient& p) {
        if (p.priority <= this->priority)
            return true;
        else
            return false;
    }
};

#endif /* Patient_h */
