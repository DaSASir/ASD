#pragma once

#include <QWidget>

namespace Ui {
class TableElementWidget;
}

class TableElementWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableElementWidget(QWidget *parent = nullptr);
    ~TableElementWidget();

    int key() const;
    QString value() const;

    void setKey(int key);
    void setValue(const QString &value);
    bool isEmpty() const;
    void clear();

signals:
    void valueChanged(int key, const QString &value);

private slots:
    void onValueChanged(const QString &value);

private:
    Ui::TableElementWidget *ui;
};

