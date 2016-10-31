/********************************************************************************
** Form generated from reading UI file 'pin_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PIN_EDITOR_H
#define UI_PIN_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PinEditForm
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ok;
    QPushButton *cancel;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLineEdit *pinLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QComboBox *pinOrientation;
    QLabel *label_3;
    QSpinBox *pinLength;
    QLabel *label_4;

    void setupUi(QWidget *PinEditForm)
    {
        if (PinEditForm->objectName().isEmpty())
            PinEditForm->setObjectName(QStringLiteral("PinEditForm"));
        PinEditForm->resize(255, 168);
        gridLayout = new QGridLayout(PinEditForm);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        ok = new QPushButton(PinEditForm);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout->addWidget(ok);

        cancel = new QPushButton(PinEditForm);
        cancel->setObjectName(QStringLiteral("cancel"));

        horizontalLayout->addWidget(cancel);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        label = new QLabel(PinEditForm);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pinLabel = new QLineEdit(PinEditForm);
        pinLabel->setObjectName(QStringLiteral("pinLabel"));

        gridLayout->addWidget(pinLabel, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

        label_2 = new QLabel(PinEditForm);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        pinOrientation = new QComboBox(PinEditForm);
        pinOrientation->setObjectName(QStringLiteral("pinOrientation"));

        gridLayout->addWidget(pinOrientation, 1, 1, 1, 1);

        label_3 = new QLabel(PinEditForm);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pinLength = new QSpinBox(PinEditForm);
        pinLength->setObjectName(QStringLiteral("pinLength"));
        pinLength->setMinimum(50);
        pinLength->setMaximum(250);
        pinLength->setSingleStep(25);

        gridLayout->addWidget(pinLength, 2, 1, 1, 1);

        label_4 = new QLabel(PinEditForm);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 2, 2, 1, 1);


        retranslateUi(PinEditForm);

        QMetaObject::connectSlotsByName(PinEditForm);
    } // setupUi

    void retranslateUi(QWidget *PinEditForm)
    {
        PinEditForm->setWindowTitle(QApplication::translate("PinEditForm", "Form", 0));
        ok->setText(QApplication::translate("PinEditForm", "&Ok", 0));
        cancel->setText(QApplication::translate("PinEditForm", "&Cancel", 0));
        label->setText(QApplication::translate("PinEditForm", "Label", 0));
        label_2->setText(QApplication::translate("PinEditForm", "Orientation", 0));
        pinOrientation->clear();
        pinOrientation->insertItems(0, QStringList()
         << QApplication::translate("PinEditForm", "LEFT", 0)
         << QApplication::translate("PinEditForm", "DOWN", 0)
         << QApplication::translate("PinEditForm", "RIGHT", 0)
         << QApplication::translate("PinEditForm", "UP", 0)
        );
        label_3->setText(QApplication::translate("PinEditForm", "Length", 0));
        label_4->setText(QApplication::translate("PinEditForm", "units", 0));
    } // retranslateUi

};

namespace Ui {
    class PinEditForm: public Ui_PinEditForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PIN_EDITOR_H
