#include "mainwindow.hpp"

MainWindow::MainWindow() : QMainWindow()
{
    this->setWindowTitle("电梯调度算法可视化演示");
    this->setFixedSize(WIDTH, HEIGHT);

    // 创建一个场景
    scene = new Scene();
    scene->initSurface();

    elevators.push_back(Elevator(10, 800, ALL));
    elevators.push_back(Elevator(10, 800, ODD));
    elevators.push_back(Elevator(10, 800, EVEN));
    elevators.push_back(Elevator(20, 2000, ALL));

    //"电梯1:当前载客人数: 当前载重: "
    label1 = new QLabel(this);
    label1->setFixedSize(250, 30);
    label1->move(700, 100);
    connect(this, &MainWindow::update1, label1,
            [=](int a, int b, int c)
            {
                label1->setText(QString("电梯1:当前载客人数:%1 载重:%2KG 等待人数:%3").arg(a).arg(b).arg(c));
            });

    label2 = new QLabel(this);
    label2->setFixedSize(250, 30);
    label2->move(700, 150);
        connect(this, &MainWindow::update2, label2,
            [=](int a, int b, int c)
            {
                label2->setText(QString("电梯2:当前载客人数:%1 载重:%2KG 等待人数:%3").arg(a).arg(b).arg(c));
            });

    label3 = new QLabel(this);
    label3->setFixedSize(250, 30);
    label3->move(700, 200);
        connect(this, &MainWindow::update3, label3,
            [=](int a, int b, int c)
            {
                label3->setText(QString("电梯3:当前载客人数:%1 载重:%2KG 等待人数:%3").arg(a).arg(b).arg(c));
            });

    label4 = new QLabel(this);
    label4->setFixedSize(250, 30);
    label4->move(700, 250);
        connect(this, &MainWindow::update4, label4,
            [=](int a, int b, int c)
            {
                label4->setText(QString("电梯4:当前载客人数:%1 载重:%2KG 等待人数:%3").arg(a).arg(b).arg(c));
            });

    // 添加电梯选择框
    elevatorComboBox = new QComboBox(this);
    for (int i = 1; i <= 4; i++)
    {
        elevatorComboBox->addItem(QString::number(i));
    }
    elevatorComboBox->move(800, 350); // 设置位置
    // 添加电梯选择框的标签
    QLabel *elevatorLabel = new QLabel("电梯编号:", this);
    elevatorLabel->move(740, 350);
    // 连接信号
    connect(elevatorComboBox, &QComboBox::currentIndexChanged, this,
            &MainWindow::changeElevator);

    // 添加开始楼层选择框
    startFloorComboBox = new QComboBox(this);
    for (int i = 1; i <= 20; i++)
    {
        startFloorComboBox->addItem(QString::number(i));
    }
    startFloorComboBox->move(800, 400); // 设置位置
    // 添加电梯选择框的标签
    QLabel *startFloorLabel = new QLabel("起始楼层:", this);
    startFloorLabel->move(740, 400); // 设置位置
    connect(startFloorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeStartFloor);

    // 创建目标楼层选择框
    targetFloorComboBox = new QComboBox(this);
    for (int i = 1; i <= 20; i++)
    {
        targetFloorComboBox->addItem(QString::number(i));
    }
    targetFloorComboBox->move(800, 450); // 设置位置
    QLabel *targetFlooLabel = new QLabel("目标楼层:", this);
    targetFlooLabel->move(740, 450); // 设置位置
    connect(targetFloorComboBox, &QComboBox::currentIndexChanged, this, &MainWindow::changeTargetFloor);

    weightBox = new QSpinBox(this);
    weightBox->move(800, 500); // 设置位置
    connect(weightBox, &QSpinBox::valueChanged, this,
            [=](int value)
            { p_weight = value; });
    weightBox->setValue(50); // 设置初始显示值为50
    QLabel *weightBoxLabel = new QLabel("客人体重:", this);
    weightBoxLabel->move(740, 500); // 设置位置

    QPushButton *generateButton = new QPushButton("生成客人", this);
    generateButton->move(800, 550);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::generatePassenger);

    QPushButton *startButton = new QPushButton("开始运行", this);
    startButton->move(800, 600);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::refresh);

    // 将场景设置到视图
    QGraphicsView *view = new QGraphicsView(scene);
    view->setParent(this);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 关闭水平滚动条
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // 关闭垂直滚动条
    view->setFixedSize(720, HEIGHT);
    view->move(0, 0);
    view->setStyleSheet("background: transparent; border: none;");
};

void MainWindow::generatePassenger()
{
    elevators[currentElevator].addWatingPassager(Passager(p_startFloor, p_targetFloor, p_weight));
    emit(update1(elevators[0].getCurrentNum(), elevators[0].getCurrentWeight(), (int)elevators[0].wattings.size()));
    emit(update2(elevators[1].getCurrentNum(), elevators[1].getCurrentWeight(), (int)elevators[1].wattings.size()));
    emit(update3(elevators[2].getCurrentNum(), elevators[2].getCurrentWeight(), (int)elevators[2].wattings.size()));
    emit(update4(elevators[3].getCurrentNum(), elevators[3].getCurrentWeight(), (int)elevators[3].wattings.size()));
}

void MainWindow::refresh()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            scene->matrix[i][j]->setReset();
        }
    }
    for (int i = 0;i < elevators.size();i++)
    {
        elevators[i].work();
        if(elevators[i].status == STOP)
        {
            scene->getRect(elevators[i].currentFloor, i + 1)->setStop();
        }
        else if(elevators[i].status == UP)
        {
            scene->getRect(elevators[i].currentFloor, i + 1)->setUp();
        }
        else if(elevators[i].status == DOWN)
        {
            scene->getRect(elevators[i].currentFloor, i + 1)->setDown();
        }
    }
    emit(update1(elevators[0].getCurrentNum(), elevators[0].getCurrentWeight(), (int)elevators[0].wattings.size()));
    emit(update2(elevators[1].getCurrentNum(), elevators[1].getCurrentWeight(), (int)elevators[1].wattings.size()));
    emit(update3(elevators[2].getCurrentNum(), elevators[2].getCurrentWeight(), (int)elevators[2].wattings.size()));
    emit(update4(elevators[3].getCurrentNum(), elevators[3].getCurrentWeight(), (int)elevators[3].wattings.size()));
}


void MainWindow::changeElevator(int index)
{
    currentElevator = index;
    if (currentElevator == 0 || currentElevator == 3)
    {
        startFloorComboBox->clear();
        targetFloorComboBox->clear();
        for (int i = 1; i <= 20; i++)
        {
            startFloorComboBox->addItem(QString::number(i));
            targetFloorComboBox->addItem(QString::number(i));
        }
    }
    else if (currentElevator == 1)
    {
        startFloorComboBox->clear();
        targetFloorComboBox->clear();
        for (int i = 1; i <= 20; i++)
        {
            if (i % 2 == 1)
            {
                startFloorComboBox->addItem(QString::number(i));
                targetFloorComboBox->addItem(QString::number(i));
            }
        }
    }
    else if (currentElevator == 2)
    {
        startFloorComboBox->clear();
        targetFloorComboBox->clear();
        for (int i = 1; i <= 20; i++)
        {
            if (i % 2 == 0)
            {
                startFloorComboBox->addItem(QString::number(i));
                targetFloorComboBox->addItem(QString::number(i));
            }
        }
    }
}


void MainWindow::changeStartFloor(int index)
{
    if(currentElevator == 0 || currentElevator == 3)
    {
        p_startFloor = index + 1;
    }
    else if(currentElevator == 1)
    {
        p_startFloor = index * 2 + 1;
    }
    else if(currentElevator == 2)
    {
        p_startFloor = index * 2 + 2;
    }
}
void MainWindow::changeTargetFloor(int index)
{
    if(currentElevator == 0 || currentElevator == 3)
    {
        p_targetFloor = index + 1;
    }
    else if(currentElevator == 1)
    {
        p_targetFloor = index * 2 + 1;
    }
    else if(currentElevator == 2)
    {
        p_targetFloor = index * 2 + 2;
    }
}