#include "address.h"
Address::Address(std::string name, const double latitude, const double longitude, const std::string &street,
                 const std::string &houseNumber, const std::string &postalCode,
                 const std::string &municipality)
    : Place(name, latitude, longitude), street(street), houseNumber(houseNumber),
    postalCode(postalCode), municipality(municipality) {}
void Address::getInfo() const {
    std::cout
        << std::setw(3) << getId()<< " | "
        << std::setw(5) << "Adr" << " | "
        << std::setw(15) << getName() << " | "
        << std::setw(12) << getLatitude() << " | "
        << std::setw(12) << getLongitude() << " | "
        << street << " " << houseNumber << ", " << postalCode << " " << municipality
        << "Nearest Neighbor ID: " << this->getNearestNeighborID()
        << std::endl;
    if (!connectedPlaceIDs.empty()) {
        std::cout << "\nConnected to the following places:\n";
        std::cout << std::setw(5) << "ID" << " | "
                  << std::setw(12) << "Distance (km)" << std::endl;
        std::cout << std::string(30, '-') << std::endl;  // Separator line

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
std::string Address::export_Place() const
{
    return std::to_string(this->getId())+ ";" + this->street + ";" + this->houseNumber + ";" + this->postalCode + ";" + this->municipality+ "\n";
}
Address *Address::import_Place(const std::string &file)
{
    try {
        size_t first = file.find(';');
        size_t second = file.find(';', first + 1);
        size_t third = file.find(';', second + 1);
        size_t fourth = file.find(';', third + 1);
        size_t fifth = file.find(';', fourth + 1);
        if (first == std::string::npos || second == std::string::npos ||
            third == std::string::npos || fourth == std::string::npos ||
            fifth == std::string::npos) {
            std::cerr << "Invalid format for Address" << std::endl;
            return nullptr;
        }
        std::string latStr = file.substr(0, first);
        std::string lonStr = file.substr(first + 1, second - first - 1);
        // Trim whitespace
        latStr.erase(0, latStr.find_first_not_of(" \t\r\n"));
        latStr.erase(latStr.find_last_not_of(" \t\r\n") + 1);
        lonStr.erase(0, lonStr.find_first_not_of(" \t\r\n"));
        lonStr.erase(lonStr.find_last_not_of(" \t\r\n") + 1);
        double latitude = std::stod(latStr);
        double longitude = std::stod(lonStr);
        std::string name = file.substr(second + 1, third - second - 1);
        std::string street = file.substr(third + 1, fourth - third - 1);
        std::string houseNumber = file.substr(fourth + 1, fifth - fourth - 1);
        std::string postalCode = file.substr(fifth + 1);
        // Split the remaining part into postal code and municipality
        size_t lastSemi = postalCode.find(';');
        std::string municipality;
        if (lastSemi != std::string::npos) {
            municipality = postalCode.substr(lastSemi + 1);
            postalCode = postalCode.substr(0, lastSemi);
        }
        return new Address(name, latitude, longitude, street, houseNumber,
                           postalCode, municipality);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing Address: " << e.what() << std::endl;
        return nullptr;
    }
}
