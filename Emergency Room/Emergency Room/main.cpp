#include "Patient.h"
#include "WaitRoom.h"
#include "TreatmentRoom.h"
#include "Caregivers.h"
#include "Records.h"
#include "Display.h"
#include "CreatePatients.h"
#include "UnitTesting.h"

using namespace std;
#include <iostream>
int main(){
    int hourlyRate, numDoc, numNurse;
    cout << "Welcome to your personalized emergency room! \n";
    cout << "How many patients arrive per hour (no more than 60): ";
    cin >> hourlyRate;
    double rate = hourlyRate/60;
    cout << "Number of doctors: ";
    cin >> numDoc;
    cout << "Number of nurses: ";
    cin >> numNurse;
    
    WaitRoom *w = new WaitRoom();
    w->setArrivalRate(rate); //creating waitroom w specified arrival rate
    
    TreatmentRoom *t = new TreatmentRoom();
    t->setCaregivers(numDoc, numNurse); //creating Nurse and Doc queues
    
    
    // run the simulation for one week which is 10,080 minutes
    for (int clock = 0; clock < 10080; ++clock)
    {
        // for each time interval ...
        w->update(clock);
        t->update(clock);
    }
    
    new Display(); //cout in constructor let's see ???
    
    return 0;
}

//bool operator <=(const Patient& p1, const Patient& p2) {
//    if (p1.priority <= p2.priority)
//        return true;
//    else
//        return false;
//}

