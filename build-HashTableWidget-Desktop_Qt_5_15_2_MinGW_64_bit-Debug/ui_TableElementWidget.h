/********************************************************************************
** Form generated from reading UI file 'TableElementWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLEELEMENTWIDGET_H
#define UI_TABLEELEMENTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableElementWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_key;
    QLineEdit *lineEdit_value;

    void setupUi(QWidget *TableElementWidget)
    {
        if (TableElementWidget->objectName().isEmpty())
            TableElementWidget->setObjectName(QString::fromUtf8("TableElementWidget"));
        TableElementWidget->resize(124, 22);
        QFont font;
        font.setPointSize(24);
        TableElementWidget->setFont(font);
        horizontalLayout = new QHBoxLayout(TableElementWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_key = new QLineEdit(TableElementWidget);
        lineEdit_key->setObjectName(QString::fromUtf8("lineEdit_key"));

        horizontalLayout->addWidget(lineEdit_key);

        lineEdit_value = new QLineEdit(TableElementWidget);
        lineEdit_value->setObjectName(QString::fromUtf8("lineEdit_value"));

        horizontalLayout->addWidget(lineEdit_value);


        retranslateUi(TableElementWidget);

        QMetaObject::connectSlotsByName(TableElementWidget);
    } // setupUi

    void retranslateUi(QWidget *TableElementWidget)
    {
        TableElementWidget->setWindowTitle(QCoreApplication::translate("TableElementWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TableElementWidget: public Ui_TableElementWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLEELEMENTWIDGET_H
