#include <QGraphicsProxyWidget>
#include <QMessageBox>

#include "TableElementWidget.h"

#include "SceneHashTableWidget.h"
#include "ui_BaseHashTableWidget.h"

#include "../laba-HashTable-Tychinsky/laba-HashTable-Tychinsky/HashTable.h"

SceneHashTableWidget::SceneHashTableWidget(QWidget *parent)
    : BaseHashTableWidget(parent)
    , m_scene(new QGraphicsScene(this))
    , m_view(new QGraphicsView(this))
{
    m_view->setScene(m_scene);
    ui->verticalLayout->insertWidget(0, m_view);
    SceneHashTableWidget::resizeTable();
}

void SceneHashTableWidget::addKeyValue() {
    int key = ui->spinBox_key->value();
    QString value = ui->lineEdit_value->text();

    if (m_hashTable->contains(key))
        onValueChanged(key, value);
    else
        m_hashTable->add(key, value);

    updateTable();
}

void SceneHashTableWidget::removeByKey() {
    int key = ui->spinBox_key->value();
    if (!m_hashTable->contains(key)) return;

    m_hashTable->remove(key);
    updateTable();
}

void SceneHashTableWidget::findByKey() {
    int key = ui->spinBox_key->value();
    if (m_hashTable->contains(key))
        QMessageBox::information(this, "Выполнено", QString("Значение ключа: %1").arg((*m_hashTable)[key]));
    else
        QMessageBox::information(this, "Не Выполнено", "Ключ не найден");
}

void SceneHashTableWidget::resizeTable() {
    m_hashTable->resize(ui->spinBox_size->value());
    updateTable();
}

void SceneHashTableWidget::updateTable() {
    clearScene();
    m_rows.resize(m_hashTable->size());

    auto& table = m_hashTable->table();
    for (int row = 0; row < m_hashTable->size(); row++) {
        addBlankElement(row, 0);

        if (!table[row].empty()) {
            m_rows[row][0].widget->setKey(table[row].front().first);
            m_rows[row][0].widget->setValue(table[row].front().second);

            int col = 1;
            for (auto it = ++table[row].begin(); it != table[row].end(); ++it) {
                addBlankElement(row, col);
                m_rows[row][col].widget->setKey(it->first);
                m_rows[row][col].widget->setValue(it->second);
                col++;
            }
        }
    }
}

void SceneHashTableWidget::clearScene() {
    for (QVector row : m_rows) {
        for (ElementData element : row) {
            m_scene->removeItem(element.proxy);
            element.widget->deleteLater();
        }
        row.clear();
    }
    m_rows.clear();
}

void SceneHashTableWidget::addBlankElement(int row, int column)
{
    //m_tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(QString::number(i)));
    TableElementWidget *item = new TableElementWidget();
    //item->setTextAlignment(Qt::AlignCenter);
    //item->setFlags(item->flags() & ~Qt::ItemIsEditable);

    connect(item, &TableElementWidget::valueChanged, this, &SceneHashTableWidget::onValueChanged);

    QGraphicsProxyWidget* proxy = m_scene->addWidget(item);
    column = m_rows[row].size();
    int x = column * (item->width() + 50);
    int y = row * item->height();
    proxy->setX(x);
    proxy->setY(y);

    if (column)
    {
        int centerY = item->height() / 2;
        auto* line = m_scene->addLine(-50, centerY, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2, 0, centerY);
        line->setParentItem(proxy);
        line = m_scene->addLine(-centerY / 2, centerY / 2 * 3, 0, centerY);
        line->setParentItem(proxy);
    }

    m_rows[row].append({item, proxy});
}
