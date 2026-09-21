#include "Resource.h"
#include "Reservations.h"
#include "ReservationsList.h"
// #include WaitingList.h"

#include <stack>
#include <queue>
#include <cstdlib>

using namespace std;



int main() {
  
  ResourceManager rm;
  ReservationsList rl;
  rl.loadFromFile("reservations.txt");
  rm.loadFromFile("resources.txt");
  

  
  int choice=0;
  int nextResNumber=321; //for counting incoming reservations
  stack<Reservations> cancelHis;
//   queue<

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
          cout<<res->getName()<<" is currently unavailable.\n";
          
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
          cancelHis.push(*sRes);
          rl.cancel(reservationID);
          rm.updateAvailability(freeResNum, true);
          cout<<"Reservation has been cancelled.\n";
        /*   if (!WaitingList::isEmpty(freeResNum)) {
            //pop them and auto create their reservation
        }*/
          
      }
      
      
    }
    
    //VIEW WAITING LISTS
    else if (choice==4) {
        
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

    }

  }

cout<<"Exited Program.\n";
  return 0;
}
