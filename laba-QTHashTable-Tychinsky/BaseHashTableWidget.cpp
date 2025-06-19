#include "BaseHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

BaseHashTableWidget::BaseHashTableWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::BaseHashTableWidget)
    , m_hashTable(new HashTable<QString>(3))
{
    ui->setupUi(this);
    connect(ui->spinBox_size, &QSpinBox::editingFinished, this, &BaseHashTableWidget::resizeTable);
    connect(ui->pushButton_add, &QPushButton::clicked, this, &BaseHashTableWidget::addKeyValue);
    connect(ui->pushButton_find, &QPushButton::clicked, this, &BaseHashTableWidget::findByKey);
    connect(ui->pushButton_remove, &QPushButton::clicked, this, &BaseHashTableWidget::removeByKey);
}

BaseHashTableWidget::~BaseHashTableWidget()
{
    delete ui;
}

void BaseHashTableWidget::onValueChanged(int key, const QString &value)
{
    (*m_hashTable)[key] = value;
}
