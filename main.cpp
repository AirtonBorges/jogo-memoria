#include <iostream>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <random>
#include <chrono>

#define DIMENSAO 4
#define LOCAL_RESULTADO_Y 0
#define LOCAL_RESULTADO_X 5

#define LOCAL_CONTINUAR_Y 7
#define LOCAL_CONTINUAR_X 0

#define LOCAL_CHANCES_Y 0
#define LOCAL_CHANCES_X 5

using namespace std;

int main()
{
    HANDLE xOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO xCursorInfo;
    GetConsoleCursorInfo(xOut, &xCursorInfo);
    xCursorInfo.bVisible = false;
    SetConsoleCursorInfo(xOut, &xCursorInfo);
    COORD coord;

    int xPosicaoX = 1, xPosicaoY = 1;
    int xPlacar = 0;
    int xTeclaPressionada;
    int xVelocidade = 10;
    int xParesRestantes = 8;
    int xChances = 24;

    // Cria matriz principal
    int xMatrizPrincipal[DIMENSAO][DIMENSAO];
    int xContador = 0;
    for (int i = 0; i < DIMENSAO; i++) {
        for (int i2 = 0; i2 < DIMENSAO; i2++) {
            xContador++;
            xMatrizPrincipal[i2][i] = xContador;
            if (xContador == 8) {
                xContador = 0;
            }
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(&xMatrizPrincipal[0][0], &xMatrizPrincipal[DIMENSAO - 1][DIMENSAO - 1], std::default_random_engine(seed));

    // Cria matriz jogo
    char xMatrizJogo[DIMENSAO][DIMENSAO];
    for (int i = 0; i < DIMENSAO; i++) {
        for (int i2 = 0; i2 < DIMENSAO; i2++) {
            xMatrizJogo[i][i2] = '*';
        }
    }

    cin.get();

    int xPrimeiraPeca = -1;
    int xPrimeiraPecaX = -1, xPrimeiraPecaY = -1;

    int xSegundaPeca = -1;
    int xSegundaPecaX = -1, xSegundaPecaY = -1;

    while (true) {
        cout << "-----------------------";
        cout << "\n| " << xMatrizJogo[0][0] << " | | " << xMatrizJogo[0][1] << " | | " << xMatrizJogo[0][2] << " | | " << xMatrizJogo[0][3] << " |";
        cout << "\n| " << xMatrizJogo[1][0] << " | | " << xMatrizJogo[1][1] << " | | " << xMatrizJogo[1][2] << " | | " << xMatrizJogo[1][3] << " |";
        cout << "\n| " << xMatrizJogo[2][0] << " | | " << xMatrizJogo[2][1] << " | | " << xMatrizJogo[2][2] << " | | " << xMatrizJogo[2][3] << " |";
        cout << "\n| " << xMatrizJogo[3][0] << " | | " << xMatrizJogo[3][1] << " | | " << xMatrizJogo[3][2] << " | | " << xMatrizJogo[3][3] << " |";
        cout << "\n-----------------------";

        // Input
        if (kbhit()) {
            xTeclaPressionada=getch();
        }

        // Movimentacao
        if (xTeclaPressionada == 'w'){
            xPosicaoY--;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 's'){
            xPosicaoY++;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 'a'){
            xPosicaoX-=6;
            xTeclaPressionada = '0';
        }
        if (xTeclaPressionada == 'd'){
            xPosicaoX+=6;
            xTeclaPressionada = '0';
        }

        if (xPosicaoY < 1) {
            xPosicaoY = 1;
        }

        if (xPosicaoY > 4) {
            xPosicaoY = 4;
        }

        if (xPosicaoX > 19) {
            xPosicaoX = 19;
        }

        if (xPosicaoX < 1) {
            xPosicaoX = 1;
        }

        // Seleção da peça
        if (xTeclaPressionada == ' '){
            int xPosicaoMatrizX = (xPosicaoX - 1) / 6;
            int xPosicaoMatrizY = xPosicaoY - 1;

            if (xPrimeiraPeca == -1) {
                // TODO: Trocar por matriz gabarito
                xPrimeiraPeca = xMatrizPrincipal[xPosicaoMatrizY][xPosicaoMatrizX];
                xPrimeiraPecaX = xPosicaoX + 1;
                xPrimeiraPecaY = xPosicaoY;
            }
            if (xPrimeiraPeca != -1 && xSegundaPeca == -1
                && (xPrimeiraPecaX != xPosicaoX + 1
                    || xPrimeiraPecaY != xPosicaoY)
                    ) {
                // TODO: Trocar por matriz gabarito
                xSegundaPeca = xMatrizPrincipal[xPosicaoMatrizY][xPosicaoMatrizX];
                xSegundaPecaX = xPosicaoX + 1;
                xSegundaPecaY = xPosicaoY;
            }
            xTeclaPressionada = '0';
        }

        // Desenhar cursor
        coord.X = (short)xPosicaoX; coord.Y = (short)xPosicaoY;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout<< char('>');

        // Desenhar peças selecionadas
        if (xPrimeiraPeca != -1) {
            coord.X = (short)xPrimeiraPecaX; coord.Y = (short)xPrimeiraPecaY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << to_string(xPrimeiraPeca)[0];
        }
        if (xSegundaPeca != -1) {
            coord.X = (short)xSegundaPecaX; coord.Y = (short)xSegundaPecaY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            cout << to_string(xSegundaPeca)[0];
        }

        // Testa se jogador fez ponto
        if (xPrimeiraPeca != -1 && xSegundaPeca != -1) {
            coord.X = (short)LOCAL_RESULTADO_X; coord.Y = (short)LOCAL_RESULTADO_Y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

            if (xPrimeiraPeca == xSegundaPeca) {
                xMatrizJogo[xPrimeiraPecaY - 1][(xPrimeiraPecaX - 1) / 6] = to_string(xPrimeiraPeca)[0];
                xMatrizJogo[xSegundaPecaY - 1][(xSegundaPecaX - 1) / 6] = to_string(xSegundaPeca)[0];

                cout << " JOGADA OK! ";
                xParesRestantes--;
            }
            else {
                cout << " JOGADA NOK! ";
                xChances--;
            }

            if (xChances == 0 || xParesRestantes == 0) {
                break;
            }

            xPrimeiraPecaY = -1;
            xPrimeiraPecaX = -1;
            xPrimeiraPeca = -1;

            xSegundaPecaY = -1;
            xSegundaPecaX = -1;
            xSegundaPeca = -1;

            coord.X = LOCAL_CONTINUAR_X; coord.Y = LOCAL_CONTINUAR_Y;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
            system("pause");
        }

        // Mostrar quantidade de chances
        coord.X = LOCAL_CHANCES_X; coord.Y = LOCAL_CHANCES_Y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        cout << " Chances: " << xChances << " ";

        Sleep(xVelocidade);
        system("cls");
    }

    // TODO: Mensagen melhores
    system("cls");
    if (xParesRestantes != 0) {
        cout << "";
        cout << " \n"
                "  ___             _            \n"
                " |  __ \\           | |           \n"
                " | |_) |_ _ _ _| | _ _   _ \n"
                " |  _/ _ \\ '__/ _` |/ _ \\ | | |\n"
                " | |  |  _/ | | (| |  _/ || |\n"
                " ||   \\_||  \\_,|\\__|\\,|\n"
                "                                 \n"
                "                                  ";
        cout << "";
    }
    else {
        cout << "";
        cout << " \n"
                "   ___             _                 \n"
                "  / __|           | |                \n"
                " | |  _  _ _ _ _ | |_   _  _   _ \n"
                " | | |_ |/ ` | ' \\| '_ \\ / _ \\| | | |\n"
                " | |_| | (| | | | | | | | () | || |\n"
                "  \\__|\\,|| ||| ||\\__/ \\,|\n"
                "                                       \n"
                "                                       . ";
        cout << "";
    }

    return 0;
}