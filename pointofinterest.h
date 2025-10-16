#ifndef POINTOFINTEREST_H
#define POINTOFINTEREST_H

#include "place.h"
#include <string>


enum class Category {
    Tankstelle,
    Restaurant,
    Sehenswürdigkeit,
    Bildungseinrichtung,
    Bundesgartenschau,
    Insel,
    JuriGargarin
};

class PointOfInterest : public Place {
private:
    Category category;
    std::string comment;

public:
    PointOfInterest(std::string name,const double latitude, const double longitude, Category category,
                    const std::string &comment);

    void getInfo() const override;
    std::string getCategoryAsString() const;
    std::string export_Place() const override;
    static PointOfInterest* import_Place(const std::string &file);
    static Category setCategory_fromString(std::string category);
};
#endif // POINTOFINTEREST_H
