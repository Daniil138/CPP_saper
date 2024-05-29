#pragma once
#include <iostream>
#include "Bomb.h"

class Cell {
public:
    Bomb bomb = Bomb(false);
    bool isOpen = false;
    bool isMarked = false;
    int bombsAround = 0;
};