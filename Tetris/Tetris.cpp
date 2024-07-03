//search "to work"
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

char randomTetrominoGenerator(char prev[4], char shapes[7])
{
    int index = (rand() % 7);
    char result = shapes[index];
    for (int i = 0; i < 4; i++)
        if (prev[i] == result)
            return randomTetrominoGenerator(prev, shapes);
    //if this has not appeared in the last 4 attempts, then shift the array and insert this in the prev array
    for (int i = 3; i > 0; i--)
        prev[i] = prev[i - 1];
    prev[0] = result;
    return result;
}

//collision function
void collisionWithGround(int m[rows][cols], int i, int j, bool& collision)
{
    //to work, update matrix
    if (m[j + 1][i] || j == rows - 1)
    {
        //this means that there are blocks below this tetromino and thus collision is taking place
        collision = true;
    }
}

//game functions for drawing
void drawCells(RenderWindow& w, RectangleShape& cell, int m[rows][cols])
{
    /*cell.setFillColor(Color(0, 0, 255, 100));*/

    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            //to work
            //change colour of the matrix based on tetris added
            cell.setFillColor(Color(0, 0, 255, 100));
            cell.setPosition(Vector2f(i * unit, j * unit));
            w.draw(cell);
        }
    }
}

void drawTetrominoes(RenderWindow& w, RectangleShape& cell, Tetromino* t, int m[rows][cols], int row, int col, bool& collision)
{
    cell.setFillColor(t->getColor());
    int n = t->getMatrixSize();
    for (int i =0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (t->getValueAtIndices(i, j))
            {
                collisionWithGround(m, col, row, collision);
                cell.setPosition(Vector2f((i + col) * unit, (j + row) * unit));
                w.draw(cell);
            }
        }
    }
}

int main()
{
    //initialize seed
    srand(time(0));

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

    //array for keeping track of previously generated tetrominoes
    char prev[4] = { 'I','I','I','I' };

    //current position
    int currentRow = 0;
    int currentCol = 0;

    //game board matrix
    int matrix[rows][cols];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            matrix[i][j] = 0;
        }
    }

    //game logic
    bool collision = false;

    //Tetromino ptr for tetromino that moves down
    Tetromino* tetromino=new Tetromino('I');

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

            if (collision)
            {
                tetromino = new Tetromino(randomTetrominoGenerator(prev, shapes));
                collision = false;
            }
        }

        window.clear();

        //draw cells
        drawCells(window, cell, matrix);
        drawTetrominoes(window, cell, tetromino, matrix, currentRow, currentCol, collision);

        window.display();
    }
}