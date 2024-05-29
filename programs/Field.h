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
    //�������� �������� ���� 
    Field(int x, int y, int bombs);

    //���������� ���� ������(��������� ������ ��� ���� ���� �� ������ ����)
    void bombs(int fx, int fy);

    //����� �������� ����
    void printField();

    //�������� ������ ������
    bool openCells(int x, int y);

    //�������� ������ ������ 
    bool openCell(int x, int y);
    

    //���������� ������ 
    void markCell(int x, int y);

    //�������� �������� 
    bool checkWin();
};