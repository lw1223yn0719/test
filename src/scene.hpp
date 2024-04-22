#pragma once
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "manager.hpp"

class Rect : public QGraphicsRectItem
{
public:
    bool isElevator = false;
    int floor;
    int elevator;
    QGraphicsTextItem *label;
    QColor color1 = QColor(255, 255, 255); // 白色
    QColor color2 = QColor(0, 51, 51);     // 黑色
    QColor color3 = QColor(204, 204, 153); // 浅色
    QColor color4 = QColor(253, 153, 0);   // 红色
    Rect(int x, int y, int width, int height, QColor c, QGraphicsScene *scene) : QGraphicsRectItem(x, y, width, height)
    {
        this->setBrush(QBrush(c));
        this->setPen(QPen(color1));
        label = new QGraphicsTextItem("", this);
        label->setPos(boundingRect().center() - label->boundingRect().center());
        scene->addItem(this);
    }
    void setText(QString text)
    {
        // 创建一个文本项
        // 将文本项的位置设置在矩形项的中心
        label->setPlainText(text);
        label->setPos(boundingRect().center() - label->boundingRect().center());
        label->setDefaultTextColor(color1); 
    }

    inline void setUp()
    {
        label->setPlainText("上");
        label->setPos(boundingRect().center() - label->boundingRect().center());
        label->setDefaultTextColor(QColor(0, 0, 0)); 
        this->setBrush(color4);
    }
    inline void setDown()
    {
        label->setPlainText("下");
        label->setPos(boundingRect().center() - label->boundingRect().center());
        label->setDefaultTextColor(QColor(0, 0, 0)); 
        this->setBrush(color4);
    }
    inline void setStop()
    {
        label->setPlainText("停");
        label->setPos(boundingRect().center() - label->boundingRect().center());
        label->setDefaultTextColor(QColor(0, 0, 0)); 
        this->setBrush(color4);
    }
    inline void setReset()
    {
        label->setPlainText("");
        label->setPos(boundingRect().center() - label->boundingRect().center());
        label->setDefaultTextColor(QColor(0, 0, 0)); 
        this->setBrush(color3);
    }
};

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject *parent = nullptr): QGraphicsScene(parent)
    {
    }
private:


    QColor color1 = QColor(255, 255, 255); // 白色
    QColor color2 = QColor(0, 51, 51);     // 黑色
    QColor color3 = QColor(204, 204, 153); // 浅色
    QColor color4 = QColor(253, 153, 0);   // 红色
public:
    vector<vector<Rect*>> table;        //从上到下存储整个表格  先行后列
    vector<vector<Rect*>> matrix;       //存储20*4楼层  前一个为楼层数，后一个为电梯数
    inline Rect* getRect(int floor, int elevator)
    {
        return matrix[floor - 1][elevator - 1];
    }

    void initSurface();

};