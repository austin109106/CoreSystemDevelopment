#include "Resource.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

// Resource class
Resource::Resource() : id(""), resourceNumber(0), name(""), type(""), available(true){}

Resource::Resource(const string& id, const string& name, const string& type, bool available)
    : id(id), name(name), type(type), available(available) {
        if (!id.empty() && (id[0] == 'R' || id [0] == 'r')){
            try{
                resourceNumber = stoi(id.substr(1));
            } catch(...){
                resourceNumber = 0;
            }
        } else {
            try {
                resourceNumber = stoi(id);
            } catch(...){
                resourceNumber = 0;
            }
        }
    }

string Resource::getId() const { return id; }
int Resource::getResourceNumber() const { return resourceNumber; }
string Resource::getName() const { return name; }
string Resource::getType() const { return type; }
bool Resource::isAvailable() const { return available; }

void Resource::setAvailable(bool status) { available = status; }
void Resource::setName(const string& n) { name = n; }
void Resource::setType(const string& t) { type = t; }
void Resource::display() const{
    cout << id << "\t|" << name << "\t|" << type << "\t|" << (available ? "Available" : "Unavailable") << "\n"; 
}
// Resource Manager class
ResourceManager::ResourceManager(){}
    void ResourceManager::addResource(const Resource& res){
        resources.push_back(res);
    }

bool ResourceManager::loadFromFile(const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Error: Could not open resource file: " << filename << endl;
        return false;
    }
    resources.clear();
    string line;
    while(getline(file, line)){
        if(line.empty()) continue;
        stringstream ss(line);
        string id, name, type, statusStr;
        if(getline(ss, id, '|') && getline(ss, name, '|') && getline(ss, type, '|') && getline(ss, statusStr)){
        if(!statusStr.empty()&& statusStr.back() == '\r'){
            statusStr.pop_back();
        }
        bool isAvail = (statusStr == "Available" || statusStr == "1");
        resources.emplace_back(id, name, type, isAvail);
    }
}
file.close();
return true;
}

Resource* ResourceManager::findById(const string& id){
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].getId() == id){
            return &resources[i];
        }
    }
    return nullptr;
}

Resource* ResourceManager::findByNumber(int resourceNum){
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].getResourceNumber() == resourceNum){
            return &resources[i];
        }
    }
    return nullptr;
}
bool ResourceManager::updateAvailability(int resourceNum, bool status){
    Resource* res = findByNumber(resourceNum);
    if(res != nullptr){
        res->setAvailable(status);
        return true;
    }
    return false;
}
void ResourceManager::displayAllResources() const {
    cout << endl << "ID\t| Name\t | Type \t | Status " << endl << endl;
    if(resources.empty()){
        cout << "No resources." << endl;
    } else{
        for(size_t i = 0; i < resources.size(); ++i){
            resources[i].display();
        }
    }
    cout << "\n\n";
}
void ResourceManager::displayAvailableResources() const{
    cout << endl << "ID\t | Name\t | Type\t | Status\t " << endl;
    cout << "\n\n";
    bool found = false;
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].isAvailable()){
            resources[i].display();
            found = true;
        }
    }
    if(!found){
        cout << "No resources." << endl;
    }
    cout << endl<< endl;
}


int ResourceManager::getAvailableResources() {
    bool found = false;
    int count = 0;
    for(size_t i = 0; i < resources.size(); ++i){
        if(resources[i].isAvailable()){
            found = true;
            count++;
        }
    }
    if(!found){
        return 0;
    } else return count;
}

size_t ResourceManager::getResourceCount() const{
    return resources.size();
}
const vector<Resource>& ResourceManager::getAllResources() const{
    return resources;
}
