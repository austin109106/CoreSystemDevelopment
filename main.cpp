#include "Resource.h"
#include "Reservations.h"
#include "ReservationsList.h"

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
      
      
    }
    
    //VIEW WAITING LISTS
    else if (choice==4) {

    }
    
    //UNDO CACELLATION
    else if (choice==5) {

    }

    //SEARCH RESERVATIONS
    else if (choice==6) {

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
