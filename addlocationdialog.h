#ifndef ADDLOCATIONDIALOG_H
#define ADDLOCATIONDIALOG_H

#include "mainwindow.h"

#include "addresswidget.h"
#include <QDialog>
#include "address.h"
#include "pointofinterest.h"


namespace Ui {
class addLocationDialog;
}

class addLocationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addLocationDialog(MainWindow* mainWindow,QWidget *parent = nullptr);
    ~addLocationDialog();


private slots:
    void onaddresclicked();
    void onAddressSubmitted();

signals:
 void locationAdded();

private:
    Ui::addLocationDialog *ui;
    QPushButton *placeButton;
    QPushButton *addressButton;
    QPushButton *poiButton;

    MainWindow* m_mainWindow;


    AddressWidget *addressWidget;
};

#endif // ADDLOCATIONDIALOG_H
