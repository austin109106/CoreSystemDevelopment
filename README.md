# CoreSystemDevelopment
Milestone 1

Required Features
Resource Management
The system shall:

Load resource information from a file.
Store resource information.
Display all resources.
Display resource availability.

Reservation Management
The system shall:

Create reservations.
Cancel reservations.
Display active reservations.
Validate reservation requests.

Linked List Implementation
A linked list must be used to store active reservations.

The implementation must support:

Insert reservation
Remove reservation
Traverse reservation records
Display reservation information

Waiting List Management
A queue must be used for waiting lists.

The implementation must support:

Add student to waiting list
Remove student from waiting list
Display waiting list

Cancellation History
A stack must be used for cancellation tracking.

The implementation must support:

Store cancelled reservations
Restore the most recently cancelled reservation
Display cancellation history

 Complexity Analysis
Provide a short report discussing:

Reservation insertion complexity
Reservation removal complexity
Waiting-list processing complexity
Undo cancellation complexity
Include Big-O notation and brief explanations.



reservations class
 "rez number | student number | name | resource id | date"
resouces class
 "request number | item number | item | availability"

austin -
 reservations class
    constructor
    get request number
    get name
    get rez number
    get student number
    get date 
    set request number
    set name
    set rez number
    set student number
    set date  
    operator overload on <> and =


Eddie - 
 Resource h holds the declarations
 holds string id, resource number, name, type,, and availability status.
 has the declarations for the constructors, getters, setters, and the display method
 ResourceManager class stores the objects inside the resource vector. also has the file loading, availibility, and display.
 Resource cpp holds the functions logic 
 the constructors will use the inputs and create new resource objects and also handle misinputs with the try catch method
 implemented loadFromFile to read the file line by line in order to display the text from the file
 The search method uses the string ID or the resource number to update availability, generate a report, or all available resources.
 
 
Payton -
 main.cpp partition, comes before, and quick sort functions, also implemented menu interface and choices view resources, create reservation, cancel reservation, view waitlist, undo cancellation, search reservations, and sort resources
 Waitlist.h/.cpp created and implemented displayWL, addtoWL, removefromWL, isEmpty, and the multikeyed map with a queue for the Waitlist
 

