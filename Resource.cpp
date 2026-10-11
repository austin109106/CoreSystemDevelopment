#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Resource class
// default constructor for the Resource, sets its defaults to empty, 0, and true.
Resource::Resource() : id(""), resourceNumber(0), name(""), type(""), available(true){} 
// fully paremeterized constructor for the resource class
Resource::Resource(const string& id, const string& name, const string& type, bool available) 
    : id(id), name(name), type(type), available(available) {
        // quick check to see if the id isnt empty, and it also has to start with R
        if (!id.empty() && (id[0] == 'R' || id [0] == 'r')){
            // used a try catch in case of potential error like an invalid numebr
            try{
                resourceNumber = stoi(id.substr(1)); // this line grabs the number after R and stoi changes the string to integer
            } catch(...){
                resourceNumber = 0; // if it fails it falls back 
            }
        } else {
            try {
                resourceNumber = stoi(id); // parses directly if it doesnt start with r
            } catch(...){
                resourceNumber = 0; // falls back to 0 if it cant
            }
        }
    }
// all getters for the resource class
string Resource::getId() const { return id; }
int Resource::getResourceNumber() const { return resourceNumber; }
string Resource::getName() const { return name; }
string Resource::getType() const { return type; }
bool Resource::isAvailable() const { return available; }
// all setters for the resource class
void Resource::setAvailable(bool status) { available = status; }
void Resource::setName(const string& n) { name = n; }
void Resource::setType(const string& t) { type = t; }
// diplay function for the resource class with it availibity
void Resource::display() const{
    cout << id << "\t|" << name << "\t|" << type << "\t|" << (available ? "Available" : "Unavailable") << "\n"; 
}
// RESOURCE MANAGER CLASS
// default constructor for resource manager
ResourceManager::ResourceManager(){}
// function to add a resource object into the resources vector
    void ResourceManager::addResource(const Resource& res){
        resources.push_back(res);
    }
// function to load the resources from txt file
bool ResourceManager::loadFromFile(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){ // quick check to open file, if not then error pops up
        cerr << "Error: Could not open resource file: " << filename << endl;
        return false;
    }
    resources.clear(); // clear data before loading file
    string line;
    while(getline(file, line)){  // while loop to grab every line from the file until the end
        if(line.empty()) continue; // if the line is empty then it'll skip it
        stringstream ss(line); // allows the line to be an input 
        string id, name, type, statusStr; // string type to eventually display
        if(getline(ss, id, '|') && getline(ss, name, '|') && getline(ss, type, '|') && getline(ss, statusStr)){ // extracts from the txt file
        if(!statusStr.empty()&& statusStr.back() == '\r'){ // if the \r is hideen in the file then this loop just removes it
            statusStr.pop_back();
        }
        bool isAvail = (statusStr == "Available" || statusStr == "1"); // if the resource is available this loop will make the isAvail  true, if not its false
        resources.emplace_back(id, name, type, isAvail); // creates a resource object with the text and adds it to the resource vector
    }
}
file.close(); // close file
return true; // the load works
}
// function to find the resource by the string id
Resource* ResourceManager::findById(const string& id){
    for(size_t i = 0; i < resources.size(); ++i){ // search through the vector
        if(resources[i].getId() == id){
            return &resources[i]; // returns the pointer to the resource
        }
    }
    return nullptr; // in case its not found
}
// function to search for the resource using the resource number
Resource* ResourceManager::findByNumber(int resourceNum){
    for(size_t i = 0; i < resources.size(); ++i){ // search whole vector
        if(resources[i].getResourceNumber() == resourceNum){
            return &resources[i]; // returns the resource found
        }
    }
    return nullptr; // in case its not foudn
}
// function to update the availability of the resource, we need the resource number
bool ResourceManager::updateAvailability(int resourceNum, bool status){
    Resource* res = findByNumber(resourceNum); // uses the find number function
    if(res != nullptr){
        res->setAvailable(status); // uses the setAvailable function
        return true;
    }
    return false; // if resource not founmd
}
// function to display all resources
void ResourceManager::displayAllResources() const {
    cout << endl << "ID\t| Name\t | Type \t | Status " << endl << endl;
    if(resources.empty()){ // if there are no resources displays "no resources"
        cout << "No resources." << endl;
    } else{ // if not, we display all of the resources stored in the resource vector using the display function.
        for(size_t i = 0; i < resources.size(); ++i){
            resources[i].display();
        }
    }
    cout << "\n\n";
}
// function to display only available resources
void ResourceManager::displayAvailableResources() const{
    cout << endl << "ID\t | Name\t | Type\t | Status\t ";
    cout << "\n\n";
    bool found = false;
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].isAvailable()){ // we use the isAvailble function for the availabilty check and the display function
            resources[i].display();
            found = true;
        }
    }
    if(!found){ // if none display no resources
        cout << "No resources." << endl;
    }
    cout << endl<< endl;
}
// only returns the count of the available resources
int ResourceManager::getAvailableResources() {
    bool found = false;
    int count = 0;
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].isAvailable()){ // using the available function, and adding to the count if its true
            found = true;
            count++;
        }
    }
    if(!found){
        return 0;
    } else return count; // returns the count
}
// function to get the resource count in the manager
size_t ResourceManager::getResourceCount() const{
    return resources.size();
}
// function to return the resources in the original resource vector
const vector<Resource>& ResourceManager::getAllResources() const{
    return resources;
}
