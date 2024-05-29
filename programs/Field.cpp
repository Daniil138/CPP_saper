#include <iostream>
#include <vector>
#include "Field.h"
#include "GameExeption.h"
using namespace std;



Field::Field(int x, int y, int bombs) : sizeX(x), sizeY(y), numBombs(bombs) {
    // �������������� ����� � ������ ������� ���� ��� �������� 
    grid.resize(sizeY, vector<Cell>(sizeX));    
}

void Field::bombs(int fx, int fy)
{   
    // ��������� ��� �������� ����� ������ ������� 
    if (fx < 0 || fx >= sizeX || fy < 0 || fy >= sizeY) {
        throw GameException("Invalid cell coordinates");
    }
    
    // �������� ������� ������ �� ��������� ������� 
    srand(time(NULL));

    //�������� ����������� �����
    for (int i = 0; i < numBombs; ++i) {

        int randX = rand() % sizeX;
        int randY = rand() % sizeY;

        if (!grid[randY][randX].bomb.Activite && randX!=fx && randY!=fy) {
            grid[randY][randX].bomb.Activite = true;
        }

        else {
            --i;
        }
    }
}


void Field::printField() {
    // ������� ������ ������ � ������� ��� ������� ����
    cout << "   ";
    for (int x = 0; x < sizeX; ++x) {
        cout << x + 1 << " ";
    }
    cout << endl;

    // ������� ��� � ����� ������
    for (int y = 0; y < sizeY; ++y) {
        // �������� ��� ����������� ������ ���� ������ �� ���� 
        if (y+1>=10)
            cout << y + 1 << " ";
        else 
            cout << y + 1 << "  ";

        // ����� ������ ���� 
        for (int x = 0; x < sizeX; ++x) {
            
            if (grid[y][x].isOpen) {
                if (grid[y][x].bomb.Activite) {
                    cout << "* ";
                }
                else {
                    cout << grid[y][x].bombsAround << " ";
                }
            }
            else {
                if (grid[y][x].isMarked)
                    cout << "M ";
                else
                    cout << ". ";
            }
        }
        cout << std::endl;
    }
}



bool Field::openCells(int x, int y) {
    
    //�������� �� �� ��� �� ��� ��� � ������� � �� �� ��� ������ ��� �������
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || grid[y][x].isOpen) {
        return true;
    }

    //��������� ������
    grid[y][x].isOpen = true;

    //�������� �� �����
    if (grid[y][x].bomb.Activite) {
        cout << "Game Over! You hit a bomb!" << endl;
        
        return false;
    }

    // ������� ���� ������ ������ 
    int bombs = 0;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int newX = x + dx;
            int newY = y + dy;
            if (newX >= 0 && newX < sizeX && newY >= 0 && newY < sizeY && grid[newY][newX].bomb.Activite) {
                ++bombs;
            }
        }
    }
    grid[y][x].bombsAround = bombs;

    if (bombs == 0) {
        // ���� ������ ������, ���������� �������� �������� ������ 
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                openCells(x + dx, y + dy);
            }
        }
    }
}

//������� ��� ��������� ��������� ������ ��� �������� ������ 
bool Field::openCell(int x, int y)
{

    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY ) {
        throw GameException("Invalid cell coordinates");
    }
    else if (grid[y][x].isOpen) {
        cout << "Cell already open" << endl;
        return true;
    }
    else if (grid[y][x].isMarked) {
        cout << "Cell is marked" << endl;
        return true;
    }
    else if (!openCells(x, y)) {
        printField();
        return false;
    }
    return true;
}



void Field::markCell(int x, int y) {
    // �������� �� ���������� � ������� � ��  �������� ������ 
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || grid[y][x].isOpen) {
        throw GameException("Invalid cell coordinates or cell already open!");
    }

    grid[y][x].isMarked = !grid[y][x].isMarked;
}




bool Field::checkWin() {
    bool f = true, p = true;
    // ��������� ���, ���� ��� ������ ����� ���� �������, ���� ��� ����� ��������������(�� ����� ������ ������ �� ��������������)
    for (int y = 0; y < sizeY; ++y) {        
        for (int x = 0; x < sizeX; ++x) {
            if (!(grid[y][x].bomb.Activite && grid[y][x].isMarked) || (!grid[y][x].bomb.Activite && grid[y][x].isMarked))
                p = false;
            
            if (!grid[y][x].isOpen && !grid[y][x].bomb.Activite) {
                f = false;
            }
        }
    }

    if (p || f) {
        return true;
    }
    return false;
}