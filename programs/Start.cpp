#include "Start.h"
#include <iostream>
#include "Field.h"
#include "GameExeption.h"
using namespace std;

Start::Start()
{
}

void Start::star_play(){
    // ���� �������� ���� � ���-�� ���
    int sizeX, sizeY, numBombs;
    cout << "Enter field size (X Y): ";
    cin >> sizeX >> sizeY;
    cout << "Enter number of bombs: ";
    cin >> numBombs;

    // ������� ���� 
    Field field(sizeX, sizeY, numBombs);
    field.printField();

    // ����� ������ ���  
    int fx, fy;

    cout << "Enter cell coordinates for first open  (X Y): ";
    cin >> fx >> fy;

    fx -= 1;
    fy -= 1;

    // ����������� ����� ���������� ���� ������ ��� ���� �� ��������� ���� ���� 
    field.bombs(fx, fy);

    //���������� ������ ������ 
    field.openCell(fx, fy);
    field.printField();

    // ��������� ��������� � ��������
    int x, y;
    char action;

    while (true) {

        
       
        
        cout << "Enter cell coordinates and action or markers(X Y A/M): ";
        cin >> x >> y >> action;

        // ����� ������� ��������� �� ������� �� ����
        x -= 1;
        y -= 1;

        
        //�������� �������� 
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

        //�������� �� ��������
        if (field.checkWin()) {
            cout << "Congratulations! You won!" << endl;
            break;
        }
    }


}
