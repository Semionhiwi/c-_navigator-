#include "addresswidget.h"
#include "ui_addresswidget.h"
#include <QMessageBox>

AddressWidget::AddressWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddressWidget)
{
    ui->setupUi(this);
    connect(ui->submitButton, &QPushButton::clicked, this, &AddressWidget::onSubmitButtonClicked);
    nameInput = ui->NameInput;
    latitudeInput = ui->latitudeInput;
    longitudeInput = ui->longitudeInput;
    streetInput = ui->streetInput;
    houseNumberInput = ui->houseNumberInput;
    postalCodeInput = ui->postalCodeInput;
    municipalityInput = ui->municipalityInput;
}
void AddressWidget::onSubmitButtonClicked() {
    if (!isValidDouble(ui->latitudeInput->text()) || !isValidDouble(ui->longitudeInput->text())) {
        QMessageBox::warning(this, "Ungültige Eingabe", "Bitte geben Sie gültige Dezimalwerte für Breitengrad und Längengrad ein.");
        return;
    }
    emit addressSubmitted();
    close();
}
AddressWidget::~AddressWidget()
{
    delete ui;
}
QString AddressWidget::getName() const { return nameInput->text(); }
double AddressWidget::getLatitude() const { return latitudeInput->text().toDouble(); }
double AddressWidget::getLongitude() const { return longitudeInput->text().toDouble(); }
QString AddressWidget::getStreet() const { return streetInput->text(); }
QString AddressWidget::getHouseNumber() const { return houseNumberInput->text(); }
QString AddressWidget::getPostalCode() const { return postalCodeInput->text(); }
QString AddressWidget::getMunicipality() const { return municipalityInput->text(); }

bool AddressWidget::isValidDouble(const QString &text) const {
    bool ok;
    text.toDouble(&ok);
    return ok;
}
