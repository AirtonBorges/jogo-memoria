/*Vers�o beta desenvolvida por Thiago Felski Pereira para disciplina de Algoritmos*/
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define TAMANHO_ESPACO 3
#define OFFSET_ESPACO 2
#define MAXIMO_X 35
#define PLACAR_X 19
#define PLACAR_Y 0

using namespace std;

/**
    F L A P B I R D (M2 Algoritmos)
    - Lembrando: n�o permitido o uso de fun��es e vari�veis compostas como structs, vetores e matrizes
    - Corrigir os rastros (p�ssaro e obst�culos)
    - Implementar colis�o
    - Implementar pontua��o (mais um ponto para cada obst�culo superado)
    - Fazer 2 obst�culos simult�neos (obstaculo1 e obstaculo2)
    - Deixar a pontua��o vis�vel durante todo o jogo
    - Definir marcos para acelerar a velocidade
*/


int main()
{
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, A SEGUIR.
    //INICIO: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
    //FIM: COMANDOS PARA QUE O CURSOR N�O FIQUE PISCANDO NA TELA
    //INICIO: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    COORD coord;
    //FIM: COMANDOS PARA REPOSICIONAR O CURSOR NO IN�CIO DA TELA
    ///ALERTA: N�O MODIFICAR O TRECHO DE C�DIGO, ACIMA.


    srand(time(NULL));
    int xPassaroX = 5, xPassaroY = 10;
    int xBirdX = 5, xBirdY = 10;
    int xObstaculoX = MAXIMO_X / 2;
    int xNovoObstaculoX = 0;
    int xObstaculosY;
    int xTecla;
    int xPlacar = 0;
    int xPosicaoAberturaObstaculoY = (rand() %15) + 3;
    int xPosicaoAberturaObstaculo2Y = 0;
    int xTeclaPressionada;
    int xVelocidade = 200;

    Sleep(1000);
    cout << "-----------------------------------------------------------";
    cout << "\n\n\n\n"
            " _____ _     ____  ____  ____ ___  _   ____  _  ____  ____ \n"
            "/    // \\   /  _ \\/  __\\/  __\\\\  \\//  /  _ \\/ \\/  __\\/  _ \\\n"
            "|  __\\| |   | / \\||  \\/||  \\/| \\  /   | | //| ||  \\/|| | \\|\n"
            "| |   | |_/\\| |-|||  __/|  __/ / /    | |_\\\\| ||    /| |_/|\n"
            "\\_/   \\____/\\_/ \\|\\_/   \\_/   /_/     \\____/\\_/\\_/\\_\\\\____/\n"
            "\n"
            "Pressione enter para iniciar o jogo \n\n\n\n";
    cout << "-----------------------------------------------------------";

    cin.get();

    while (true) { //esse la�o faz o jogo rodar para sempre
        cout << "------------------ " << xPlacar << " ------------------";
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "--------------------------------------";

        if (kbhit()) {
            xTeclaPressionada=getch();
        }

        if ( xTeclaPressionada == 'w' ){
            xBirdY--;
            xTeclaPressionada = '0';
        } else {
            xBirdY++;
        }

        if(xObstaculoX <= 0) {
            xObstaculoX = MAXIMO_X;

            srand(45);
            xPosicaoAberturaObstaculoY = (rand() %15) + 3;
        }

        if(xNovoObstaculoX <= 0) {
            xNovoObstaculoX = MAXIMO_X;
            int xOffset = 0;

            if ((rand() % 2) == 1) {
                xOffset = -OFFSET_ESPACO;
            }
            else {
                xOffset = OFFSET_ESPACO;
            }
            xPosicaoAberturaObstaculo2Y = (xPosicaoAberturaObstaculoY + xOffset);
        }

        coord.X = xBirdX;    coord.Y = xBirdY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout<<char(190);
        xObstaculosY = 1;
        while (xObstaculosY < 20) {
            coord.X = PLACAR_X;
            coord.Y = PLACAR_Y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << xPlacar;

            coord.X = xObstaculoX;
            coord.Y = xObstaculosY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if(xObstaculosY < xPosicaoAberturaObstaculoY || xObstaculosY > xPosicaoAberturaObstaculoY + TAMANHO_ESPACO ){
                cout<<char(219);
            }

            coord.X = xNovoObstaculoX;
            coord.Y = xObstaculosY;

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            if(xObstaculosY < xPosicaoAberturaObstaculo2Y || xObstaculosY > xPosicaoAberturaObstaculo2Y + TAMANHO_ESPACO){
                cout<<char(219);
            }

            xObstaculosY++;
        }

        if(xBirdY < 0 || xBirdY > 20) {
            break;
        }

        if(xBirdX == xObstaculoX) {
            if(xBirdY < xPosicaoAberturaObstaculoY || xBirdY > xPosicaoAberturaObstaculoY + TAMANHO_ESPACO ) {
                break;
            }
            else {
                xPlacar++;

                if(xPlacar % 5 == 0) {
                    xVelocidade = xVelocidade *  0.90;
                }
            }
        }

        else if(xBirdX == xNovoObstaculoX) {
            if(xBirdY < xPosicaoAberturaObstaculo2Y || xBirdY > xPosicaoAberturaObstaculo2Y + TAMANHO_ESPACO ) {
                break;
            }
            else {
                xPlacar++;

                if(xPlacar % 5 == 0) {
                    xVelocidade = xVelocidade *  0.90;
                }
            }
        }


        xObstaculoX--;
        xNovoObstaculoX--;

        Sleep(xVelocidade);
        system("cls");
    }

    system("cls");
    cout << "----------------------------------------------------------";
    cout << "\n\n\n\n"
            " _____ ____  _      _____   ____  _     _____ ____ \n"
            "/  __//  _ \\/ \\__/|/  __/  /  _ \\/ \\ |\\/  __//  __\\\n"
            "| |  _| / \\|| |\\/|||  \\    | / \\|| | //|  \\  |  \\/|\n"
            "| |_//| |-||| |  |||  /_   | \\_/|| \\// |  /_ |    /\n"
            "\\____\\\\_/ \\|\\_/  \\|\\____\\  \\____/\\__/  \\____\\\\_/\\_\\\n"
            "\n"
            "Pressione Ctrl + F5 para reiniciar o jogo"
            "                                                    \n\n\n";
    cout << "----------------------------------------------------------";
    return 0;
}