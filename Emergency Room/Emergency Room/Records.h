
#ifndef Records_h
#define Records_h

#include "Patient.h"
#include "WaitRoom.h"
#include "TreatmentRoom.h"
#include <set>
#include <algorithm> // Required for set_intersection()
#include <iterator> // Required for inserter()

class Records{
private:
    std::map<std::string, Patient*> records; // map of records
public:
    Records() {}
    
    friend class TreatmentRoom;
    friend class Display;
};


#endif /* Records_h */
