#include "place.h"
#include "address.h"
#include "PointOfInterest.h"
std::vector<Place*>* Place::allPlaces = nullptr;
int Place::nextID = 0;
const double Earth_radius= 6371.0;
void Place::setAllPlaces(std::vector<Place*>* places) {
    allPlaces = places;
}
Place* Place::findPlaceById(int id) {
    if (allPlaces) {
        for (Place* place : *allPlaces) {
            if (place->getId() == id) {
                return place;
            }
        }
    }
    return nullptr;
}
std::string Place::getName() const
{
    return name;
}
int Place::getNearestNeighborID() const
{
 return nearestNeighborID;
}
void Place::setNearestNeighborID(int id)
{
    nearestNeighborID = id;
}
Place::Place(std::string name, double latitude, double longitude)
    : id(nextID++), name(name), latitude(latitude), longitude(longitude), nearestNeighborID(-1), active(true) {}

bool Place::isConnectedTo(const Place &otherPlace) const
{
    return std::find(connectedPlaceIDs.begin(), connectedPlaceIDs.end(),
                     otherPlace.getId()) != connectedPlaceIDs.end();
}
int Place::getId() const
{
    return id;
}
void Place::setId(int newId)
{
    id = newId;
}
double Place::getLatitude() const {
    return latitude;
}
double Place::getLongitude() const {
    return longitude;
}
double Place::CalcDistance(const Place &Place_other) const
{
    double lat1 = this->latitude * M_PI / 180.0;
    double lon1 = this->longitude * M_PI / 180.0;
    double lat2 = Place_other.latitude * M_PI / 180.0;
    double lon2 = Place_other.longitude * M_PI / 180.0;

    double delta_lat = lat2 - lat1;
    double delta_lon = lon2 - lon1;

    double a = std::pow(std::sin(delta_lat / 2), 2) +
               std::pow(std::sin(delta_lon / 2), 2) *
                   std::cos(lat1) * std::cos(lat2);

    double c = 2 * std::asin(std::sqrt(a));
    return Earth_radius * c;
}
Place *Place::import_Place(const std::string &file)
{
    int count = std::count(file.begin(), file.end(), ';');
    try {
        if (file.empty()) {
            std::cerr << "Empty line encountered" << std::endl;
            return nullptr;
        }
        if (std::isdigit(file[0])) {
            size_t first = file.find(';');
            size_t second = file.find(';', first + 1);
            size_t third = file.find(';', second + 1);

            if (first == std::string::npos || second == std::string::npos ||
                third == std::string::npos) {
                std::cerr << "Invalid city format" << std::endl;
                return nullptr;
            }
            std::string name = file.substr(first + 1, second - first - 1);
            std::string latStr = file.substr(second + 1, third - second - 1);
            std::string lonStr = file.substr(third + 1);
            latStr.erase(0, latStr.find_first_not_of(" \t\r\n"));
            latStr.erase(latStr.find_last_not_of(" \t\r\n") + 1);
            lonStr.erase(0, lonStr.find_first_not_of(" \t\r\n"));
            lonStr.erase(lonStr.find_last_not_of(" \t\r\n") + 1);
            double latitude = std::stod(latStr);
            double longitude = std::stod(lonStr);
            return new Place(name, latitude, longitude);
        }
        else if (count == 4) {
            return PointOfInterest::import_Place(file);
        }
        else {
            std::cerr << "Invalid format - semicolon count: " << count << std::endl;
            return nullptr;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing line: " << e.what() << std::endl;
        std::cerr << "Line content: " << file << std::endl;
        return nullptr;
    }
}
void Place::getInfo() const {
    std::cout << std::setw(3) << id << " | "
    << std::setw(15) << getName() << " | "
    << std::setw(12) << getLatitude() << " | "
    << std::setw(12) << getLongitude() << " | "
    << "Nearest Neighbor ID: " << nearestNeighborID
    << std::endl;
    if (!connectedPlaceIDs.empty()) {
        std::cout << "\nConnected to the following places:\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(15) << "Name" << " | "
                  << std::setw(12) << "Distance (km)" << std::endl;
        std::cout << std::string(40, '-') << std::endl;
        for (int connectedId : connectedPlaceIDs) {
            Place* connectedPlace = findPlaceById(connectedId);
            if (connectedPlace) {
                double distance = CalcDistance(*connectedPlace);
                std::cout << std::setw(5) << connectedId << " | "
                          << std::setw(15) << connectedPlace->getName() << " | "
                          << std::setw(12) << std::fixed << std::setprecision(2) << distance << std::endl;
            }
        }
    } else {
        std::cout << "\nNo connected places." << std::endl;
    }
}
std::string Place::export_Place() const {
    return std::to_string(id)+ ";"+ this->getName() + ";" + std::to_string(this->getLatitude()) + ";" + std::to_string(this->getLongitude())+"\n";
}
void Place::addConnection(int placeID) {
    if (std::find(connectedPlaceIDs.begin(), connectedPlaceIDs.end(), placeID) == connectedPlaceIDs.end()) {
        connectedPlaceIDs.push_back(placeID);
    }
}
bool Place::isConnectedTo(int placeID) const {
    return std::find(connectedPlaceIDs.begin(), connectedPlaceIDs.end(), placeID) != connectedPlaceIDs.end();
}
const std::vector<int>& Place::getConnections() const {
    return connectedPlaceIDs;
}
void Place::clearConnections() {
    connectedPlaceIDs.clear();
}
bool Place::isActive() const {
    return active;
}
// Setter for the active status
void Place::setActive(bool active) {
    active =  active;
}
void Place::removeConnection(Place* place) {
    if (!place) return;

    auto it = std::find(connectedPlaceIDs.begin(), connectedPlaceIDs.end(), place->getId());
    if (it != connectedPlaceIDs.end()) {
        connectedPlaceIDs.erase(it);
    }
}
