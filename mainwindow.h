#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QPixmap>
#include <QVBoxLayout>
#include <QPointF>
#include <vector>
#include <QPushButton>
#include <QRadioButton>

class Place;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addLocation(Place &place, const QPoint &position);
    void loadDefaultLocations();

    QPointF mapToImage(double latitude, double longitude) const ;


    QLabel *getImageLabel() const;

    std::vector<Place *> getPlaces() const;
    void findRoute(Place* start, Place* end);

private slots:
    void onaddLocationclicked();
    void onshowAllLocationsclicked();
    void onCalculateDistanceClicked();
    void onLocationSelected(bool checked);
    void onInformationclicked();
    void onMyLocationclicked();
    void onloadfileclicked();
    void onsavefileclicked();
    void changemyplace();
    void onRoutingclicked();
    void onRemovePlaceClicked();


private:

    struct Neighbor_Node {
        Place* place;
        double distance;
    };


    struct RouteInfo_Edge {
        double distance;
        int previousIndex;
        bool visited;

        RouteInfo_Edge() : distance(std::numeric_limits<double>::infinity()),
            previousIndex(-1), visited(false) {}
    };



    static bool compareByDistance(const Neighbor_Node& neighbor1, const Neighbor_Node& neighbor2);


    Ui::MainWindow *ui;
    QLabel *imageLabel;
    double minLatitude, maxLatitude;
    double minLongitude, maxLongitude;
    int imageWidth, imageHeight;
    std::vector<Place*>places;
    std::vector<QRadioButton *> locationRadioButtons;
    std::vector<Place*> meinOrt;

    QList<Place *> selectedPlaces;
    bool isDistanceCalculationMode = false;
    bool isinformation = false;
    bool isRouting = false;
    QLabel* currentMarker = nullptr;

    void buildGraph();
    void clearGraph();
    void findNearestNeighbors(Place* place, int numNeighbors = 3);
    void connectPlaces(Place* place1, Place* place2);
    void updatePlaceConnections();


    std::vector<Place*> reconstructPath(
        const std::vector<RouteInfo_Edge>& routeInfo,
        int startIndex,
        int endIndex
        );
    void displayRoute(const std::vector<Place*>& path);
    Place* firstSelectedPlace;    // Store first selection
    Place* secondSelectedPlace;   // Store second selection
    bool isFirstSelection;

    void onGraphRebuild();

    void showRouteInfo(const std::vector<Place*>& path, const std::vector<double>& distances);
    void drawRoute(const std::vector<Place*>& path);
    void removePlace(Place* place, bool permanentDelete = true);
    bool isRemovalMode = false;

    void drawGraph();

    void deletegraphicroute();

    QPixmap originalPixmap;



};
#endif // MAINWINDOW_H
