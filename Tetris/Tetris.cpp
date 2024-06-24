#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
using namespace std;
using namespace sf;

//window and cell variables
const int rows = 20;
const int cols = 10;
const float cellSize = 8.0;
const float scale = 4.0;
const float unit = cellSize * scale;
const float outline = 4.0;
const float timeStep = 0.75;
const float moveSpeed = 40.0f; 

//game functions
void drawCells(RenderWindow& w, RectangleShape& cell)
{
    cell.setFillColor(Color(0, 0, 255, 100));

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            cell.setPosition(Vector2f(i * unit, j * unit));
            w.draw(cell);
        }
    }
}

void drawTetrominoes(RenderWindow& w, RectangleShape& cell, char type, int row, int col)
{
    cell.setFillColor(Color(255, 0, 0, 255));

    Tetromino t(type, 0);
    int n = t.getMatrixSize();
    for (int i =0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (t.getValueAtIndices(i, j))
            {
                cell.setPosition(Vector2f((i + col) * unit, (j + row) * unit));
                w.draw(cell);
            }
        }
    }
}

int main()
{
    //Window
    RenderWindow window(VideoMode((cols + 10) * unit, rows * unit), "Tetris", Style::Close | Style::Resize);

    //cells for the window
    RectangleShape cell(Vector2f(unit - (outline * 2), unit - (outline * 2)));
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(outline);

    //clock for moving cell down
    Clock clock;
    float deltaTime = 0.0f;
    float accumulator = 0.0f;

    //assign numbers to each of the tetromino letters
    char shapes[7] = { 'I','L','J','S','Z','T','O' };

    //create array of colours of the blocks
    Color colours[] = { Color(240,240,0,255), Color(240,160,0,255) ,Color(240,0,0,255), Color(160,0,240,255), Color(0,0,240,255), Color(0,240,240,255), Color(0,240,0,255) };

    //current position
    int currentRow = 0;
    int currentCol = 0;

    //game logic
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        //event management
        Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
                window.close();
            else if (evnt.type == evnt.Resized)
                cout << "Resize";
            else if (evnt.type == Event::KeyPressed)
            {
                if (evnt.key.code == Keyboard::Left)
                    currentCol -= 1; // Move left by one cell
                else if (evnt.key.code == Keyboard::Right)
                    currentCol += 1; // Move right by one cell
            }
        }

        //after a specific interval, game is updated
        if (accumulator >= timeStep)
        {
            accumulator = 0.0f;
            currentRow++;
        }

        window.clear();

        //draw cells
        drawCells(window, cell);
        drawTetrominoes(window, cell, shapes[0], currentRow, currentCol);

        window.display();
    }
}