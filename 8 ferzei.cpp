#include <iostream>
using namespace std;

int board[8][8];
void Board();
void showBoard();
void placeQueen(int i, int j);
void removeQueen(int i, int j);
bool checkQueen(int i);

int main()
{
    Board();
    checkQueen(0);
    cout << "Results: " << endl;
    showBoard();
    return 0;
}


void Board() // Функция для инициализации доски
{
    for (int i = 0; i < 8; i++) { // Заполнение двумерного массива нулями
        for (int j = 0; j < 8; j++) { //Ноль означает, что в данную клетку можно поставить ферзя
            board[i][j] = 0;
        }
    }
}

void showBoard() // Функция, которая выводит доску
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) { // Перебор двумерного массива (доски)
            if (board[i][j] == -1) { 
                cout << "Q "; // Вывести в данную клетку ферзя
            }
            if (board[i][j] == 0) {
                cout << ". "; // Вывести в данную клетку ферзя
            }
            else {
                cout << "X "; // Вывести пустую клетку
            }
        }
        cout << endl;
    }
}

void placeQueen(int i, int j) // Размещение ферзя на доске, отметка атакованных клеток 
{
    for (int x = 0; x < 8; ++x) {
        ++board[x][j]; // Увеличение значения клетки (Т.к. изначально значение клетки = 0,
        ++board[i][x]; // если значение клетки больше 0, то клетка будет атакована другим ферзем)

        int d;
        d = j - i + x; // Нахождение координат диагонали
        if (d >= 0 && d < 8) {
            ++board[x][d];
        }

        d = j + i - x; // Нахождение координат второй диагонали
        if (d >= 0 && d < 8) {
            ++board[x][d];
        }
    }
    board[i][j] = -1; // Устанавливаем ферзя (Такое значение клетки означает ферзя )
    showBoard(); // Вывод доски
    cout << endl << endl;
}

void removeQueen(int i, int j) // Удаление ферзя
{
    for (int x = 0; x < 8; ++x) {
        --board[x][j];
        --board[i][x];

        int d;
        d = j - i + x; // Нахождение координат диагонали
        if (d >= 0 && d < 8) {
            --board[x][d];
        }

        d = j + i - x; // Нахождение координат второй диагонали
        if (d >= 0 && d < 8) {
            --board[x][d];
        }
    }
    board[i][j] = 0; // Удаляем ферзя
}

bool checkQueen(int i)
{
    bool result = false;

    for (int j = 0; j < 8; ++j) { // Проход по строке 
        if (board[i][j] == 0) { // Если значение клетки = 0 (Эту клетку нельзя срубить другим ферзем)
            placeQueen(i, j); // Размещаем ферзя и отмечаем атакованные клетки

            if (i == 7) { // Если при проверке дошли до конца доски (Поставили в последнюю строку)
                result = true; // Комбинация найдена
            }
            else if (!(result = checkQueen(i + 1))) { // Если нет места в следующей строке
                removeQueen(i, j); // удалить ферзя и продолжить поиск со следущей клетки
            }
        }
        if (result) break; // Если result = True - ферзь в поставлен
    }
    return result;
}