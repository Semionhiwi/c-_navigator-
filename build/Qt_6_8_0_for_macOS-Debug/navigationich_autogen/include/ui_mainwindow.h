/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionspeichern;
    QAction *actionladen;
    QAction *actionOrte_Laden;
    QAction *actionOrte_Laden_2;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuDatei;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionspeichern = new QAction(MainWindow);
        actionspeichern->setObjectName("actionspeichern");
        actionladen = new QAction(MainWindow);
        actionladen->setObjectName("actionladen");
        actionOrte_Laden = new QAction(MainWindow);
        actionOrte_Laden->setObjectName("actionOrte_Laden");
        actionOrte_Laden_2 = new QAction(MainWindow);
        actionOrte_Laden_2->setObjectName("actionOrte_Laden_2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 36));
        menuDatei = new QMenu(menubar);
        menuDatei->setObjectName("menuDatei");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDatei->menuAction());
        menuDatei->addAction(actionspeichern);
        menuDatei->addAction(actionladen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionspeichern->setText(QCoreApplication::translate("MainWindow", "speichern", nullptr));
        actionladen->setText(QCoreApplication::translate("MainWindow", "laden", nullptr));
        actionOrte_Laden->setText(QCoreApplication::translate("MainWindow", "Orte Laden", nullptr));
        actionOrte_Laden_2->setText(QCoreApplication::translate("MainWindow", "Orte Laden", nullptr));
        menuDatei->setTitle(QCoreApplication::translate("MainWindow", "Datei", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
