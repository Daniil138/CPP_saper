#include "Start.h"
#include <iostream>
#include "Field.h"
#include "GameExeption.h"
using namespace std;

Start::Start()
{
}

void Start::star_play(){
    // Ввод размеров поля и кол-во мин
    int sizeX, sizeY, numBombs;
    cout << "Enter field size (X Y): ";
    cin >> sizeX >> sizeY;
    cout << "Enter number of bombs: ";
    cin >> numBombs;

    // Создаем поле 
    Field field(sizeX, sizeY, numBombs);
    field.printField();

    // Делем первый ход  
    int fx, fy;

    cout << "Enter cell coordinates for first open  (X Y): ";
    cin >> fx >> fy;

    fx -= 1;
    fy -= 1;

    // Расставляем бомбы передаавая туда первый ход чтоб не поставить туда мину 
    field.bombs(fx, fy);

    //Открывавем первую клетку 
    field.openCell(fx, fy);
    field.printField();

    // Оюъявляем кординаты и действие
    int x, y;
    char action;

    while (true) {

        
       
        
        cout << "Enter cell coordinates and action or markers(X Y A/M): ";
        cin >> x >> y >> action;

        // Чтобы вводить кординаты не начиная от нуля
        x -= 1;
        y -= 1;

        
        //Проверка действия 
        if (action == 'A') {
            if (!field.openCell(x, y))
                break;
        }

        else if (action == 'M') {
            field.markCell(x, y);
        }
        else {
            cout << "Invalid move" << endl;
        }

        
        field.printField();

        //Проверка на выигрышь
        if (field.checkWin()) {
            cout << "Congratulations! You won!" << endl;
            break;
        }
    }


}
