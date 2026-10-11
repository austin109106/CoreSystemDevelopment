#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <vector>
using namespace std;
// Resource class declarations
class Resource{
// we need a string id for the "R***", resource number for just the number portion, the name of resource,, the type of resource, and the availability
    private:
        string id;
        int resourceNumber;
        string name;
        string type;
        bool available;
    public:
        // default constructor, and fully parameterized constructor
        Resource();
        Resource(const string& id, const string& name, const string& type, bool available = true);
        // getter declarations to get our private members
        string getId() const;
        int getResourceNumber() const;
        string getName() const;
        string getType() const;
        bool isAvailable() const;
        // setters
        void setAvailable(bool status);
        void setName(const string& name);
        void setType(const string& type);
        // the display method declaration
        void display() const;
};
// added second class "Resource Manager" to implement a vector to stor the resources
class ResourceManager {
    private:
    // vector to store resource information
        vector<Resource> resources;
    public:
        // default constructor
        ResourceManager();

        // needed to load the resource txt file
        bool loadFromFile(const string& filename);
        // add resources function declaration
        void addResource(const Resource& res);
        // declarations for the search methods
        Resource* findById(const string& id);
        Resource* findByNumber(int resourceNum);
        // check if available
        bool updateAvailability(int resourceNum, bool status);
        // display methods
        void displayAllResources() const;
        int getAvailableResources();
        void displayAvailableResources() const; // display the available resources
        
        size_t getResourceCount() const;  // how many total items in the manager list
        const vector<Resource>& getAllResources() const; // shows a complete list of all resources
};
#endif
