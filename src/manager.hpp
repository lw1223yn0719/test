#pragma once
#include <cstdlib> // 用于rand()函数
#include <ctime>   // 用于time()
#include <utility>
#include <set>
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

enum EStatus
{
    UP,
    DOWN,
    STOP
};

enum MoveType
{
    ODD,
    EVEN,
    ALL
};

class Passager
{
public:
    int weight;
    int startFloor;
    int targetFloor;
    bool wait = true;
    Passager(int start, int end,int w) : startFloor(start), targetFloor(end),weight(w) {}
};

class Elevator
{
public:
    int currentFloor;
    int maxNum;
    int maxWeight;
    EStatus status;
    MoveType type;
    Elevator(int num, int weight, MoveType t)
        : currentFloor(1), maxNum(num),  maxWeight(weight), status(STOP), type(t) {}
    vector<Passager> passagers;
    vector<Passager> wattings;
    void loadPassager();
    void unloadPassager();
    void work();
    void move();
    inline int getCurrentWeight()
    {
        int currentWeight = 0;
        for (auto &p : passagers)
        {
            currentWeight += p.weight;
        }
        return currentWeight;
    }
    inline int getCurrentNum()
    {
        return static_cast<int>(passagers.size());
    }
    inline void addWatingPassager(Passager p)
    {
        wattings.push_back(p);
    }


};
