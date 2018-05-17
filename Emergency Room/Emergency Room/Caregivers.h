#ifndef Caregivers_h
#define Caregivers_h

#include <queue>
#include <iostream>
#include <string>

class Caregivers{
protected:
    int treatmentTime;
    int treatment_Start;
public:
    Caregivers(){
        treatmentTime = -1;
        treatment_Start = -1;
    }
    
    int getTreatmentTime(){
        return treatmentTime;
    }
    
    virtual void setTreatmentTime(Patient *p, int clock) = 0;
    virtual bool isNurse(Caregivers* ) = 0;
};

class Nurse : public Caregivers{

public:
    Nurse() : Caregivers() {}
    void setTreatmentTime(Patient* p, int clock){
        int time = rand() % 10 + 1;
        if (p->priority > 10)
            std::cout << "Nurse can't treat" << std::endl;
        p->treatment_time = time; //assigns treatment time to patient
        this->treatmentTime = time;
        p->treatment_start = clock;
        this->treatment_Start = clock;
    }
    
    bool isNurse(Caregivers*){
        return true;
    }
};

class Doctor : public Caregivers{

public:
    Doctor() : Caregivers() {}
    void setTreatmentTime(Patient* p, int clock){
        int time = rand() % 20 + 1;
        p->treatment_time = time; //assigns treatment time to patient
        this->treatmentTime = time;
        p->treatment_start = clock;
        this->treatment_Start = clock;
    }
    
    bool isNurse(Caregivers*){
        return false;
    }
};

#endif /* Caregivers_h */
