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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/viewers/symbol_editor_view.h"

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
    SymbolEditorView *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QPlainTextEdit *propText;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *jsonText;
    QWidget *tab_3;
    QGridLayout *gridLayout_4;
    QPlainTextEdit *undoText;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1065, 731);
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

        graphicsView = new SymbolEditorView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 1, 3, 1);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setMaximumSize(QSize(250, 16777215));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        propText = new QPlainTextEdit(tab);
        propText->setObjectName(QStringLiteral("propText"));
        propText->setReadOnly(true);

        gridLayout_2->addWidget(propText, 0, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        jsonText = new QPlainTextEdit(tab_2);
        jsonText->setObjectName(QStringLiteral("jsonText"));
        jsonText->setReadOnly(true);

        gridLayout_3->addWidget(jsonText, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_4 = new QGridLayout(tab_3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        undoText = new QPlainTextEdit(tab_3);
        undoText->setObjectName(QStringLiteral("undoText"));
        undoText->setReadOnly(true);

        gridLayout_4->addWidget(undoText, 0, 0, 1, 1);

        tabWidget->addTab(tab_3, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1065, 21));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


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
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Properties", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "JSON", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Undo Stack", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
