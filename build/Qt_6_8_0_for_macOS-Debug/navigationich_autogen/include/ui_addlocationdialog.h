/********************************************************************************
** Form generated from reading UI file 'addlocationdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDLOCATIONDIALOG_H
#define UI_ADDLOCATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_addLocationDialog
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *addLocationDialog)
    {
        if (addLocationDialog->objectName().isEmpty())
            addLocationDialog->setObjectName("addLocationDialog");
        addLocationDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(addLocationDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Orientation::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(addLocationDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, addLocationDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, addLocationDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(addLocationDialog);
    } // setupUi

    void retranslateUi(QDialog *addLocationDialog)
    {
        addLocationDialog->setWindowTitle(QCoreApplication::translate("addLocationDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addLocationDialog: public Ui_addLocationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDLOCATIONDIALOG_H
