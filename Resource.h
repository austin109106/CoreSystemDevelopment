#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <vector>
using namespace std;

class Resource{
    private:
        string id;
        int resourceNumber;
        string name;
        string type;
        bool available;
    public:
        Resource();
        Resource(const string& id, const string& name, const string& type, bool available = true);

        string getId() const;
        int getResourceNumber() const;
        string getName() const;
        string getType() const;
        bool isAvailable() const;

        void setAvailable(bool status);
        void setName(const string& name);
        void setType(const string& type);
        void display() const;
};
// added second class "Resource Manager" to implement a vector to stor the resources
class ResourceManager {
    private:
    // vector to store resource information
        vector<Resource> resources;
    public:
        ResourceManager();

        // needed for resource.txt
        bool loadFromFile(const string& filename);
        // add resources and matching them
        void addResource(const Resource& res);
        Resource* findById(const string& id);
        Resource* findByNumber(int resourceNum);
        // check if available
        bool updateAvailability(int resourceNum, bool status);
        // display methods
        void displayAllResources() const;
        int getAvailableResources();
        void displayAvailableResources() const;

        size_t getResourceCount() const;
        const vector<Resource>& getAllResources() const;
};
#endif
