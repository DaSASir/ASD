#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>

#include "TableElementWidget.h"

#include "BaseHashTableWidget.h"

class SceneHashTableWidget : public BaseHashTableWidget
{
public:
    SceneHashTableWidget(QWidget *parent = nullptr);

protected slots:
    void addKeyValue() override;
    void resizeTable() override;
    void findByKey() override;
    void removeByKey() override;

private:
    struct ElementData
    {
        TableElementWidget* widget = nullptr;
        QGraphicsProxyWidget* proxy = nullptr;
    };

private:
    void addBlankElement(int row, int column);
    void updateTable();
    void clearScene();

private:
    QGraphicsScene *m_scene = nullptr; //Сцена, на которой размещаются элементы таблицы.
    QGraphicsView *m_view = nullptr;//отображение заданной области сцены (сцена может быть намного больше видимой части)
    QVector<QVector<ElementData>> m_rows;
};
