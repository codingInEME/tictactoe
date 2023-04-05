#include <iostream>
#include <windows.h>

using namespace std;

void ticTacToe();
void displayBoard(char[3][3], char*);
bool hasWon(char board[3][3], char*, int&);

bool isValid(int, int, int);
void textColor(int);

enum colors {
    black = 0, red = 4, grey = 8, light_red = 12,
    blue = 1, purple = 5, light_blue = 9, light_purple = 13,
    green = 2, yellow = 6, light_green = 10, light_yellow = 14,
    aqua = 3, white = 7, light_aqua = 11, bright_white = 15
};

int main()
{
    int select;
    while (true) {
        ticTacToe();
        cout << "Enter -1 to close the game: ";
        cin >> select;

        if (cin.fail())
        {
            cin.ignore(100, '\n');
            cin.clear();
        }

        system("CLS");
        if (select == -1)
            break;
    }
    system("pause");
    return 0;
}

void ticTacToe()
{
    char board[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}
    };
    char icons[2] = { 'O', 'X' };

    bool win = false;

    int player = 0;
    int select = 0;
    int icon;

    while (player < 9)
    {
        icon = ++player % 2;
        int row, column;

        while (true)
        {
            displayBoard(board, icons);

            cout << "Player " << icons[icon] << " turn: ";
            cin >> select;

            row = (select - 1) / 3;
            column = (select - 1) % 3;

            system("CLS");

            if (isValid(select, 0, 10))
            {
                if (board[row][column] == select + 48)
                    break;
            }
        }

        board[row][column] = icons[icon]; //board[row][column] = icon[player 0 or 1]

        // Checking
        if (hasWon(board, icons, icon))
        {
            win = true;
            break;
        }
    } // while()

    displayBoard(board, icons);

    if (win) {
        cout << "Player " << icons[icon] << " has won!\n";
    }
    else
        cout << "Round is a draw!\n";
}

void displayBoard(char board[3][3], char* icons)
{
    for (int i = 0; i < 3; i++)
    {
        cout << "[ ";
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == icons[0])
                textColor(yellow);
            else if (board[i][j] == icons[1])
                textColor(light_red);

            cout << board[i][j] << " ";
            textColor(white);
        }
        cout << " ]\n";
    }
}

bool hasWon(char board[3][3], char* icons, int& turn)
{
    int diagonal = 0, diagonal_2 = 0;
    int horizontal, vertical;
    for (int i = 0; i < 3; i++)
    {
        horizontal = 0; vertical = 0;
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == icons[turn])
                vertical++;

            if (board[j][i] == icons[turn])
                horizontal++;
        }

        if (vertical == 3 || horizontal == 3) {
            return true;
            break;
        }

        if (board[i][i] == icons[turn])
            diagonal++;

        if (board[i][2 - i] == icons[turn])
            diagonal_2++;
    }

    if (diagonal == 3 || diagonal_2 == 3) {
        return true;
    }

    return false;
}

bool isValid(int input, int lowLimit, int highLimit)
{
    if (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        return false;
    }

    if (input < lowLimit || input > highLimit)
        return false;

    return true;
}

void textColor(int x)
{
    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, x);
}