/********************************************************************************
** Form generated from reading UI file 'frmvideopanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMVIDEOPANEL_H
#define UI_FRMVIDEOPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "videopanel.h"

QT_BEGIN_NAMESPACE

class Ui_frmVideoPanel
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    VideoPanel *widget;

    void setupUi(QWidget *frmVideoPanel)
    {
        if (frmVideoPanel->objectName().isEmpty())
            frmVideoPanel->setObjectName(QString::fromUtf8("frmVideoPanel"));
        frmVideoPanel->resize(400, 300);
        verticalLayout = new QVBoxLayout(frmVideoPanel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new VideoPanel(frmVideoPanel);
        widget->setObjectName(QString::fromUtf8("widget"));

        horizontalLayout->addWidget(widget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(frmVideoPanel);

        QMetaObject::connectSlotsByName(frmVideoPanel);
    } // setupUi

    void retranslateUi(QWidget *frmVideoPanel)
    {
        frmVideoPanel->setWindowTitle(QCoreApplication::translate("frmVideoPanel", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frmVideoPanel: public Ui_frmVideoPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMVIDEOPANEL_H
