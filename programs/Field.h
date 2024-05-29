#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"
using namespace std;

class Field {
private:
    vector<vector<Cell>> grid;
    int sizeX, sizeY;
    int numBombs;

public:
    //Создание игрового поля 
    Field(int x, int y, int bombs);

    //Заподнение поле минами(передется первый ход чтоб туда не попала мина)
    void bombs(int fx, int fy);

    //Вывод игрового поля
    void printField();

    //Открытие клеток вокруг
    bool openCells(int x, int y);

    //Открытие клеток вокруг 
    bool openCell(int x, int y);
    

    //Маркировка клетки 
    void markCell(int x, int y);

    //Проверка выигрыша 
    bool checkWin();
};