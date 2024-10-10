// Onur Bagirov Exam Projcet

#include <conio.h>
#include <iostream>

//Varibles

//===================================================

using namespace std;

#pragma warning(disable: 4996)

string player_one;
string player_two;


int control;


int map_one[10][10] = { 0 };
int map_two[10][10] = { 0 };

int enter_y;
int enter_x;

bool player_one_turn = true;
bool player_two_turn = false;

bool game_run = true;

int player_one_ship = 0;
int player_two_ship = 0;

int ship_sizes[] = { 2, 3, 4, 5, 6 };

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

//=======================================================

// Functions

//=======================================================

void reset_Map(int map[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            map[i][j] = 0;
        }
    }
}


void create_Map(int map[10][10])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (map[i][j] == 0)
            {
                cout << "\033[37mO\033[0m" << " ";
            }
            else if (map[i][j] == -1)
            {
                cout << "\033[31mH\033[0m" << " ";
            }
            else if (map[i][j] > 1)
            {
                cout << "\033[36mX\033[0m" << " ";
            }
        }
        cout << endl;
    }
}

bool is_valid_position(int map[10][10], int ship[])
{
    int x = ship[0];
    int y = ship[1];
    int direction = ship[2];
    int size = ship[3];


    for (int i = 0; i < size; i++)
    {
        if (x < 0 || x > 9 || y < 0 || y > 9 || map[x][y] != 0)
        {
            return false;
        }

        for (int dx = -1; dx <= 1; dx++)
        {
            for (int dy = -1; dy <= 1; dy++)
            {
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10 && map[nx][ny] != 0)
                {
                    return false; 
                }
            }
        }

        if (direction == 1)
        {
            y++;
        }
        else if (direction == 2)
        {
            x++;
        }
    }
    return true;
}

void create_Ship(int map[10][10], int ship[])
{
    cout << "\n\n";

    do {
        cout << "Enter x coordinate (0 - 9): ";
        cin >> ship[0];
    } while (ship[0] >= 0 && ship[0] >= 9);

    do {
        cout << "Enter y coordinate (0 - 9): ";
        cin >> ship[1];
    } while (ship[1] >= 0 && ship[1] >= 9);

    do {
        cout << "Enter choice (1 - row, 2 - col): ";
        cin >> ship[2];
    } while (ship[2] != 1 && ship[2] != 2);

    while (!is_valid_position(map, ship))
    {
        cout << "\n\n";
        cout << "\033[31mInvalid position ! Plesase try agein !\033[0m ";
        create_Ship(map, ship);
    }
}

void ship_include_map(int map[10][10], int* ship)
{
    int x = ship[0];
    int y = ship[1];
    int row_or_col = ship[2];
    int size_ship = ship[3];

    for (int i = 0; i < size_ship; i++)
    {
        map[x][y] = size_ship;
        if (row_or_col == 1)
        {
            y++;
        }

        else if (row_or_col == 2)
        {
            x++;
        }
    }
}

bool start_Battleship_game(const string& player_name, int map[10][10], int& hit_count)
{
    cout << "\n\n";
    cout << player_name << " play your turn !";
    cout << "\n\n";

    do {
        cout << "Enter x coordinate : ";
        cin >> enter_x;
    } while (enter_x < 0 || enter_x > 9);

    do {
        cout << "Enter y coordinate : ";
        cin >> enter_y;
    } while (enter_y < 0 || enter_y > 9);

    int hit_ship_size = map[enter_x][enter_y];

    if (hit_ship_size > 1)
    {
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (map[i][j] == hit_ship_size)
                    map[i][j] = -1;
            }
        }

        hit_count++;

        cout << "\n\n";
        cout << "\033[32mHit !\033[0m";
        cout << "\n\n";
        create_Map(map);
        cout << "\n\n";

        return true;
    }
    else
    {
        cout << "\n\n";
        cout << "\033[31mMISS ! Wrong cootdinate ! \033[0m";
        cout << "\n\n";

        return false;
    }
}

bool check_Game(int hit_count)
{
    return hit_count >= 5;
}

void Information_desk()
{
    system("cls");
    cout << "\t\tBattle Ship";
    cout << "\n\n\n";
    cout << "\033[33mFirst you need to place your ships on the map.";
    cout << endl;
    cout << "To place, you need to enter the x and y coordinates between 0 and 9.";
    cout << endl;
    cout << "Then choose row or column (1 for row, 2 for column).";
    cout << endl;
    cout << "The aim of the game is to sink all 5 of your opponent's ships.";
    cout << endl;
    cout << "If you sink 5 ships, you win!\033[0m\n";
}

void start_game()
{
    system("cls");

    cout << "\n\n";
    cout << "\t\t Start Game !";
    cout << "\n\n";

    cout << "Please enter player one's name : ";
    cin >> player_one;

    cout << "\n\n\n";

    cout << player_one << "'s unfilled map ! ";

    cout << "\n\n";
    create_Map(map_one);
    cout << "\n\n";

    for (int i = 1; i <= 5; i++)
    {
        int ship[4] = { 0, 0, 0, i + 1 };
        create_Ship(map_one, ship);
        ship_include_map(map_one, ship);

        if (i < 5)
        {
            system("cls");
            cout << player_one << "'s " << i << " ship";

            cout << "\n\n";
            create_Map(map_one);
            cout << "\n\n";
        }
    }

    system("cls");
    cout << "Please enter player two's name : ";
    cin >> player_two;

    cout << "\n\n\n";

    cout << player_two << "'s unfilled map !";

    cout << "\n\n";
    create_Map(map_two);
    cout << "\n\n\n";

    for (int i = 1; i <= 5; i++)
    {
        int ship[4] = { 0, 0, 0, i + 1 };
        create_Ship(map_two, ship);
        ship_include_map(map_two, ship);

        if (i < 5)
        {
            system("cls");
            cout << player_two << "'s " << i << " ship";

            cout << "\n\n";
            create_Map(map_two);
            cout << "\n\n";
        }
    }

    system("cls");

    while (game_run)
    {
        if (player_one_turn)
        {
            start_Battleship_game(player_one, map_two, player_one_ship);
            if (check_Game(player_one_ship))
            {
                system("cls");

                cout << "\t\tRseult !";
                cout << "\n\n\n";
                cout << player_two << "'s Map !";
                cout << "\n\n";
                create_Map(map_two);
                cout << "\n\n\n";
                cout << player_one << "\033[32m IS WINNER ! \033[0m";
                cout << "\n";
                cout << player_two << "\033[31m IS LOST GAME ! \033[0m";

                break;
            }
            player_one_turn = false;
            player_two_turn = true;
        }

        else if (player_two_turn)
        {
            start_Battleship_game(player_two, map_one, player_two_ship);
            if (check_Game(player_two_ship))
            {
                     system("cls");

                cout << "\t\tRseult !";
                cout << "\n\n\n";
                cout << player_one << "'s Map !";
                cout << "\n\n";
                create_Map(map_one);
                cout << "\n\n\n";
                cout << player_two << "\033[32m IS WINNER ! \033[0m";
                cout << "\n";
                cout << player_one << "\033[31m IS LOST GAME ! \033[0m";
                break;
            }
            player_one_turn = true;
            player_two_turn = false;
        }
    }
}

//=======================================================

// Main

//=======================================================

int main() {
    cout << "\tWelcome to Battleship Game !";
    cout << "\n\n";
    cout << "\033[32m - Start Game: Press UP button\n";
    cout << "\033[33m - Information Desk: Press LEFT button\n";
    cout << "\033[31m - Exit Game: Press DOWN button\033[0m\n";

    while (1) {
        control = getch();

        switch (control)
        {
        case KEY_UP:
            start_game();
            break;

        case KEY_DOWN:
            cout << "Finish game !";
            exit(0);

        case KEY_LEFT:
            Information_desk();
            break;
        }
    }
}

//=======================================================
