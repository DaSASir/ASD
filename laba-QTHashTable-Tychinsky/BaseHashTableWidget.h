#pragma once

#include <QWidget>
#include "../laba-HashTable-Tychinsky/laba-HashTable-Tychinsky/HashTable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BaseHashTableWidget; }
QT_END_NAMESPACE

class BaseHashTableWidget : public QWidget
{
    Q_OBJECT

public:
    BaseHashTableWidget(QWidget *parent = nullptr);
    ~BaseHashTableWidget() override;

protected slots:
    void onValueChanged(int key, const QString &value);

    virtual void addKeyValue() = 0;
    virtual void resizeTable() = 0;
    virtual void findByKey() = 0;
    virtual void removeByKey() = 0;

protected:
    Ui::BaseHashTableWidget *ui;
    HashTable<QString> *m_hashTable = nullptr;
};
