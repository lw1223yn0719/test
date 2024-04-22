#include "manager.hpp"

void Elevator::loadPassager()
{
    for (auto p = wattings.begin(); p != wattings.end();)
    {
        if (getCurrentNum() + 1 <= maxNum &&
                getCurrentWeight() + p->weight <= maxWeight &&
                currentFloor == p->startFloor)
        {
            if(p->startFloor == p->targetFloor)
            {
                p = wattings.erase(p);
                continue;
            }
            passagers.push_back(*p);
            p = wattings.erase(p);
        }
        else
        {
            p++;
        }
    }

}

void Elevator::unloadPassager()
{
    for (auto p = passagers.begin(); p != passagers.end();)
    {
        if (currentFloor == p->targetFloor)
        {
            p = passagers.erase(p);
        }
        else
        {
            p++;
        }
    }
}

void Elevator::work()
{
    // 无人等待且电梯无人
    if (passagers.size() == 0 && wattings.size() == 0)
    {
        status = STOP;
        return;
    }

    if (passagers.size() != 0)
    {
        unloadPassager();
    }
    if (wattings.size() != 0)
    {
        loadPassager();
    }

    if (status == STOP && passagers.size() != 0)
    {
        if (passagers[0].startFloor > currentFloor)
        {
            status = UP;
        }
        else if (passagers[0].startFloor < currentFloor)
        {
            status = DOWN;
        }
        else if (passagers[0].startFloor == currentFloor)
        {
            if (passagers[0].targetFloor > currentFloor)
            {
                status = UP;
            }
            else if (passagers[0].targetFloor < currentFloor)
            {
                status = DOWN;
            }
            else if (passagers[0].targetFloor == currentFloor)
            {
                status = STOP;
            }
        }
    }

    if (status == STOP && wattings.size() != 0)
    {
        if (wattings[0].startFloor > currentFloor)
        {
            status = UP;
            move();
            return;
        }
        else if (wattings[0].startFloor < currentFloor)
        {
            status = DOWN;
            move();
            return;
        }
    }

    if (passagers.size() != 0 || wattings.size() != 0)
    {
        move();
        return;
    }


    if (passagers.size() == 0 && wattings.size() == 0)
    {
        status = STOP;
        return;
    }

}


void Elevator::move()
{
    if (status == UP)
    {
        if (currentFloor == 20)
        {
            status = DOWN;
            currentFloor--;
        }
        else
        {
            currentFloor++;
        }
    }
    else if (status == DOWN)
    {
        if (currentFloor == 1)
        {
            status = UP;
            currentFloor++;
        }
        else
        {
            currentFloor--;
        }
    }
}