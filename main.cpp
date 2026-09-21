#include "Resource.h"
#include "Reservations.h"
#include "ReservationsList.h"
#include "WaitingList.h"

#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;


void printMostPopular(const ReservationsList& reservations, const ResourceManager& manager) { // gets the most popular resource use
    const vector<Resource>& all = manager.getAllResources();

    int bestIndex = -1;
    int bestCount = 0;

    for (size_t i = 0; i < all.size(); ++i) {
        int c = reservations.countForResource(all[i].getResourceNumber());
        if (c > bestCount) {
            bestCount = c;
            bestIndex = i;
        }
    }

    if (bestIndex == -1) {
        cout << "No reservations yet." << endl;
    } else {
        cout << "Most popular: " << all[bestIndex].getName()
             << " (" << all[bestIndex].getId() << ") with "
             << bestCount << " reservations" << endl;
    }
}

int main() {
  
  ResourceManager rm;
  ReservationsList rl;
  WaitingList wl;
  stack<Reservations> cancelHis;

  rl.loadFromFile("reservations.txt");
  rm.loadFromFile("resources.txt");
  

  
  int choice=0;
  int nextResNumber=321; //for counting incoming reservations

  while (choice!=9) {
    //Main User-Interface
    cout<<"===== Campus Resource Reservation System =====\n\n1. View Resources\n2. Create Reservation\n3. Cancel Reservation\n4. View Waiting Lists\n5. Undo Cancellation\n6. Search Reservations\n7. Sort Resources\n8. Generate Report\n9. Exit\n\nEnter Choice: ";
      cin>>choice;

    //VIEW RESOURCES
    if (choice==1) {
      rm.displayAllResources();
    }
    
    //CREATE RESERVATION
    else if (choice==2) {
      //Reservations(int rNumber, int SID, string name, int recNumber, int d, int m, int y);
      
      string resourceID;
      cout<<"\nEnter Resource ID: (include 'R')";
      cin>>resourceID;
      
      //test if resource number exists
      Resource* res = rm.findById(resourceID);
      if (res == nullptr) {
          cout<<"No resource found with Resource ID "<<resourceID<<endl;
      }
      //check to see if resource is available
      else if (!res->isAvailable()) {
          int studentID;
          string name;
          cout<<res->getName()<<" is currently unavailable. You will be added to the waitlist.\nEnter Student ID: ";
          cin>>studentID;
          cout<<"Enter Name: ";
          cin.ignore(); //for incoming getline
          getline(cin, name);
          
          wl.addtoWL(studentID, name, res->getResourceNumber());
          
          cout<<"Added to the waitlist. Type '4' at the menu to view Waiting List.\n";
          
      } else {
          int studentID;
          cout<<"Enter Student ID: ";
          cin>>studentID;
          
          string name;
          cout<<"Enter Name: ";
          cin.ignore(); //to make sure incoming getline() works consistently
          getline(cin, name);
          
          int month, day, year;
          cout<<"Enter Date for Reservation (MM DD YYYY): ";
          cin>>month>>day>>year;
          
          Reservations newRes(nextResNumber, studentID, name, res->getResourceNumber(), day, month, year);
          
          rl.add(newRes);
          rm.updateAvailability(res->getResourceNumber(), false);
          
          cout<<"\nReservation created.\n";
          nextResNumber++; //for next reservations
      }
      
    }
    
    //CANCEL RESERVATION
    else if (choice==3) {
      int reservationID;
      
      cout<<"Enter Reservation ID: ";
      cin>>reservationID;
      
      const Reservations* sRes = rl.searchbyRes(reservationID);
      
      if (sRes==nullptr) {
          cout<<"Reservation Not Found.\n";
      } else {
          int freeResNum = sRes->getResourceNumber();
          int fRNDay = sRes->getDay();
          int fRNMonth = sRes->getMonth();
          int fRNYear = sRes->getYear();
          cancelHis.push(*sRes);
          rl.cancel(reservationID);
          rm.updateAvailability(freeResNum, true);
          cout<<"Reservation has been cancelled.\n";
          
          if (!wl.isEmpty(freeResNum)) {
            //   pop them and auto create their reservation
            WaitingList::Entry e = wl.removefromWL(freeResNum);
            
            Reservations WLr = Reservations(nextResNumber, e.studentID, e.name, freeResNum, fRNDay, fRNMonth, fRNYear);
            rl.add(WLr);
            rm.updateAvailability(freeResNum, false);
            nextResNumber++;
            cout<<"Waitlisted Reservation moved up to cancelled Reservation's date.\n";
        }
          
      }
      
      
    }
    
    //VIEW WAITING LISTS
    else if (choice==4) {
        wl.displayWL();
    }
    
    //UNDO CANCELLATION
    else if (choice==5) {
      if (cancelHis.empty()) {
          cout<<"No cancellations to undo.\n";
      } else {
          Reservations restoreRes = cancelHis.top();
          cancelHis.pop();
          Resource* r = rm.findByNumber(restoreRes.getResourceNumber());
          if (r==nullptr) {
              cout<<"Doesn't exist for some reason.\n";
          } else if (r->isAvailable()) {
              rl.add(restoreRes);
              rm.updateAvailability(restoreRes.getResourceNumber(), false);
              cout<<"Reservation "<<restoreRes<<" has been added back.\n";
          } else {
              //call waiting list add to wl back of queue
              wl.addtoWL(restoreRes.getStudentID(), restoreRes.getName(), restoreRes.getResourceNumber());
              cout<<"Resource is currently unavilable now. You've been added to the waiting list.\n";
          }
      }
    }

    //SEARCH RESERVATIONS
    else if (choice==6) {
      int x;
      cout<<"How to search? (1 for by Reservation ID, 2 for by Student ID) ";
      cin>>x;
      if (x==1) {
          int s1;
          cout<<"Enter Reservation Number: ";
          cin>>s1;
          const Reservations* result = rl.searchbyRes(s1);
          if (result==nullptr) {
              cout<<"This reservation does not exist.\n";
          } else {
              cout<<"Found! Here it is:\n"<<*result<<endl;
          }
      } else if (x==2) {
          int s2;
          cout<<"Enter Student ID: ";
          cin>>s2;
          vector<Reservations> results = rl.searchbySID(s2);
          if (results.empty()) {
              cout<<"This student's reservations cannot be found.\n";
          } else {
              cout<<"Found! Here it is:\n";
              for (int i = 0; i<results.size(); i++) {
                cout<<results.at(i)<<endl;  
              }
          }
      } else {
          cout<<"Not a valid number.\n";
      }
    }

    //SORT RESOURCES
    else if (choice==7) {

    }

    //GENERATE REPORT
    else if (choice==8) {
        /*Most frequently reserved resources
        Current availability
        Number of active reservations
        Waiting list reports*/
        printMostPopular(rl, rm);
        cout << "Current availability " << rm.getAvailableResources() << endl;
        cout << "Number of active reservations: " << rl.size(); << endl;
        cout << "waiting list report" << wl.displayWL() << endl;
    }

  }

cout<<"Exited Program.\n";
  return 0;
}
