/********************************************************************************
** Form generated from reading UI file 'addresswidget.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESSWIDGET_H
#define UI_ADDRESSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddressWidget
{
public:
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label;
    QLineEdit *houseNumberInput;
    QLineEdit *streetInput;
    QLineEdit *municipalityInput;
    QLineEdit *latitudeInput;
    QLabel *label_4;
    QLabel *NameLabel;
    QLabel *label_5;
    QLabel *label_3;
    QPushButton *submitButton;
    QLineEdit *longitudeInput;
    QLineEdit *NameInput;
    QLineEdit *postalCodeInput;
    QWidget *widget;

    void setupUi(QWidget *AddressWidget)
    {
        if (AddressWidget->objectName().isEmpty())
            AddressWidget->setObjectName("AddressWidget");
        AddressWidget->resize(533, 472);
        label_2 = new QLabel(AddressWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(220, 230, 111, 16));
        label_6 = new QLabel(AddressWidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(220, 420, 58, 16));
        label = new QLabel(AddressWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(220, 180, 101, 16));
        houseNumberInput = new QLineEdit(AddressWidget);
        houseNumberInput->setObjectName("houseNumberInput");
        houseNumberInput->setGeometry(QRect(220, 350, 113, 21));
        streetInput = new QLineEdit(AddressWidget);
        streetInput->setObjectName("streetInput");
        streetInput->setGeometry(QRect(220, 300, 113, 21));
        municipalityInput = new QLineEdit(AddressWidget);
        municipalityInput->setObjectName("municipalityInput");
        municipalityInput->setGeometry(QRect(220, 440, 113, 21));
        latitudeInput = new QLineEdit(AddressWidget);
        latitudeInput->setObjectName("latitudeInput");
        latitudeInput->setGeometry(QRect(220, 200, 113, 21));
        label_4 = new QLabel(AddressWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(220, 330, 91, 16));
        NameLabel = new QLabel(AddressWidget);
        NameLabel->setObjectName("NameLabel");
        NameLabel->setGeometry(QRect(220, 110, 111, 20));
        label_5 = new QLabel(AddressWidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(220, 380, 58, 16));
        label_3 = new QLabel(AddressWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(220, 280, 101, 16));
        submitButton = new QPushButton(AddressWidget);
        submitButton->setObjectName("submitButton");
        submitButton->setGeometry(QRect(390, 340, 100, 32));
        longitudeInput = new QLineEdit(AddressWidget);
        longitudeInput->setObjectName("longitudeInput");
        longitudeInput->setGeometry(QRect(220, 250, 113, 21));
        NameInput = new QLineEdit(AddressWidget);
        NameInput->setObjectName("NameInput");
        NameInput->setGeometry(QRect(220, 140, 113, 21));
        postalCodeInput = new QLineEdit(AddressWidget);
        postalCodeInput->setObjectName("postalCodeInput");
        postalCodeInput->setGeometry(QRect(220, 400, 113, 21));
        widget = new QWidget(AddressWidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(330, 360, 120, 80));

        retranslateUi(AddressWidget);

        QMetaObject::connectSlotsByName(AddressWidget);
    } // setupUi

    void retranslateUi(QWidget *AddressWidget)
    {
        AddressWidget->setWindowTitle(QCoreApplication::translate("AddressWidget", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("AddressWidget", "L\303\244ngengrad", nullptr));
        label_6->setText(QCoreApplication::translate("AddressWidget", "Stadt", nullptr));
        label->setText(QCoreApplication::translate("AddressWidget", "Breitengrad", nullptr));
        label_4->setText(QCoreApplication::translate("AddressWidget", "Hausnummer", nullptr));
        NameLabel->setText(QCoreApplication::translate("AddressWidget", "Name:", nullptr));
        label_5->setText(QCoreApplication::translate("AddressWidget", "PLZ", nullptr));
        label_3->setText(QCoreApplication::translate("AddressWidget", "Stra\303\237e", nullptr));
        submitButton->setText(QCoreApplication::translate("AddressWidget", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddressWidget: public Ui_AddressWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESSWIDGET_H
