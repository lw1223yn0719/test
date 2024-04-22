#include "scene.hpp"


void Scene::initSurface()
{

    // 方块的大小
    int blockWidth = 100;
    int blockHeight = 30;

    // 创建21*5的方块矩阵
    for (int i = 0; i < 21; i++)
    {
        vector<Rect *> line;
        for (int j = 0; j < 5; j++)
        {
            // 创建一个矩形项
            Rect *rect = new Rect(j * blockWidth, i * blockHeight, blockWidth, blockHeight, color2, this);
            line.push_back(rect);
        }
        table.push_back(line);
    }

    for (int i = 20; i >= 1; i--)
    {
        vector<Rect *> line;
        for (int j = 1; j < 5; j++)
        {
            table[i][j]->isElevator = true;
            table[i][j]->floor = std::abs(21 - i);
            table[i][j]->elevator = j;
            table[i][j]->setBrush(QBrush(color3));
            line.push_back(table[i][j]);
        }
        matrix.push_back(line);
    }

    // 第一行设置
    table[0][0]->setText(QString("楼层"));
    for(int i = 1; i < 5; i++)
    {
        table[0][i]->setText(QString("电梯%1").arg(i));
    }
    for(int i = 1; i < 21; i++)
    {
        table[i][0]->setText(QString("%1").arg(21 - i));
    }

}