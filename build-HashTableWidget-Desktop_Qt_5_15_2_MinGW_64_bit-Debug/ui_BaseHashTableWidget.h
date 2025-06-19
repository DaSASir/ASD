/********************************************************************************
** Form generated from reading UI file 'BaseHashTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASEHASHTABLEWIDGET_H
#define UI_BASEHASHTABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseHashTableWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_size;
    QSpinBox *spinBox_size;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_key;
    QSpinBox *spinBox_key;
    QLabel *label_value;
    QLineEdit *lineEdit_value;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_add;
    QPushButton *pushButton_remove;
    QPushButton *pushButton_find;

    void setupUi(QWidget *BaseHashTableWidget)
    {
        if (BaseHashTableWidget->objectName().isEmpty())
            BaseHashTableWidget->setObjectName(QString::fromUtf8("BaseHashTableWidget"));
        BaseHashTableWidget->resize(797, 580);
        QFont font;
        font.setPointSize(24);
        BaseHashTableWidget->setFont(font);
        verticalLayout = new QVBoxLayout(BaseHashTableWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_size = new QLabel(BaseHashTableWidget);
        label_size->setObjectName(QString::fromUtf8("label_size"));

        gridLayout->addWidget(label_size, 0, 0, 1, 1);

        spinBox_size = new QSpinBox(BaseHashTableWidget);
        spinBox_size->setObjectName(QString::fromUtf8("spinBox_size"));
        spinBox_size->setMinimum(1);

        gridLayout->addWidget(spinBox_size, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_key = new QLabel(BaseHashTableWidget);
        label_key->setObjectName(QString::fromUtf8("label_key"));

        horizontalLayout_2->addWidget(label_key);

        spinBox_key = new QSpinBox(BaseHashTableWidget);
        spinBox_key->setObjectName(QString::fromUtf8("spinBox_key"));
        spinBox_key->setMinimum(-999999999);
        spinBox_key->setMaximum(999999999);

        horizontalLayout_2->addWidget(spinBox_key);

        label_value = new QLabel(BaseHashTableWidget);
        label_value->setObjectName(QString::fromUtf8("label_value"));

        horizontalLayout_2->addWidget(label_value);

        lineEdit_value = new QLineEdit(BaseHashTableWidget);
        lineEdit_value->setObjectName(QString::fromUtf8("lineEdit_value"));

        horizontalLayout_2->addWidget(lineEdit_value);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_add = new QPushButton(BaseHashTableWidget);
        pushButton_add->setObjectName(QString::fromUtf8("pushButton_add"));

        horizontalLayout->addWidget(pushButton_add);

        pushButton_remove = new QPushButton(BaseHashTableWidget);
        pushButton_remove->setObjectName(QString::fromUtf8("pushButton_remove"));

        horizontalLayout->addWidget(pushButton_remove);

        pushButton_find = new QPushButton(BaseHashTableWidget);
        pushButton_find->setObjectName(QString::fromUtf8("pushButton_find"));

        horizontalLayout->addWidget(pushButton_find);


        gridLayout->addLayout(horizontalLayout, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(BaseHashTableWidget);

        QMetaObject::connectSlotsByName(BaseHashTableWidget);
    } // setupUi

    void retranslateUi(QWidget *BaseHashTableWidget)
    {
        BaseHashTableWidget->setWindowTitle(QCoreApplication::translate("BaseHashTableWidget", "Widget", nullptr));
        label_size->setText(QCoreApplication::translate("BaseHashTableWidget", "Size:", nullptr));
        label_key->setText(QCoreApplication::translate("BaseHashTableWidget", "Key:", nullptr));
        label_value->setText(QCoreApplication::translate("BaseHashTableWidget", "Value:", nullptr));
        pushButton_add->setText(QCoreApplication::translate("BaseHashTableWidget", "Add", nullptr));
        pushButton_remove->setText(QCoreApplication::translate("BaseHashTableWidget", "Remove", nullptr));
        pushButton_find->setText(QCoreApplication::translate("BaseHashTableWidget", "Find", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BaseHashTableWidget: public Ui_BaseHashTableWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASEHASHTABLEWIDGET_H
