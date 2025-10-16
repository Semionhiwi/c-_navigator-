#ifndef ADDRESS_H
#define ADDRESS_H

#include "place.h"
#include <string>

class Address : public Place {
private:
    std::string street;
    std::string houseNumber;
    std::string postalCode;
    std::string municipality;

public:
    Address(std::string name, const double latitude, const double longitude, const std::string &street,
            const std::string &houseNumber, const std::string &postalCode,
            const std::string &municipality);

    void getInfo() const override;
    std::string export_Place() const override;
    static Address* import_Place(const std::string& file);
};


#endif // ADDRESS_H
