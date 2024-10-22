#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Create(int** P, const int rowCount, const int colCount, const int Low, const int High, int i, int j);
void Print(int** P, const int rowCount, const int colCount, int i, int j);
void Sort(int** P, const int rowCount, const int colCount, int i0, int i1);
void Change(int** P, const int col1, const int col2, const int rowCount, int j);
void Calc(int** P, const int rowCount, const int colCount, int& S, int& k, int i, int j);

int main() {
    srand((unsigned)time(NULL));
    int Low = -21;
    int High = 24;
    int rowCount = 9;
    int colCount = 6;
    int** P = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        P[i] = new int[colCount];

    Create(P, rowCount, colCount, Low, High, 0, 0);
    Print(P, rowCount, colCount, 0, 0);

 
    Sort(P, rowCount, colCount, 0, 0);
    Print(P, rowCount, colCount, 0, 0);

    int S = 0;
    int k = 0;
    Calc(P, rowCount, colCount, S, k, 0, 0);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    Print(P, rowCount, colCount, 0, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] P[i];
    delete[] P;

    return 0;
}

// Функція для формування матриці випадковими значеннями в діапазоні
void Create(int** P, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
    P[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(P, rowCount, colCount, Low, High, i, j + 1);
    else if (i < rowCount - 1)
        Create(P, rowCount, colCount, Low, High, i + 1, 0);
}

// Функція для виведення матриці
void Print(int** P, const int rowCount, const int colCount, int i, int j) {
    cout << setw(4) << P[i][j];
    if (j < colCount - 1)
        Print(P, rowCount, colCount, i, j + 1);
    else if (i < rowCount - 1) {
        cout << endl;
        Print(P, rowCount, colCount, i + 1, 0);
    }
    else
        cout << endl << endl;
}

// Функція сортування стовпців за спаданням
void Sort(int** P, const int rowCount, const int colCount, int i0, int i1) {
    if (i0 >= colCount - 1)
        return;

    if (i1 < colCount - i0 - 1) {
        if ((P[0][i1] < P[0][i1 + 1]) ||
            (P[0][i1] == P[0][i1 + 1] && P[1][i1] < P[1][i1 + 1]) ||
            (P[0][i1] == P[0][i1 + 1] && P[1][i1] == P[1][i1 + 1] && P[2][i1] > P[2][i1 + 1])) {
            Change(P, i1, i1 + 1, rowCount, 0);
        }
        Sort(P, rowCount, colCount, i0, i1 + 1);
    }
    else {
        Sort(P, rowCount, colCount, i0 + 1, 0);
    }
}

// Функція для перестановки стовпців
void Change(int** P, const int col1, const int col2, const int rowCount, int j = 0) {
    int tmp;
    if (j < rowCount) {
        tmp = P[j][col1];
        P[j][col1] = P[j][col2];
        P[j][col2] = tmp;
        Change(P, col1, col2, rowCount, j + 1);
    }
    return;
}

// Функція для підрахунку суми та кількості елементів, кратних 3, та їх заміни на нулі
void Calc(int** P, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0) {
    if (i >= rowCount)
        return;

    if (j < colCount) {
        if (P[i][j] % 3 == 0 && !(P[i][j] < 0)) {
            S += P[i][j];
            k++;
            P[i][j] = 0;
        }
        Calc(P, rowCount, colCount, S, k, i, j + 1);
    }
    else {
        Calc(P, rowCount, colCount, S, k, i + 1, 0);
    }
}
