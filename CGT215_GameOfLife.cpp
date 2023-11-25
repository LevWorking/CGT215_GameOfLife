// CGT215_GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <random>

using namespace std;
using namespace sf;

//Set the dimensions of the grid.
const int gridX = 10;
const int gridY = 10;

int currentStep[gridX][gridY];
int nextStep[gridX][gridY];


//Initialize the arrays. 
void initialize()
{
    for (int x = 0; x < gridX; x++) 
    {
        for (int y = 0; y < gridY; y++)
        {
            currentStep[x][y] = 0;
            nextStep[x][y] = 0;
        }
    }
}

//Had to get this from StackOverflow. 
//Used for the procedural generator. Might replace later. 
bool generateBool() 
{
    int g = std::rand();
    return (g % 2); // 1 is converted to true and 0 as false

}

//Randomize the grid of the current array.
void randomizeGrid() 
{
    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (generateBool()) { currentStep[x][y] = 0; }
            else { currentStep[x][y] = 1; }
        }
    }
}

//Consulting the currentArray, construct the next step in the nextStep array, then reassign that into the current state.
void simulateStep() {}

void drawGrid() {} 

int main()
{
    
    RenderWindow window(VideoMode(800, 600), "Game of Life");
    initialize();
    randomizeGrid();

    //do { simulateStep(); drawGrid(); } while (true);
}