#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int main()
{
    HANDLE xOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO xCursorInfo;
    GetConsoleCursorInfo(xOut, &xCursorInfo);
    xCursorInfo.bVisible = false;
    SetConsoleCursorInfo(xOut, &xCursorInfo);
    COORD coord;

    int xPosicaoX = 5, xPosicaoY = 10;
    int xPlacar = 0;
    int xTeclaPressionada;
    int xVelocidade = 10;

    cin.get();

    while (true) {
        cout << "-----------------------";
        cout << "\n| 1 | | 2 | | 3 | | 4 |";
        cout << "\n| 2 | | 5 | | 6 | | 7 |";
        cout << "\n| 2 | | 4 | | 5 | | 6 |";
        cout << "\n| 2 | | 4 | | 5 | | 6 |";
        cout << "\n-----------------------";

        if (kbhit()) {
            xTeclaPressionada=getch();
        }

        if (xTeclaPressionada == 'w'){
            xPosicaoY--;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 's'){
            xPosicaoY++;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 'a'){
            xPosicaoX--;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 'd'){
            xPosicaoX++;
            xTeclaPressionada = '0';
        }

        coord.X = (short)xPosicaoX; coord.Y = (short)xPosicaoY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout<<char('>');

        if(xPosicaoY < 0 || xPosicaoY > 20) {
            break;
        }

        Sleep(xVelocidade);
        system("cls");
    }

    system("cls");
    cout << "----------------------------------------------------------";
    cout << " Perdeste. ";
    cout << "----------------------------------------------------------";
    return 0;
}