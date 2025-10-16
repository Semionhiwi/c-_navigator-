#ifndef ADDRESSWIDGET_H
#define ADDRESSWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class AddressWidget;
}

class AddressWidget : public QWidget
{
    Q_OBJECT

public:
    AddressWidget(QWidget *parent = nullptr);
    ~AddressWidget();

    QString getName() const;
    double getLatitude() const;
    double getLongitude() const;
    QString getStreet() const;
    QString getHouseNumber() const;
    QString getPostalCode() const;
    QString getMunicipality() const;

signals:
    void addressSubmitted();

public slots:
    void onSubmitButtonClicked();
private:
    Ui::AddressWidget *ui;

    QLineEdit *nameInput;
    QLineEdit *latitudeInput;
    QLineEdit *longitudeInput;
    QLineEdit *streetInput;
    QLineEdit *houseNumberInput;
    QLineEdit *postalCodeInput;
    QLineEdit *municipalityInput;


    bool isValidDouble(const QString &text) const;
};

#endif // ADDRESSWIDGET_H
