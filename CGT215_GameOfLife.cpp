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
const int gridY = 25;
const int buffer = 100;

RenderWindow window(VideoMode(800, 600), "Game of Life");


int cellSize = (window.getSize().x - buffer) / min(gridX, gridY);
int border = 3;

//Arrays that reference variables gridX or gridY
RectangleShape cell[gridX][gridY];
int currentStep[gridX][gridY];
int nextStep[gridX][gridY];

//Load textures function. 
void LoadTex(Texture& tex, string filename) {
    if (!tex.loadFromFile(filename)) {
        cout << "Could not load " << filename << endl;
    }
}



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
            cell[x][y].setFillColor(Color(255, 0, 255));
            cell[x][y].setPosition(Vector2f(cellSize * x, cellSize * y));
        }
    }
}

//Had to get this from StackOverflow. 
//Used for the procedural generator. Might replace later. 
bool generateBool() 
{

    int g = rand() % 100;
    return (g > 30); // 1 is converted to true and 0 as false

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
    int alive;

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            alive = 0;

            //Loop each neighboring cell. 
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    
                    if (i == 0 and j == 0) {
                        continue;
                    }

                    int neighborX = x + i;
                    int neighborY = y + j;
                    
                    if (neighborX >= 0 and neighborX < gridX and neighborY >= 0 and neighborY < gridY) {
                    
                        if (currentStep[neighborX][neighborY] == 1) {
                            alive++;
                        }
                    }
                }
            }

            if (alive < 2 || alive > 3)
            {
                nextStep[x][y] = 0;
            }
            else if (alive == 3)
            {
                nextStep[x][y] = 1;
            }
            else
            {
                nextStep[x][y] = currentStep[x][y];
            }
            
            
        }
        
        
        
    }
    memcpy(currentStep, nextStep, sizeof(currentStep));
    //cout << "Step simulated" << endl;
}

void drawGrid() 
{
    window.clear();

    for (int x = 0; x < gridX; x++)
    {
        for (int y = 0; y < gridY; y++)
        {
            if (currentStep[x][y] == 0) 
            {
                cell[x][y].setFillColor(Color(255, 255, 255));
            }
            else 
            {
                cell[x][y].setFillColor(Color(255, 0, 255));
            }
            window.draw(cell[x][y]);
        }
    }
    //cout << "Grid Drawn" << endl;
    
} 

int main()
{
    srand(time(nullptr));
    
    Clock clock;
    Time lastTime(clock.getElapsedTime());
    Time currentTime(lastTime);

    initialize();
    randomizeGrid();

    do { 
        
        currentTime = clock.getElapsedTime();
        Time deltaTime = currentTime - lastTime;
        long deltaMS = deltaTime.asMilliseconds();

        if (deltaMS > 1000) 
        {
            lastTime = currentTime;
            simulateStep();
            
        }
        drawGrid();
        
        window.display();
    } while (true);
}