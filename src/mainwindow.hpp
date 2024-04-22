#pragma once
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QVector>
#include <QLabel>

#include "scene.hpp"

const int WIDTH = 1080;
const int HEIGHT = 720;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
    ~MainWindow(){};
    vector<Elevator> elevators;

    void refresh();

public slots:
    void changeElevator(int index);
    void changeStartFloor(int index);
    void changeTargetFloor(int index);
    void generatePassenger();

signals:
    void update1(int a,int b,int c);
    void update2(int a,int b,int c);
    void update3(int a,int b,int c);
    void update4(int a,int b,int c);

public:
    QComboBox *startFloorComboBox;
    QComboBox *targetFloorComboBox;
    QComboBox *elevatorComboBox;
    QSpinBox *weightBox;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    Scene *scene;
    int currentElevator = 0;
    int p_startFloor = 1;
    int p_targetFloor = 1;
    int p_weight = 50;
};