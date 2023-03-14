#include "header.h"
#include <iostream>
#include <conio.h>
#include <ctime>
using namespace std;
Food::Food(Snake* ptr) {
    Snakeptr = ptr;

}


bool Snake::isthereaSnake(int x, int y) {
    for (int i = 0; i < body.size(); i++) {

        if (body[i].X == x && body[i].Y == y) {
            return true;
        }
    }

    return false;

}

void Food::make_food()
{   int pos_X= (rand() % (SIZE_X - 3)) + 1;
    int pos_Y= (rand() % (SIZE_Y - 3)) + 1;
    
    while (( * Snakeptr).isthereaSnake(pos_X,pos_Y)) {
         pos_X = (rand() % (SIZE_X - 3)) + 1;
         pos_Y = (rand() % (SIZE_Y - 3)) + 1;
    }
    pos.X = pos_X;
    pos.Y = pos_Y;
    
}

Case Food::return_position() { return pos; }


Snake::Snake(Case pos, int snake_speed)
{
    position = pos;
    speed = snake_speed;
    len = 1;
    orientation = 'o';
    body.push_back(pos);
}

void Snake::direction(char dir) { orientation = dir; }
void Snake::grow() { len++; }
Case Snake::return_position() { return position; }

vector<Case> Snake::return_body() { return body; }

void Snake::move_snake()
{
    switch (orientation)
    {
    case 'N': 
        position.Y -= speed; 
        break;
    case 'S': 
        position.Y += speed; 
        break;
    case 'W': 
        position.X -= speed; 
        break;
    case 'E': 
        position.X += speed; 
        break;
    }

    body.push_back(position);
    if (body.size() > len) { 
        body.erase(body.begin()); 
    }
}

bool Snake::hit()
{
    if (position.X < 1 || position.X > SIZE_X - 2 || position.Y < 1 || position.Y > SIZE_Y - 2)
    {
        return true;
    }
    for (int i = 0; i < len - 1; i++)
    {
        if (position.X == body[i].X && position.Y == body[i].Y)
        {
            return true;
        }
    }
    {
        return false;
    }
}

bool Snake::fed(Case food)
{
    if (position.X == food.X && position.Y == food.Y) {

        return true;
    }
    return false;
}

void run(Snake* snk, Food* fd) {

    Snake* snek = snk;
    Food* theFood = fd;
    bool game_over = false;
    while (!game_over)
    {
        display_board(snek, theFood);

        if (_kbhit())
        {
            switch (_getch())
            {
            case 'z':
                (*snk).direction('N');
                break;
            case 'q':
                (*snk).direction('W');
                break;
            case 's':
                (*snk).direction('S');
                break;
            case 'd':
                (*snk).direction('E');
                break;
            }
        }

        if ((*snk).hit()) {

            game_over = true;
        }

        if ((*snk).fed((*theFood).return_position()))
        {
            (*theFood).make_food();

            (*snk).grow();

        }

        (*snk).move_snake();

        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 0 });//magie noire
    }

}

void display_board(Snake* snk, Food* fd)
{
    Snake* snek = snk;
    Food* theFood = fd;

    Case snake_position = (*snek).return_position();

    Case food_position = (*theFood).return_position();



    vector<Case> snake_body = (*snek).return_body();



    for (int i = 0; i < SIZE_Y; i++)
    {
        cout << "\tX";
        for (int j = 0; j < SIZE_X - 2; j++)
        {
            if (i == 0 || i == SIZE_Y - 1) {
                cout << 'X';
            }
            else if (i == snake_position.Y && j + 1 == snake_position.X) {
                cout << 'S';
            }
            else if (i == food_position.Y && j + 1 == food_position.X) {
                cout << 'F';
            }

            else
            {
                bool belongs_to_snake = false;
                for (int k = 0; k < snake_body.size() - 1; k++)
                {
                    if (i == snake_body[k].Y && j + 1 == snake_body[k].X)
                    {
                        cout << 's';
                        belongs_to_snake = true;
                        break;
                    }
                }

                if (!belongs_to_snake) cout << ' ';
            }
        }
        //cout << "B\n";
        cout << "X" << endl;
    }
}
