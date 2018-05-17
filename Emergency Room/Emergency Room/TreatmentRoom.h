#ifndef TreatmentRoom_h
#define TreatmentRoom_h

#include <queue>
#include <iostream>
#include <string>
#include <map>
#include <algorithm> // Required for set_intersection()
#include <iterator> // Required for inserter()
#include <utility>
#include "Patient.h"
#include "WaitRoom.h"
#include "Caregivers.h"
#include "Records.h"

//treats patients based on their priority level
class TreatmentRoom{
private:
    WaitRoom *wait_room; //pointer to waiting room
    Records *rec; //pointer to records
    std::map<Patient *, Caregivers *> treating; //map of the patients being treated
    std::queue<Doctor *> availableDocs;
    std::queue<Nurse *> availableNurses;
    
public:
    TreatmentRoom() {};
    
    void set_waitingQueue(WaitRoom *waitRoom){
        wait_room = waitRoom;
    }
    
//    void set_DischargeRoom(DischargeRoom *dischargeRoom) {
//        discharge_room = dischargeRoom;
//    }
    
    //sets amount of doctors and nurses
    void setCaregivers(int doc, int nurse){
        if (doc < 0 || nurse < 0)
            throw ("Error not in range");
        for (int i = 0; i < doc; i++){
            Doctor *d = new Doctor();
            availableDocs.push(d);
        }
        for (int i = 0; i < nurse; i++){
            Nurse *n = new Nurse();
            availableNurses.push(n);
        }
    }
    
    void update(int clock){
        //reviewing patient at top of list
        //need to check empty because priority queue doesn't like top() if empty
        if (!wait_room->wait.empty()){
                Patient *p = new Patient(clock);
                p = wait_room->wait.top();
                std::string patientName = p->name;
                std::queue<Patient *> doctorsOnly; //queue to hold onto high priority patients
            
            //to make sure all docs and nurses are treating
            do{
                //check if nurse is free
                if (!availableNurses.empty()){
                    //if priority of patient is below 10 treat
                    if (p->priority <= 10){
                        treating.insert(std::make_pair(p, availableNurses.front()));
                        availableNurses.front()->setTreatmentTime(wait_room->wait.top(), clock);
                        
                        //remove patient from waitlist and nurse from availQueue
                        wait_room->wait.pop();
                        availableNurses.pop();
                    }
                    if(p->priority > 10 && availableDocs.empty()){
                        //next priority patient
                        doctorsOnly.push(p); //putting on to doctors only (to save information)
                        wait_room->wait.pop(); //removing top patient to find patient nurse can treat
                    }
                }
                else if (!availableDocs.empty()) {
                    treating.insert(std::make_pair(p, availableDocs.front()));
                    availableDocs.front()->setTreatmentTime(p,clock);
                    
                    //remove patient from waitlist and doc from availQueue
                    wait_room->wait.pop();
                    availableDocs.pop();
                }
            }while (!availableNurses.empty() || !availableDocs.empty());
            
            //put docsOnly patients back in to priority queue
            // doctorsOnly.size() - 1 because it starts at zero, without -1 it doesn't like doctorsOnly.front() because no front
            for(int i = 0; i < (doctorsOnly.size()-1); i++){
                Patient* x = new Patient(clock);
                x = doctorsOnly.front();
                wait_room->wait.push(x);
                doctorsOnly.pop();
            }
        }
        //walking through treating to check if they are done
        for (auto it = treating.begin(); it != treating.end(); it++){
            
            //see if treatment is done and move patient to records
            if (clock - it->first->arrival_time < it->first->treatment_time){
                rec->records.insert(make_pair(it->first->name,it->first));
                
                //checking what the caregiver is and putting them back into available queue
                if(it->second->isNurse(it->second) == true){
                    availableNurses.push((Nurse*)it->second);
                }
                else{
                    availableDocs.push((Doctor*)it->second);
                }
                //update total wait time and total number treated
                wait_room->totalwait+= (clock - it->first->arrival_time);
                wait_room->numTreated++;
                treating.erase(it->first);
            }
        }
    }
    
    friend class WaitRoom;
    friend class Records;
    
};



#endif /* TreatmentRoom_h */
