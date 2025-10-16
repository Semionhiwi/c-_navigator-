#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRadioButton>
#include <QMessageBox>
#include <fstream>
#include <sstream>
#include <string>
#include <QPainter>
#include <filesystem>
#include "place.h"
#include "pointofinterest.h"
#include "AddLocationDialog.h"
#include "address.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Place* Mein_Ort_start = new Place("mein Ort",49.86682,8.639912);
    Mein_Ort_start->setId(0);
    meinOrt.push_back(Mein_Ort_start);
    imageLabel = new QLabel(this);
    QPixmap pixmap(":/Hintergrund/866-8664209_leer-deutschland-karte.png");
    imageLabel->setPixmap(pixmap);
    imageLabel->setScaledContents(true);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(imageLabel);
    scrollArea->setAlignment(Qt::AlignCenter);
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->addWidget(scrollArea);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Bild als Hintergrund mit Scrollbars");
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addLocationButton = new QPushButton("Neuer Ort", this);
    QPushButton *calculateDistanceButton = new QPushButton("Entfernung", this);
    QPushButton *showInfoButton = new QPushButton("Information", this);
    QPushButton *showAllLocationsButton = new QPushButton("Alle Orte", this);
    QPushButton *myLocationButton = new QPushButton("Mein Ort", this);
    QPushButton *routingButton = new QPushButton("Routing", this);
    QPushButton *removeButtonButton = new QPushButton("Ort Entfernen",this);
    buttonLayout->addWidget(addLocationButton);
    buttonLayout->addWidget(calculateDistanceButton);
    buttonLayout->addWidget(showInfoButton);
    buttonLayout->addWidget(showAllLocationsButton);
    buttonLayout->addWidget(myLocationButton);
    buttonLayout->addWidget(routingButton);
    buttonLayout->addWidget(removeButtonButton);
    layout->addLayout(buttonLayout);
    connect(addLocationButton, &QPushButton::clicked, this, &MainWindow::onaddLocationclicked);
    connect(showAllLocationsButton, &QPushButton::clicked, this, &MainWindow::onshowAllLocationsclicked);
    connect(calculateDistanceButton, &QPushButton::clicked, this, &MainWindow::onCalculateDistanceClicked);
    connect(showInfoButton, &QPushButton::clicked, this, &MainWindow::onInformationclicked);
    connect(myLocationButton, &QPushButton::clicked, this, &MainWindow::onMyLocationclicked);
    connect(routingButton,&QPushButton::clicked,this, &MainWindow::onRoutingclicked);
    connect(removeButtonButton,&QPushButton::clicked,this, &MainWindow::onRemovePlaceClicked);
    QMenu *PlaceMenu = menuBar()->addMenu(tr("&Weiteres"));
    PlaceMenu->addAction(tr("Orte Laden"), this, &MainWindow::loadDefaultLocations);
    PlaceMenu->addAction(tr("Mein Ort"), this, &MainWindow::changemyplace);
    connect(ui->actionladen, &QAction::triggered, this, &MainWindow::onloadfileclicked);
    connect(ui->actionspeichern , &QAction::triggered, this, &MainWindow::onsavefileclicked);
    Place::setAllPlaces(&places);
isFirstSelection = true;
    secondSelectedPlace = nullptr;
firstSelectedPlace=nullptr;
}
void MainWindow::addLocation(Place &place, const QPoint &position){
    int nearestID = -1;
    double minDistance = std::numeric_limits<double>::max();
    for (const auto &existingPlace : places) {
        if (existingPlace->getId() != place.getId()) {
            double distance = place.CalcDistance(*existingPlace);
            if (distance < minDistance) {
                minDistance = distance;
                nearestID = existingPlace->getId();
            }
        }
    }
    if (nearestID != -1) {
        for (auto &existingPlace : places) {
            if (existingPlace->getId() == nearestID) {
                existingPlace->setNearestNeighborID(place.getId());
                break;
            }
        }
    }
    place.setNearestNeighborID(nearestID);
    places.push_back(&place);
    QRadioButton *radioButton = new QRadioButton(imageLabel);
    locationRadioButtons.push_back(radioButton);
    radioButton->setText(QString::fromStdString(place.getName()));
    radioButton->move(position);
    radioButton->setVisible(true);
    connect(radioButton, &QRadioButton::toggled, this, &MainWindow::onLocationSelected);
    connect(radioButton, &QRadioButton::toggled, [place](bool checked) {
        if (checked) {
            qDebug() << QString::fromStdString(place.getName()) << " wurde ausgewählt.";
        }
    });
}
void MainWindow::loadDefaultLocations(){
    if(!places.empty()){
    for(const auto &place :places){
        delete place;
    }
    places.clear();
    }
    if(!locationRadioButtons.empty()){
    for(const auto &radiobutton :locationRadioButtons){
        delete radiobutton;
    }
    locationRadioButtons.clear();
}
        Place* berlin = new Place("Berlin", 52.5163, 13.3777);
        addLocation(*berlin, mapToImage(berlin->getLatitude(), berlin->getLongitude()).toPoint());

        Place* stuttgart = new Place("Stuttgart", 48.7833, 9.1833);
        addLocation(*stuttgart, mapToImage(stuttgart->getLatitude(), stuttgart->getLongitude()).toPoint());

        Place* muenchen = new Place("München", 48.1351, 11.5820);
        addLocation(*muenchen, mapToImage(muenchen->getLatitude(), muenchen->getLongitude()).toPoint());

        Place* potsdam = new Place("Potsdam", 52.3906, 13.0645);
        addLocation(*potsdam, mapToImage(potsdam->getLatitude(), potsdam->getLongitude()).toPoint());

        Place* bremen = new Place("Bremen", 53.0793, 8.8017);
        addLocation(*bremen, mapToImage(bremen->getLatitude(), bremen->getLongitude()).toPoint());

        Place* hamburg = new Place("Hamburg", 53.5503, 10.0007);
        addLocation(*hamburg, mapToImage(hamburg->getLatitude(), hamburg->getLongitude()).toPoint());

        Place* hannover = new Place("Hannover", 52.3759, 9.7320);
        addLocation(*hannover, mapToImage(hannover->getLatitude(), hannover->getLongitude()).toPoint());

        Place* wiesbaden = new Place("Wiesbaden", 50.0826, 8.2416);
        addLocation(*wiesbaden, mapToImage(wiesbaden->getLatitude(), wiesbaden->getLongitude()).toPoint());

        Place* schwerin = new Place("Schwerin", 53.6294, 11.4132);
        addLocation(*schwerin, mapToImage(schwerin->getLatitude(), schwerin->getLongitude()).toPoint());

        Place* magdeburg = new Place("Magdeburg", 52.1205, 11.6276);
        addLocation(*magdeburg, mapToImage(magdeburg->getLatitude(), magdeburg->getLongitude()).toPoint());

        Place* duesseldorf = new Place("Düsseldorf", 51.2277, 6.7735);
        addLocation(*duesseldorf, mapToImage(duesseldorf->getLatitude(), duesseldorf->getLongitude()).toPoint());

        Place* mainz = new Place("Mainz", 49.9929, 8.2473);
        addLocation(*mainz, mapToImage(mainz->getLatitude(), mainz->getLongitude()).toPoint());

        Place* saarbruecken = new Place("Saarbrücken", 49.2400, 6.9969);
        addLocation(*saarbruecken, mapToImage(saarbruecken->getLatitude(), saarbruecken->getLongitude()).toPoint());

        Place* dresden = new Place("Dresden", 51.0504, 13.7373);
        addLocation(*dresden, mapToImage(dresden->getLatitude(), dresden->getLongitude()).toPoint());

        Place* kiel = new Place("Kiel", 54.3233, 10.1394);
        addLocation(*kiel, mapToImage(kiel->getLatitude(), kiel->getLongitude()).toPoint());

        Place* erfurt = new Place("Erfurt", 50.9787, 11.0328);
        addLocation(*erfurt, mapToImage(erfurt->getLatitude(), erfurt->getLongitude()).toPoint());

        PointOfInterest* neuschwanstein = new PointOfInterest("Neuschwanstein", 47.5576, 10.7498, Category::Sehenswürdigkeit, "schloss");
        addLocation(*neuschwanstein, mapToImage(neuschwanstein->getLatitude(), neuschwanstein->getLongitude()).toPoint());

        PointOfInterest* bodensee = new PointOfInterest("Bodensee", 47.6500, 9.2500, Category::Sehenswürdigkeit, "See");
        addLocation(*bodensee, mapToImage(bodensee->getLatitude(), bodensee->getLongitude()).toPoint());

        PointOfInterest* saechsischeSchweiz = new PointOfInterest("Sächsische Schweiz", 50.8833, 14.2000, Category::Sehenswürdigkeit, "Nationalpark");
        addLocation(*saechsischeSchweiz, mapToImage(saechsischeSchweiz->getLatitude(), saechsischeSchweiz->getLongitude()).toPoint());

        PointOfInterest* zugspitze = new PointOfInterest("Zugspitze", 47.4210, 10.9852, Category::Sehenswürdigkeit, "Berg");
        addLocation(*zugspitze, mapToImage(zugspitze->getLatitude(), zugspitze->getLongitude()).toPoint());

        PointOfInterest* burgHohenzollern = new PointOfInterest("Burg Hohenzollern", 48.3623, 8.9747, Category::Sehenswürdigkeit, "Burg");
        addLocation(*burgHohenzollern, mapToImage(burgHohenzollern->getLatitude(), burgHohenzollern->getLongitude()).toPoint());

        Place* passau = new Place("Passau", 48.5667, 13.4319);
        addLocation(*passau, mapToImage(passau->getLatitude(), passau->getLongitude()).toPoint());

        Place* konstanz = new Place("Konstanz", 47.6582, 9.1916);
        addLocation(*konstanz, mapToImage(konstanz->getLatitude(), konstanz->getLongitude()).toPoint());

        Place* cottbus = new Place("Cottbus", 51.7563, 14.3326);
        addLocation(*cottbus, mapToImage(cottbus->getLatitude(), cottbus->getLongitude()).toPoint());

        PointOfInterest* langeAnna = new PointOfInterest("Lange Anna", 54.1810, 7.8829, Category::Sehenswürdigkeit, "Felsen");
        addLocation(*langeAnna, mapToImage(langeAnna->getLatitude(), langeAnna->getLongitude()).toPoint());

        PointOfInterest* h_da = new PointOfInterest("h_da", 49.8717, 8.6318, Category::Bildungseinrichtung, "Hochschule");
        addLocation(*h_da, mapToImage(h_da->getLatitude(), h_da->getLongitude()).toPoint());

        std::cout << "Loading default locations..." << std::endl;
        Place::setAllPlaces(&places);
        buildGraph();
        drawGraph();
}
QPointF MainWindow::mapToImage(double latitude, double longitude) const{
    double minLatitude = 47.27; // Südlichster Punkt Deutschlands
    double maxLatitude = 55.06; // Nördlichster Punkt Deutschlands
    double minLongitude = 5.87; // Westlichster Punkt Deutschlands
    double maxLongitude = 15.04; // Östlichster Punkt Deutschlands
    int imageWidth = MainWindow::imageLabel->pixmap().width();
    int imageHeight = MainWindow::imageLabel->pixmap().height();
    double x = (longitude - minLongitude) / (maxLongitude - minLongitude) * imageWidth;
    double y = (1 - (latitude - minLatitude) / (maxLatitude - minLatitude)) * imageHeight;
    return QPointF(x, y);
}
QLabel *MainWindow::getImageLabel() const{
    return imageLabel;}
void MainWindow::onaddLocationclicked(){
    addLocationDialog* dialog = new addLocationDialog(this);
    connect(dialog, &addLocationDialog::locationAdded, this, &MainWindow::onGraphRebuild);
    dialog->show();
}
void MainWindow::onshowAllLocationsclicked(){
    std::ostringstream output;
    output << std::setw(3) << "ID" << " | "
           << std::setw(5) << "Typ" << " | "
           << std::setw(15) << "Name" << " | "
           << std::setw(12) << "Latitude" << " | "
           << std::setw(12) << "Longitude" << " | "
           << "Parameters" << "\n";
    output << "-------------------------------------------------------------------------" << "\n";
    for (const auto &place : places) {
        std::streambuf *coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());
        place->getInfo();
        std::cout.rdbuf(coutBuffer);
    }
    std::cout << "Initializing graph..." << std::endl;
    buildGraph();  // Make sure this line is present
    std::cout << "Graph initialization complete." << std::endl;
    QString mapContent = QString::fromStdString(output.str());
    if (mapContent.isEmpty()) {
        mapContent = "Die Karte ist leer. Es sind keine Orte vorhanden.";
    }
    QMessageBox::information(this, "Karte anzeigen", mapContent);
}
void MainWindow::onCalculateDistanceClicked(){
    isDistanceCalculationMode = true;
    isFirstSelection = true;
    firstSelectedPlace = nullptr;
    secondSelectedPlace = nullptr;
    selectedPlaces.clear();
    QMessageBox::information(this, "Modus aktiviert",
                             "Wählen Sie den ersten Ort für die Entfernungsberechnung aus.");
}
void MainWindow::onLocationSelected(bool checked) {
    if (!checked) {
        return;
    }
    QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
    if (!radioButton) {
        return;
    }
    QString placeName = radioButton->text();
    Place* selectedPlace = nullptr;
    for (auto &place : places) {
        if (place->getName() == placeName.toStdString()) {
            selectedPlace = place;
            break;
        }
    }
    if (!selectedPlace) {
        return;
    }
    if (isRemovalMode) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Removal",
                                      QString("Are you sure you want to remove %1?")
                                          .arg(QString::fromStdString(selectedPlace->getName())),
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            radioButton->setAutoExclusive(false);
            radioButton->setChecked(false);
            radioButton->setAutoExclusive(true);
            auto placeIt = std::find(places.begin(), places.end(), selectedPlace);
            if (placeIt != places.end()) {
                places.erase(placeIt);
            }
            QList<QLabel*> markers = imageLabel->findChildren<QLabel*>();
            for (QLabel* marker : markers) {
                if (marker->property("placeId").toInt() == selectedPlace->getId()) {
                    marker->deleteLater();
                    break;
                }
            }
            auto buttonIt = std::find(locationRadioButtons.begin(),
                                      locationRadioButtons.end(),
                                      radioButton);
            if (buttonIt != locationRadioButtons.end()) {
                locationRadioButtons.erase(buttonIt);
            }
            delete selectedPlace;
            delete radioButton;
            Place::setAllPlaces(&places);
            buildGraph();
            QMessageBox::information(this, "Success", "Place removed successfully.");
        }
        isRemovalMode = false;
        return;
    }
    if (isinformation) {
        std::ostringstream output;
        std::streambuf *coutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());
        selectedPlace->getInfo();
        std::cout.rdbuf(coutBuffer);
        QString mapContent = QString::fromStdString(output.str());
        QMessageBox::information(this, "Karte anzeigen", mapContent);
        isinformation = false;
        radioButton->setAutoExclusive(false);
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);
        return;
    }
    if (isFirstSelection) {
        firstSelectedPlace = selectedPlace;
        isFirstSelection = false;
        if (isRouting) {
            QMessageBox::information(this, "Routing Modus",
                                     "Bitte wählen Sie den Zielort für die Route aus.");
        }
    } else {
        secondSelectedPlace = selectedPlace;
        if (isDistanceCalculationMode) {
            double distance = firstSelectedPlace->CalcDistance(*secondSelectedPlace);
            QMessageBox::information(this, "Entfernung",
                                     QString("Die Entfernung zwischen %1 und %2 beträgt %3 km.")
                                         .arg(QString::fromStdString(firstSelectedPlace->getName()))
                                         .arg(QString::fromStdString(secondSelectedPlace->getName()))
                                         .arg(distance));
            isDistanceCalculationMode = false;
        } else if (isRouting) {
            selectedPlaces.clear();
            selectedPlaces.push_back(firstSelectedPlace);
            selectedPlaces.push_back(secondSelectedPlace);
            findRoute(firstSelectedPlace, secondSelectedPlace);
            isRouting = false;
        }
        isFirstSelection = true;
        firstSelectedPlace = nullptr;
        secondSelectedPlace = nullptr;
    }
    radioButton->setAutoExclusive(false);
    radioButton->setChecked(false);
    radioButton->setAutoExclusive(true);
    qDebug() << "Current selections:";
    if (firstSelectedPlace) {
        qDebug() << "First place:" << QString::fromStdString(firstSelectedPlace->getName());
    }
    if (secondSelectedPlace) {
        qDebug() << "Second place:" << QString::fromStdString(secondSelectedPlace->getName());
    }
}
void MainWindow::onInformationclicked(){
    isRouting = false;
    isDistanceCalculationMode = false;
    isinformation = true;
    isFirstSelection = true;
    firstSelectedPlace = nullptr;
    secondSelectedPlace = nullptr;
    selectedPlaces.clear();
    for (auto* radioButton : locationRadioButtons) {
        radioButton->setAutoExclusive(false);
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);
    }
    QMessageBox::information(this, "Information Modus",
                             "Bitte wählen Sie einen Ort aus, um Informationen anzuzeigen.");
}
void MainWindow::onMyLocationclicked(){
    QPointF imagePoint = mapToImage(meinOrt.at(0)->getLatitude(), meinOrt.at(0)->getLongitude());
    currentMarker = new QLabel(imageLabel);
    QPixmap markerPixmap(20, 20);
    markerPixmap.fill(Qt::transparent);
    QPainter painter(&markerPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(255, 0, 0, 200));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(2, 2, 16, 16);
    painter.end();
    currentMarker->setPixmap(markerPixmap);
    currentMarker->move(imagePoint.toPoint() - QPoint(10, 10));
    currentMarker->setVisible(true);
}
void MainWindow::onloadfileclicked(){
    std::ifstream file("/Users/semionraitsev/navigationich/build/Qt_6_8_0_for_macOS-Debug/myNavigation.txt");
    int maxID1= 0;
    if (!file){
        std::cerr<<"Fehler Speichern!"<<std::endl;
        return;
    }
    for(const auto& place: places){
        delete place;
    }
    places.clear();
    for(const auto& button: locationRadioButtons){
        delete button;
    }
    locationRadioButtons.clear();
    Place::nextID=0;
    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        std::cout << "Processing line " << lineNumber << ": " << line << std::endl;
        Place* place = Place::import_Place(line);
        if (place) {
            addLocation(*place, mapToImage(place->getLatitude(), place->getLongitude()).toPoint());
        } else {
            std::cerr << "Failed to import line " << lineNumber << std::endl;
        }
    }
    file.close();
    Place::setAllPlaces(&places);
    buildGraph();
}
void MainWindow::onsavefileclicked(){
    std::cout << "Current working directory: "
              << std::filesystem::current_path() << "\n";
    std::ofstream file("/Users/semionraitsev/navigationich/build/Qt_6_8_0_for_macOS-Debug/myNavigation.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing\n";
        return;
    }
    for(const auto& place: places){
        file << place->export_Place();
    }
    places.clear();
    file.close();
}
void MainWindow::changemyplace(){
    for(const auto &me: meinOrt){
        delete me;
    }
    meinOrt.clear();
    if(currentMarker) {
        delete currentMarker;
        currentMarker = nullptr;
    }
        double latitude, longitude;
    std::cout << "Geben Sie die Koordinaten ein:\n";
    std::cout << "Breitengrad: ";
    std::cin >> latitude;
    std::cout << "Längengrad: ";
    std::cin >> longitude;
    Place* Mein_Ort = new Place("mein Ort",latitude,longitude);
    Mein_Ort->setId(0);
    meinOrt.push_back(Mein_Ort);
    QPointF imagePoint = mapToImage(meinOrt.at(0)->getLatitude(), meinOrt.at(0)->getLongitude());
    currentMarker = new QLabel(imageLabel);
    QPixmap markerPixmap(20, 20);
    markerPixmap.fill(Qt::transparent);
    QPainter painter(&markerPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(255, 0, 0, 200));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(2, 2, 16, 16);
    painter.end();
    currentMarker->setPixmap(markerPixmap);
    currentMarker->move(imagePoint.toPoint() - QPoint(10, 10));
    currentMarker->setVisible(true);
}
void MainWindow::onRoutingclicked(){
    isRouting = true;
    isinformation = false;
    isDistanceCalculationMode = false;
    isFirstSelection = true;
    firstSelectedPlace = nullptr;
    secondSelectedPlace = nullptr;
    selectedPlaces.clear();
    for (auto* radioButton : locationRadioButtons) {
        radioButton->setAutoExclusive(false);
        radioButton->setChecked(false);
        radioButton->setAutoExclusive(true);
    }
}
void MainWindow::onRemovePlaceClicked() {
    isRemovalMode = true;
    QMessageBox::information(this, "Remove Place", "Please select a place to remove.");
}
std::vector<Place *> MainWindow::getPlaces() const{
    return places;
}
MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::buildGraph() {
    for (auto* place : places) {
        place->clearConnections();
    }
    for (auto* place : places) {
        if (place->isActive()) {
            findNearestNeighbors(place, 3);
        }
    }
    for (auto* place : places) {
        if (place->isActive()) {
            std::cout << "Place " << place->getId() << " (" << place->getName()
            << ") has " << place->getConnections().size() << " connections" << std::endl;
}}}
void MainWindow::clearGraph(){
    for (auto* place : places) {
        place->clearConnections();
    }
    std::cout << "Graph cleared." << std::endl;
}
bool MainWindow::compareByDistance(const Neighbor_Node& neighbor1, const Neighbor_Node& neighbor2) {
    return neighbor1.distance < neighbor2.distance;
}
void MainWindow::findNearestNeighbors(Place* place, int numNeighbors) {
        if (!place || !place->isActive()) return;
        std::vector<Neighbor_Node> neighbors;
        for (auto* otherPlace : places) {
            if (otherPlace != place && otherPlace->isActive()) {
                double distance = place->CalcDistance(*otherPlace);
                neighbors.push_back({otherPlace, distance});
            }
        }
        std::sort(neighbors.begin(), neighbors.end(), compareByDistance);
        int connCount = 0;
        for (const auto& neighbor : neighbors) {
            if (connCount >= numNeighbors) break;
            connectPlaces(place, neighbor.place);
            connCount++;
        }
    }
void MainWindow::connectPlaces(Place* place1, Place* place2) {
    place1->addConnection(place2->getId());
    place2->addConnection(place1->getId());
}
void MainWindow::findRoute(Place* start, Place* end) {
    if (!start || !end) {
        std::cout << "Bitte suchen Sie sich Zwei Orte für die Routenfindung aus." << std::endl;
        return;
    }
    std::vector<RouteInfo_Edge> routeInfo(places.size());
    int startIndex = -1;
    int endIndex = -1;
    for (size_t i = 0; i < places.size(); ++i) {
        if (places[i] == start) startIndex = i;
        if (places[i] == end) endIndex = i;
    }
    if (startIndex == -1 || endIndex == -1) {
        std::cout << "Fehler: Kein Ort 1 und Ort 2." << std::endl;
        return;
    }
    for (auto& info : routeInfo) {
        info.distance = std::numeric_limits<double>::infinity();
    }
    routeInfo[startIndex].distance = 0;
    while (true) {
        int currentIndex = -1;
        double minDistance = std::numeric_limits<double>::infinity();
        for (size_t i = 0; i < places.size(); ++i) {
            if (!routeInfo[i].visited && routeInfo[i].distance < minDistance) {
                currentIndex = i;
                minDistance = routeInfo[i].distance;
            }
        }
        if (currentIndex == -1 || currentIndex == endIndex) {
            break;
        }
        routeInfo[currentIndex].visited = true;
        for (int connectedId : places[currentIndex]->getConnections()) {
            int neighborIndex = -1;
            for (size_t i = 0; i < places.size(); ++i) {
                if (places[i]->getId() == connectedId) {
                    neighborIndex = i;
                    break;
                }
            }
            if (neighborIndex == -1 || routeInfo[neighborIndex].visited) continue;
            double newDistance = routeInfo[currentIndex].distance +
                                 places[currentIndex]->CalcDistance(*places[neighborIndex]);
            if (newDistance < routeInfo[neighborIndex].distance) {
                routeInfo[neighborIndex].distance = newDistance;
                routeInfo[neighborIndex].previousIndex = currentIndex;
            }
        }
    }
    if (routeInfo[endIndex].distance == std::numeric_limits<double>::infinity()) {
        std::cout << "Keine Route zwischen "
                  << start->getName() << " und "
                  << end->getName() << std::endl;
        return;
    }
    std::vector<Place*> path = reconstructPath(routeInfo, startIndex, endIndex);
    if (path.empty()) {
        std::cout << "Fehler beim Aufbau der Route zwischen "
                  << start->getName() << " und "
                  << end->getName() << std::endl;
        return;
    }
    std::vector<double> distances;
        for (size_t i = 0; i < path.size() - 1; ++i) {
            if (path[i] && path[i+1]) {
                distances.push_back(path[i]->CalcDistance(*path[i + 1]));
            } else {
                std::cout << "Illegaler Ort Index " << i << std::endl;
                return;
            }
        }
    showRouteInfo(path, distances);
    drawRoute(path);
}
std::vector<Place*> MainWindow::reconstructPath( const std::vector<RouteInfo_Edge>& routeInfo, int startIndex, int endIndex){
    std::vector<Place*> path;
    if (routeInfo[endIndex].distance == std::numeric_limits<double>::infinity()) {
        std::cout << "Keine Route gefunden zwischen den ausgesuchten Orten." << std::endl;
        return path;
    }
    for (int currentIndex = endIndex; currentIndex != -1;
         currentIndex = routeInfo[currentIndex].previousIndex) {
        path.push_back(places[currentIndex]);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
void MainWindow::displayRoute(const std::vector<Place*>& path) {
    if (path.empty()) {
        std::cout << "Keine Route gefunden." << std::endl;
        return;
    }
    std::cout << "Route:" << std::endl;
    for (const Place* place : path) {
        std::cout << place->getName() << " -> ";
    }
    std::cout << "Ende" << std::endl;
}
void MainWindow::onGraphRebuild() {
    clearGraph();
    Place::setAllPlaces(&places);
    buildGraph();
}
void MainWindow::showRouteInfo(const std::vector<Place*>& path, const std::vector<double>& distances) {
    QString message = "Route:\n\n";
    double totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        message += QString::fromStdString(path[i]->getName());
        message += " -> ";
        message += QString::fromStdString(path[i + 1]->getName());
        message += QString(": %1 km\n").arg(distances[i], 0, 'f', 2);
        totalDistance += distances[i];
    }
    message += QString("\nGesamtentfernung: %1 km").arg(totalDistance, 0, 'f', 2);
    QMessageBox::information(this, "Routeninformation", message);
}
void MainWindow::drawRoute(const std::vector<Place*>& path) {
    deletegraphicroute();
    if (originalPixmap.isNull()) {
        originalPixmap = imageLabel->pixmap().copy();
    }
    QPixmap pixmap = imageLabel->pixmap().copy();
    QPainter painter(&pixmap);
    QPen routePen(Qt::red, 3);
    painter.setPen(routePen);
    for (size_t i = 0; i < path.size() - 1; ++i) {
        QPoint start = mapToImage(path[i]->getLatitude(), path[i]->getLongitude()).toPoint();
        QPoint end = mapToImage(path[i + 1]->getLatitude(), path[i + 1]->getLongitude()).toPoint();
        painter.drawLine(start, end);
    }
    imageLabel->setPixmap(pixmap);
    update();
}
void MainWindow::removePlace(Place* place, bool permanentDelete) {
    if (!place) return;
    for (auto* otherPlace : places) {
        if (otherPlace != place) {
            otherPlace->removeConnection(place);
        }
    }
    if (permanentDelete) {
        auto it = std::find(places.begin(), places.end(), place);
        if (it != places.end()) {
            places.erase(it);
        }
        QList<QLabel*> markers = imageLabel->findChildren<QLabel*>();
        for (QLabel* marker : markers) {
            if (marker->property("placeId").toInt() == place->getId()) {
                marker->deleteLater();
                break;
            }
        }
        delete place;
    } else {
        place->setActive(false);
    }
    Place::setAllPlaces(&places);
    buildGraph();
}
void MainWindow::drawGraph(){
    QPixmap pixmap = imageLabel->pixmap().copy();
    QPainter painter(&pixmap);
    QPen connectionPen(QColor(173, 216, 230), 1);
    painter.setPen(connectionPen);
    for (auto* place : places) {
        if (place->isActive()) {
            QPoint start = mapToImage(place->getLatitude(), place->getLongitude()).toPoint();
            const auto& connectionIDs = place->getConnections();
            for (int neighborID : connectionIDs) {
                Place* neighbor = Place::findPlaceById(neighborID);
                if (neighbor && neighbor->isActive()) {
                    QPoint end = mapToImage(neighbor->getLatitude(), neighbor->getLongitude()).toPoint();
                    painter.drawLine(start, end);
    }}}}
    imageLabel->setPixmap(pixmap);
    update();
}
void MainWindow::deletegraphicroute(){
    if (!originalPixmap.isNull()) {
        imageLabel->setPixmap(originalPixmap);
        originalPixmap = QPixmap();
        update();
    }
}
