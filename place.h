#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iomanip>
#include <iostream>

class Address;
class PointOfInterest;

class Place {
private:

    int id;
    const double latitude;
    const double longitude;
    std::string name;
    int nearestNeighborID;
    static std::vector<Place*>* allPlaces;
    Place* firstSelectedPlace;
    Place* secondSelectedPlace;
    bool isFirstSelection;
    bool active= true;


public:
    Place(std::string name, double latitude, double longitude);

    virtual bool isConnectedTo(const Place& otherPlace) const;

    virtual ~Place() = default;
    static int nextID;
    double getLatitude() const;
    double getLongitude() const;
    double CalcDistance(const Place& Place_other) const;
    virtual void getInfo() const;
    virtual std::string export_Place() const;
    static Place* import_Place(const std::string& file);
    int getId() const;
    void setId(int newId);
    std::string getName() const;
    std::vector<int> connectedPlaceIDs;


    int getNearestNeighborID() const;
    void setNearestNeighborID(int id);
    void addConnection(int placeID);
    bool isConnectedTo(int placeID) const;
    const std::vector<int>& getConnections() const;
    void clearConnections();

    static void setAllPlaces(std::vector<Place*>* places);
    static Place* findPlaceById(int id);


    bool isActive() const;
    void setActive(bool active);
    void removeConnection(Place* place);

};





#endif // PLACE_H
