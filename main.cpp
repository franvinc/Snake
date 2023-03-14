#include <iostream>
#include <conio.h>
#include <ctime>

#include "header.h"

#define SIZE_X 50
#define SIZE_Y 25

#define START_X 10
#define START_Y 10

using namespace std;

Snake snake({ START_X, START_Y }, 1);
Food food =Food(&snake);//on génère un seul objet food et on recalcule la position à chaque nouvelle génération








int main()
{
    
    srand(time(NULL));

    food.make_food();
    
   
    run(&snake, &food);
}
