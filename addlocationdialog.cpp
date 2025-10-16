#include "addlocationdialog.h"
#include "ui_addlocationdialog.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "addresswidget.h"  // Include the AddressWidget header

addLocationDialog::addLocationDialog(MainWindow *mainWindow, QWidget *parent)
    : QDialog(parent), addressWidget(nullptr), m_mainWindow(mainWindow) // Initialize addressWidget to nullptr
{
    setWindowTitle("Neuer Ort");
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Welcher Ort?", this);
    layout->addWidget(label);
    placeButton = new QPushButton("Ort", this);
    addressButton = new QPushButton("Adresse", this);
    poiButton = new QPushButton("Point of Interest", this);
    layout->addWidget(placeButton);
    layout->addWidget(addressButton);
    layout->addWidget(poiButton);
    connect(placeButton, &QPushButton::clicked, this, &addLocationDialog::accept);
    connect(poiButton, &QPushButton::clicked, this, &addLocationDialog::accept);
    // Connect the addressButton to show AddressWidget
    connect(addressButton, &QPushButton::clicked, this, &addLocationDialog::onaddresclicked);
}
addLocationDialog::~addLocationDialog()
{
    delete addressWidget;  // Ensure the AddressWidget is deleted when AddLocationDialog is destroyed
}
void addLocationDialog::onaddresclicked()
{
    AddressWidget * addreswidget= new AddressWidget;
    addreswidget->show();
    connect(addreswidget, &AddressWidget::addressSubmitted, this, &addLocationDialog::onAddressSubmitted);

}
void addLocationDialog::onAddressSubmitted()
{
    AddressWidget *addressWidget = qobject_cast<AddressWidget *>(sender());
    if (addressWidget) {
        QString name = addressWidget->getName();
        double latitude = addressWidget->getLatitude();
        double longitude = addressWidget->getLongitude();
        QString street = addressWidget->getStreet();
        QString houseNumber = addressWidget->getHouseNumber();
        QString postalCode = addressWidget->getPostalCode();
        QString municipality = addressWidget->getMunicipality();
      /*  if (name.isEmpty() || street.isEmpty() || houseNumber.isEmpty() || postalCode.isEmpty() || municipality.isEmpty()) {
            QMessageBox::warning(this, "Fehler", "Bitte füllen Sie alle Felder aus.");
            return;
        }*/
        Address *newPlace = new Address(name.toStdString(), latitude, longitude,
                                        street.toStdString(), houseNumber.toStdString(),
                                        postalCode.toStdString(), municipality.toStdString());
        m_mainWindow->getPlaces().push_back(newPlace);
        QPoint position = m_mainWindow->mapToImage(newPlace->getLatitude(), newPlace->getLongitude()).toPoint();
        m_mainWindow->addLocation(*newPlace,position);
        emit locationAdded(); // Signal that a location was added
        close();
    }
}
