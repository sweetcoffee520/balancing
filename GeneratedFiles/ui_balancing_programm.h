/********************************************************************************
** Form generated from reading UI file 'balancing_programm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALANCING_PROGRAMM_H
#define UI_BALANCING_PROGRAMM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_balancing_programmClass
{
public:
    QAction *action_open;
    QAction *action_save;
    QAction *actioncod_adjust;
    QAction *actionird_adjust;
    QAction *actionori_data;
    QAction *actionleve_network;
    QAction *actionresult;
    QAction *actionhelp;
    QAction *action_close;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QMenu *file;
    QMenu *method;
    QMenu *display;
    QMenu *help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *balancing_programmClass)
    {
        if (balancing_programmClass->objectName().isEmpty())
            balancing_programmClass->setObjectName(QString::fromUtf8("balancing_programmClass"));
        balancing_programmClass->resize(837, 678);
        action_open = new QAction(balancing_programmClass);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Images/\346\211\223\345\274\200.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_open->setIcon(icon);
        action_open->setIconVisibleInMenu(true);
        action_open->setShortcutVisibleInContextMenu(false);
        action_save = new QAction(balancing_programmClass);
        action_save->setObjectName(QString::fromUtf8("action_save"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Images/\344\277\235\345\255\230.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_save->setIcon(icon1);
        actioncod_adjust = new QAction(balancing_programmClass);
        actioncod_adjust->setObjectName(QString::fromUtf8("actioncod_adjust"));
        actionird_adjust = new QAction(balancing_programmClass);
        actionird_adjust->setObjectName(QString::fromUtf8("actionird_adjust"));
        actionori_data = new QAction(balancing_programmClass);
        actionori_data->setObjectName(QString::fromUtf8("actionori_data"));
        actionleve_network = new QAction(balancing_programmClass);
        actionleve_network->setObjectName(QString::fromUtf8("actionleve_network"));
        actionresult = new QAction(balancing_programmClass);
        actionresult->setObjectName(QString::fromUtf8("actionresult"));
        actionhelp = new QAction(balancing_programmClass);
        actionhelp->setObjectName(QString::fromUtf8("actionhelp"));
        action_close = new QAction(balancing_programmClass);
        action_close->setObjectName(QString::fromUtf8("action_close"));
        centralWidget = new QWidget(balancing_programmClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        horizontalLayout->addWidget(tableWidget);

        balancing_programmClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(balancing_programmClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 837, 26));
        file = new QMenu(menuBar);
        file->setObjectName(QString::fromUtf8("file"));
        method = new QMenu(menuBar);
        method->setObjectName(QString::fromUtf8("method"));
        display = new QMenu(menuBar);
        display->setObjectName(QString::fromUtf8("display"));
        help = new QMenu(menuBar);
        help->setObjectName(QString::fromUtf8("help"));
        balancing_programmClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(balancing_programmClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        balancing_programmClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(balancing_programmClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        balancing_programmClass->setStatusBar(statusBar);

        menuBar->addAction(file->menuAction());
        menuBar->addAction(method->menuAction());
        menuBar->addAction(display->menuAction());
        menuBar->addAction(help->menuAction());
        file->addAction(action_open);
        file->addSeparator();
        file->addAction(action_save);
        file->addSeparator();
        file->addAction(action_close);
        method->addAction(actioncod_adjust);
        method->addSeparator();
        method->addAction(actionird_adjust);
        display->addAction(actionori_data);
        display->addSeparator();
        display->addAction(actionleve_network);
        display->addSeparator();
        help->addAction(actionhelp);
        mainToolBar->addAction(action_open);
        mainToolBar->addAction(action_save);

        retranslateUi(balancing_programmClass);

        QMetaObject::connectSlotsByName(balancing_programmClass);
    } // setupUi

    void retranslateUi(QMainWindow *balancing_programmClass)
    {
        balancing_programmClass->setWindowTitle(QApplication::translate("balancing_programmClass", "\346\260\264\345\207\206\347\275\221\345\271\263\345\267\256\347\250\213\345\272\217", nullptr));
        action_open->setText(QApplication::translate("balancing_programmClass", "\346\211\223\345\274\200(&O)", nullptr));
        action_save->setText(QApplication::translate("balancing_programmClass", "\344\277\235\345\255\230(&S)", nullptr));
        actioncod_adjust->setText(QApplication::translate("balancing_programmClass", "\346\235\241\344\273\266\345\271\263\345\267\256", nullptr));
        actionird_adjust->setText(QApplication::translate("balancing_programmClass", "\351\227\264\346\216\245\345\271\263\345\267\256", nullptr));
        actionori_data->setText(QApplication::translate("balancing_programmClass", "\345\216\237\345\247\213\346\225\260\346\215\256", nullptr));
        actionleve_network->setText(QApplication::translate("balancing_programmClass", "\346\260\264\345\207\206\347\275\221", nullptr));
        actionresult->setText(QApplication::translate("balancing_programmClass", "\345\271\263\345\267\256\347\273\223\346\236\234", nullptr));
        actionhelp->setText(QApplication::translate("balancing_programmClass", "\345\270\256\345\212\251\346\226\207\346\241\243", nullptr));
        action_close->setText(QApplication::translate("balancing_programmClass", "\345\205\263\351\227\255", nullptr));
        file->setTitle(QApplication::translate("balancing_programmClass", "\346\226\207\344\273\266", nullptr));
        method->setTitle(QApplication::translate("balancing_programmClass", "\345\271\263\345\267\256\346\226\271\346\263\225", nullptr));
        display->setTitle(QApplication::translate("balancing_programmClass", "\346\230\276\347\244\272", nullptr));
        help->setTitle(QApplication::translate("balancing_programmClass", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class balancing_programmClass: public Ui_balancing_programmClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALANCING_PROGRAMM_H
