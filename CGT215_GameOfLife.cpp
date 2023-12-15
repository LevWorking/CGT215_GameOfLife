// CGT215_GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

using namespace std;
using namespace sf;


RenderWindow window(VideoMode(1200, 800), "Game of Life");

//Set the dimensions of the grid.
const int gridX = 20;
const int gridY = 20;
const int buffer = window.getSize().x / 4;
const int uiPos = window.getSize().y / 5;


int cellSize = (window.getSize().x - buffer) / min(gridX, gridY);
int border = 3;

//Arrays that reference variables gridX or gridY
RectangleShape cell[gridX][gridY];
int currentStep[gridX][gridY];
int nextStep[gridX][gridY];

int stepCount = 0;

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
    stepCount++;
    //cout << "Step simulated" << endl;
}


int main()
{
    //Setting up buttons and their associated textures. 
    Texture pause;
    LoadTex(pause, "assets/pause.png");
    Sprite pauseButton;
    pauseButton.setTexture(pause);
    pauseButton.setScale(0.125, 0.125);

    Texture play;
    LoadTex(play, "assets/play.png");

    pauseButton.setPosition(window.getSize().x - 0.5 * buffer, uiPos / 4);

    //Setting up fonts & variables that use the font. 
    Font fnt;
    if (!fnt.loadFromFile("assets/fnt_cyber.ttf")) {
        cout << "Could not load font." << endl;
        exit(3);
        Text stepText;
        stepText.setFont(fnt);
        stepText.setString("Steps: " + to_string(stepCount));
        stepText.setPosition(window.getSize().x - 0.2 * buffer, uiPos / 4);
    }

    bool gamePaused = false; 

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

        if (Keyboard::isKeyPressed(Keyboard::Space)) 
        {
            gamePaused = !gamePaused;
            if(gamePaused)
            {
                pauseButton.setTexture(play);
            }
            else
            {
                pauseButton.setTexture(pause);
            }


            while (Keyboard::isKeyPressed(Keyboard::Space)) {}
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) 
        {
            exit(0);
        }

        if (deltaMS > 1000 and !gamePaused) 
        {
            lastTime = currentTime;
            simulateStep(); 
            
        }

        //Start drawing Stuff
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
        
        window.draw(pauseButton);

        window.display();
    } while (window.isOpen());
}