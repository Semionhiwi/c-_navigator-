#include "PointOfInterest.h"
PointOfInterest::PointOfInterest(std::string name, const double latitude, const double longitude, Category category,
                                 const std::string &comment)
    : Place(name, latitude, longitude), category(category), comment(comment) {}
std::string PointOfInterest::getCategoryAsString() const {
    switch (category) {
    case Category::Tankstelle: return "Tankstelle";
    case Category::Restaurant: return "Restaurant";
    case Category::Sehenswürdigkeit: return "Sehenswürdigkeit";
    case Category::Bildungseinrichtung: return "Bildungseinrichtung";
    case Category::Bundesgartenschau: return "Bundesgartenschau";
    case Category::Insel: return "Insel";
    case Category::JuriGargarin: return "Juri Gargarin";
    default: return "Unbekannt";
    }
}
std::string PointOfInterest::export_Place() const
{
    std::cout<<"HELLO EXPORT POI";
    return std::to_string(this->getId())+ ";"+ this->getName() + ';'+ std::to_string(this->getLatitude()) + ";" + std::to_string(this->getLongitude()) + ";" + this->getCategoryAsString() + ";" + this->comment+"\n";
}
PointOfInterest *PointOfInterest::import_Place(const std::string &file)
{
    try {
        size_t first = file.find(';');
        size_t second = file.find(';', first + 1);
        size_t third = file.find(';', second + 1);
        size_t fourth = file.find(';', third + 1);
        if (first == std::string::npos || second == std::string::npos ||
            third == std::string::npos || fourth == std::string::npos) {
            std::cerr << "Invalid POI format" << std::endl;
            return nullptr;
        }
        std::string name = file.substr(0, first);
        std::string latStr = file.substr(first + 1, second - first - 1);
        std::string lonStr = file.substr(second + 1, third - second - 1);
        std::string category = file.substr(third + 1, fourth - third - 1);
        std::string comment = file.substr(fourth + 1);
        latStr.erase(0, latStr.find_first_not_of(" \t\r\n"));
        latStr.erase(latStr.find_last_not_of(" \t\r\n") + 1);
        lonStr.erase(0, lonStr.find_first_not_of(" \t\r\n"));
        lonStr.erase(lonStr.find_last_not_of(" \t\r\n") + 1);
        double latitude = std::stod(latStr);
        double longitude = std::stod(lonStr);
        return new PointOfInterest(name, latitude, longitude,
                                   setCategory_fromString(category), comment);
    }
    catch (const std::exception& e) {
        std::cerr << "Error parsing PointOfInterest: " << e.what() << std::endl;
        return nullptr;
    }
}
Category PointOfInterest::setCategory_fromString(std::string category)
{
    if (category == "Tankstelle") {
        return Category::Tankstelle;
    } else if (category == "Restaurant") {
        return Category::Restaurant;
    } else if (category == "Sehenswürdigkeit") {
        return Category::Sehenswürdigkeit;
    } else if (category == "Bildungseinrichtung"){
        return Category::Bildungseinrichtung;
    }else if (category == "Bundesgartenschau"){
        return Category::Bundesgartenschau;
    }else if (category == "Insel"){
        return Category::Insel;
    }else if (category == "Juri Gargarin"){
        return Category::JuriGargarin;
    }
}
void PointOfInterest::getInfo() const {
    std::cout
        << std::setw(3) << getId()<< " | "
        << std::setw(5) << "PoI" << " | "
        << std::setw(15) << getName() << " | "
        << std::setw(12) << getLatitude() << " | "
        << std::setw(12) << getLongitude() << " | "
        << comment << ", " << getCategoryAsString()
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
