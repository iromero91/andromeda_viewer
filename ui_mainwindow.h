/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "viewers/symbol_editor_view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *clearAllButton;
    QPushButton *deleteButton;
    QFrame *line;
    QPushButton *lineButton;
    QPushButton *polyButton;
    QPushButton *rectLine;
    QPushButton *ellipseButton;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *json;
    SymbolEditorView *graphicsView;
    QPlainTextEdit *prop;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1065, 618);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        clearAllButton = new QPushButton(groupBox);
        clearAllButton->setObjectName(QStringLiteral("clearAllButton"));

        verticalLayout->addWidget(clearAllButton);

        deleteButton = new QPushButton(groupBox);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        verticalLayout->addWidget(deleteButton);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        lineButton = new QPushButton(groupBox);
        lineButton->setObjectName(QStringLiteral("lineButton"));

        verticalLayout->addWidget(lineButton);

        polyButton = new QPushButton(groupBox);
        polyButton->setObjectName(QStringLiteral("polyButton"));

        verticalLayout->addWidget(polyButton);

        rectLine = new QPushButton(groupBox);
        rectLine->setObjectName(QStringLiteral("rectLine"));

        verticalLayout->addWidget(rectLine);

        ellipseButton = new QPushButton(groupBox);
        ellipseButton->setObjectName(QStringLiteral("ellipseButton"));

        verticalLayout->addWidget(ellipseButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(groupBox, 0, 2, 2, 1);

        json = new QPlainTextEdit(centralWidget);
        json->setObjectName(QStringLiteral("json"));
        json->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(json, 3, 0, 1, 1);

        graphicsView = new SymbolEditorView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 1, 4, 1);

        prop = new QPlainTextEdit(centralWidget);
        prop->setObjectName(QStringLiteral("prop"));
        prop->setMaximumSize(QSize(200, 16777215));

        gridLayout->addWidget(prop, 1, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1065, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "TOOLZ", 0));
#ifndef QT_NO_TOOLTIP
        clearAllButton->setToolTip(QApplication::translate("MainWindow", "Clear the entire scene", 0));
#endif // QT_NO_TOOLTIP
        clearAllButton->setText(QApplication::translate("MainWindow", "Clear All", 0));
#ifndef QT_NO_TOOLTIP
        deleteButton->setToolTip(QApplication::translate("MainWindow", "Delete selected objects", 0));
#endif // QT_NO_TOOLTIP
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", 0));
#ifndef QT_NO_TOOLTIP
        lineButton->setToolTip(QApplication::translate("MainWindow", "Add a new line", 0));
#endif // QT_NO_TOOLTIP
        lineButton->setText(QApplication::translate("MainWindow", "Line", 0));
#ifndef QT_NO_TOOLTIP
        polyButton->setToolTip(QApplication::translate("MainWindow", "Add a polygon", 0));
#endif // QT_NO_TOOLTIP
        polyButton->setText(QApplication::translate("MainWindow", "Poly", 0));
#ifndef QT_NO_TOOLTIP
        rectLine->setToolTip(QApplication::translate("MainWindow", "Add a rectangle", 0));
#endif // QT_NO_TOOLTIP
        rectLine->setText(QApplication::translate("MainWindow", "Rect", 0));
#ifndef QT_NO_TOOLTIP
        ellipseButton->setToolTip(QApplication::translate("MainWindow", "Add an ellipse", 0));
#endif // QT_NO_TOOLTIP
        ellipseButton->setText(QApplication::translate("MainWindow", "Ellipse", 0));
        label->setText(QApplication::translate("MainWindow", "Property Inspector", 0));
        label_2->setText(QApplication::translate("MainWindow", "JSON Inspector", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
