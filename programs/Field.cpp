#include <iostream>
#include <vector>
#include "Field.h"
#include "GameExeption.h"
using namespace std;



Field::Field(int x, int y, int bombs) : sizeX(x), sizeY(y), numBombs(bombs) {
    // Инициализируем класс и меняем размеры поля под заданные 
    grid.resize(sizeY, vector<Cell>(sizeX));    
}

void Field::bombs(int fx, int fy)
{   
    // Проверяем что стартова точка внутри массива 
    if (fx < 0 || fx >= sizeX || fy < 0 || fy >= sizeY) {
        throw GameException("Invalid cell coordinates");
    }
    
    // Обявляем функцию рандом по нынешнему времени 
    srand(time(NULL));

    //Рандомно распологаем бомбы
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
    // Выводим первую строку с цифрами для удобной игры
    cout << "   ";
    for (int x = 0; x < sizeX; ++x) {
        cout << x + 1 << " ";
    }
    cout << endl;

    // Выводим пле и цифры справа
    for (int y = 0; y < sizeY; ++y) {
        // Проверка для корректного вывода цифр справа от поля 
        if (y+1>=10)
            cout << y + 1 << " ";
        else 
            cout << y + 1 << "  ";

        // Вывод самого поля 
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
    
    //Проверка на то что мы все еще в массиве и на то что клетка уже открыта
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || grid[y][x].isOpen) {
        return true;
    }

    //Открываем клетку
    grid[y][x].isOpen = true;

    //Проверка на бомбу
    if (grid[y][x].bomb.Activite) {
        cout << "Game Over! You hit a bomb!" << endl;
        
        return false;
    }

    // Подсчет бомб вокруг клетки 
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
        // Если клетка пустая, рекурсивно вызываем открытие клеток 
        for (int dy = -1; dy <= 1; ++dy) {
            for (int dx = -1; dx <= 1; ++dx) {
                openCells(x + dx, y + dy);
            }
        }
    }
}

//Функция для обработки введенных данных для открытия клетки 
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
    // Проверка на нахождение в массиве и на  открытую клетку 
    if (x < 0 || x >= sizeX || y < 0 || y >= sizeY || grid[y][x].isOpen) {
        throw GameException("Invalid cell coordinates or cell already open!");
    }

    grid[y][x].isMarked = !grid[y][x].isMarked;
}




bool Field::checkWin() {
    bool f = true, p = true;
    // Проверяем что, либо все клетки кроме бомб открыты, либо все бомбы промаркерованы(ни ондна пустая клетка не промаркерована)
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