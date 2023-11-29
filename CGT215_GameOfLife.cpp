// CGT215_GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

using namespace std;
using namespace sf;

//Set the dimensions of the grid.
const int gridX = 25;
const int gridY = 20;
const int buffer = 100;


RenderWindow window(VideoMode(800, 600), "Game of Life");
int cellSize = (window.getSize().x - buffer) / max(gridX, gridY);
int border = 3;
RectangleShape cell[gridX][gridY];

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

            cell[x][y].setSize(Vector2f(cellSize - border, cellSize - border));
            cell[x][y].setFillColor(Color(255, 255, 255));
            cell[x][y].setPosition(Vector2f(cellSize * x, cellSize * y));
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
void simulateStep() 
{
    int alive = 0;

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (x > 0) {
                if (y > 0) 
                {
                    if (currentStep[x - 1][y - 1] == 1) { alive++; }
                }

                if (currentStep[x - 1][y] == 1) { alive++; }

                if (y < gridY) 
                {
                    if (currentStep[x - 1][y+1] == 1) { alive++; }
                }
            }

            if (y > 0) 
            {
                if(x < gridX)
                { 
                    if (currentStep[x + 1][y - 1] == 1) { alive++; } 
                }

                if (currentStep[x][y - 1] == 1) { alive++; }
                
            }

            if (x < gridX) 
            {
                if (currentStep[x + 1][y] == 1) { alive++; }
                
                if(y < gridY)
                {
                    if (currentStep[x + 1][y + 1] == 1) { alive++; }
                }
            }

            if (y < gridY) 
            {
                if (currentStep[x][y + 1] == 1) { alive++; }
            }

        }
    }
}

void drawGrid() 
{
    window.clear();

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            window.draw(cell[x][y]);
        }
    }

    
} 

int main()
{
   
    initialize();
    randomizeGrid();

    do { 
        simulateStep(); 
        drawGrid();
        window.display();
    } while (true);
}