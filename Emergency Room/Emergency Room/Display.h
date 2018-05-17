//
//  Display.h
//  Emergency Room
//
//  Created by Janell Martin on 5/16/18.
//  Copyright © 2018 Janell Martin. All rights reserved.
//

#ifndef Display_h
#define Display_h

using namespace std;
class Display{
private:
    WaitRoom *wr;
    Records *r;
public:
    Display(){
        //Average visit time (Total time)/(total visits)
        double avgVisitTime = (wr->totalwait)/(wr->numTreated);
        cout << "Average visit time: " << avgVisitTime << endl;
        
        string name;
        do {
            std::cout << "What person do you want to see? If none type 'exit' \n";
            cin >> name; //'exit' to exit'
            //Display patient's number of visits
            cout << "Total number of visits for " << name << ": " << r->records[name]->numVisits << endl;
            //severity of each visit
            cout << name << "'s severity for each visit: /n";
            for (int i = 0; i < r->records[name]->pastPriority.size(); i++) {
                cout << i << "/t";
                cout << r->records[name]->pastPriority[i] << endl;
            }
        } while(name != "exit");
    }

    friend class Records;
    friend class WaitRoom;
};


#endif /* Display_h */
