//search "to work"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
#include "Constants.h"
#include "GameFunctions.h"
using namespace std;
using namespace sf;

//to work:
 
// add destructors/del tetromino ptrs

// game over?

//window and cell variables
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

//collision functions
void collisionBottom(int m[rows][cols], int i, int j, bool& collisionGround)
{
    if (m[j + 1][i]!=0 || j >= rows - 1)
    {
        //this means that there are blocks below this tetromino and thus collision is taking place
        collisionGround = true;
    }
}

void collisionOnLeft(int m[rows][cols], int i, int j, bool& collisionLeft, bool& leftSet)
{
    if (i <= 0 || m[j][i - 1] != 0 )
    {
        leftSet = true;
        collisionLeft = true;
    }
    else collisionLeft = false;
}

void collisionOnRight(int m[rows][cols], int i, int j, bool& collisionRight, bool& rightSet)
{
    if (i >= cols - 1 || m[j][i + 1] != 0)
    {
        rightSet = true;
        collisionRight = true;
    }
    else collisionRight = false;
}

bool collisionAtRotation(int m[rows][cols], int** copy, int n, int row, int col)
{
    bool colLeft = false;
    bool colRight = false;
    bool colGround = false;
    bool set = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (copy[i][j])
            {
                if(m[j + row][i + col] || i + col < 0 || i + col > cols - 1)
                {
                    return true;
                }

                collisionBottom(m, i + col, j + row, colGround);
                if (colGround)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

//game functions for drawing
void drawCells(RenderWindow& w, RectangleShape& cell, int m[rows][cols], Color colors[7])
{
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            if(m[j][i]!=0)
                cell.setFillColor(colors[m[j][i]-1]);
            else cell.setFillColor(Color(0, 0, 255, 100));
            cell.setPosition(Vector2f(i * unit, j * unit));
            w.draw(cell);
        }
    }
}

void drawTetrominoes(RenderWindow& w, RectangleShape& cell, Tetromino* t, int m[rows][cols], int row, int col, bool& collisionGround, bool& collisionLeft, bool& collisionRight, Color colors[7])
{
    cell.setFillColor(colors[t->getColor()]);
    int n = t->getMatrixSize();
    bool leftSet = false;
    bool rightSet = false;
    for (int i =0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (t->getValueAtIndices(i, j))
            {
                collisionBottom(m, i+col, j+row, collisionGround);
                if(!leftSet)
                    collisionOnLeft(m, i+col, j+row, collisionLeft, leftSet);
                if(!rightSet)
                   collisionOnRight(m, i+col, j+row, collisionRight, rightSet);
                cell.setPosition(Vector2f((i + col) * unit, (j + row) * unit));
                w.draw(cell);
            }
        }
    }
}

void shiftCellsDown(int m[rows][cols], int cleared)
{
    for (int i = cleared-1; i > 0; i--)
    {
        for (int j = 0; j < cols; j++)
        {
            m[i+1][j] = m[i][j];
        }
    }
}

void clearLine(int m[rows][cols], int& score)
{
    for (int i = 0; i < rows; i++)
    {
        bool line = true;
        for (int j = 0; j < cols && line; j++)
        {
            if (m[i][j] == 0)
            {
                line = false;
            }
        }
        if (line)
        {   
            score++;
            //shift down cells above this row
            shiftCellsDown(m, i);
        }
    }
}

bool gameOver(int m[rows][cols], int startCol, int pieceSize)
{
    for (int i = startCol; i < startCol + pieceSize; i++)
    {
        for(int j=0;j<pieceSize;j++)
        {
            if (m[j][i])
                return true;
        }
    }
    return false;
}

int main()
{
    //initialize seed
    srand(time(0));

    //Window
    RenderWindow window(VideoMode((cols + 10) * unit, rows * unit), "Tetris", Style::Close | Style::Resize);
    Vector2i windowPos=window.getPosition();

    //cells for the window
    RectangleShape cell(Vector2f(unit - (outline * 2), unit - (outline * 2)));
    cell.setOutlineColor(Color::Black);
    cell.setOutlineThickness(outline);

    //play button
    RectangleShape playButton(Vector2f((rows / 4) * unit, (cols / 4) * unit));
    playButton.setFillColor(Color(0, 0, 255, 100));
    playButton.setPosition(windowPos.x / 2 +75, windowPos.y / 2 + 175);

    //game over background
    RectangleShape gameOverBox(Vector2f(rows / 2 * unit, cols / 2 * unit));
    gameOverBox.setFillColor(Color(30, 20, 117));
    gameOverBox.setPosition(windowPos.x / 2-160, windowPos.y / 2+120);
    gameOverBox.setOutlineColor(Color::Black);
    gameOverBox.setOutlineThickness(10);

    //tetris logo
    RectangleShape tetrisLogo(Vector2f(600, 600));
    Texture tetris;
    tetris.loadFromFile("tetrislogo.png");
    tetrisLogo.setTexture(&tetris);
    Vector2f logoSize = tetrisLogo.getSize();
    Vector2u textureSize = tetris.getSize();
    tetrisLogo.setScale(logoSize.x / textureSize.x, logoSize.y / textureSize.y);
    tetrisLogo.setPosition(windowPos.x / 2 +25, windowPos.y / 2-75);

    //font and text
    Font font;
    if (!font.loadFromFile("Faction-Clean.ttf"))
        cout << "error in loading" << endl;

    Text play;
    play.setFillColor(Color::White);
    play.setString("Play");
    play.setCharacterSize(45);
    play.setPosition(windowPos.x / 2+107, windowPos.y / 2+175);
    play.setFont(font);

    Text gameOverText;
    gameOverText.setFillColor(Color::White);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setPosition(windowPos.x/2-130, windowPos.y/2+160);
    gameOverText.setFont(font);

    Text scoreText;
    scoreText.setFillColor(Color::White);
    scoreText.setString("Score: ");
    scoreText.setCharacterSize(35);
    scoreText.setPosition(windowPos.x / 2 + 95, windowPos.y / 2 + 275);
    scoreText.setFont(font);

    Text scoreNum;
    scoreNum.setFillColor(Color::White);
    scoreNum.setString("0");
    scoreNum.setCharacterSize(35);
    scoreNum.setPosition(windowPos.x / 2 + 195, windowPos.y / 2 + 275);
    scoreNum.setFont(font);

    //clock for moving cell down
    Clock clock;
    float deltaTime = 0.0f;
    float accumulator = 0.0f;

    //assign numbers to each of the tetromino letters
    char shapes[7] = { 'I','L','J','S','Z','T','O' };
    //assign corresponding colours
    Color colors[7] = { Color(0, 240, 240, 255), Color(240, 160, 0, 255), Color(0, 0, 240, 255), Color(0, 240, 0, 255), Color(240, 0, 0, 255), Color(160, 0, 240, 255), Color(240, 240, 0, 255) };

    //array for keeping track of previously generated tetrominoes
    char prev[4] = { 'I','I','I','I' };

    //current position
    int currentRow = 0;
    int currentCol = 3;

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
    bool collisionGround = false;
    bool collisionLeft = false;
    bool collisionRight = false;
    bool gameEnd = false;
    bool gameStart = false;
    int score = 0;

    //Tetromino ptr for tetromino that moves down
    Tetromino* tetromino= new Tetromino(randomTetrominoGenerator(prev, shapes));

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
                if (evnt.key.code == Keyboard::Left && !collisionLeft)
                    currentCol -= 1;
                else if (evnt.key.code == Keyboard::Right && !collisionRight)
                    currentCol += 1;
                else if (evnt.key.code == Keyboard::Down && !collisionGround)
                    currentRow += 1;
                else if (evnt.key.code == Keyboard::Up)
                    tetromino->rotation(matrix, currentRow, currentCol);
            }
            else if (evnt.type == Event::MouseButtonPressed)
            {
                if (evnt.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePosition = Mouse::getPosition(window);
                    if (playButton.getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                    {
                        gameStart = true;
                    }
                }
            }
        }

        if(gameStart)
        {
            //after a specific interval, game is updated
            if (accumulator >= timeStep)
            {
                accumulator = 0.0f;

                if (collisionGround)
                {
                    //modify the matrix
                    int n = tetromino->getMatrixSize();
                    int tetrominoColor = tetromino->getColor() + 1;

                    for (int i = 0; i < n; i++)
                    {
                        for (int j = 0; j < n; j++)
                        {
                            if (tetromino->getValueAtIndices(i, j))
                            {
                                matrix[currentRow + j][currentCol + i] = tetrominoColor;
                            }
                        }
                    }

                    //generate the next tetromino
                    tetromino = new Tetromino(randomTetrominoGenerator(prev, shapes));

                    //for next round, reset variables
                    collisionGround = false;
                    n = tetromino->getMatrixSize();
                    currentRow = 0;
                    if (n == 2)
                        currentCol = 4;
                    else currentCol = 3;

                    gameEnd = gameOver(matrix, currentCol, n);
                }
                else
                {
                    currentRow++;
                }
            }
        }

        window.clear();

        window.draw(tetrisLogo);
        window.draw(playButton);
        window.draw(play);
        window.draw(scoreText);

        //draw cells
        drawCells(window, cell, matrix, colors);

        if(!gameEnd && gameStart)
        {
            drawTetrominoes(window, cell, tetromino, matrix, currentRow, currentCol, collisionGround, collisionLeft, collisionRight, colors);
            //update matrix if line can be cleared
            clearLine(matrix, score);
            string scoreStr = to_string(score);
            scoreNum.setString(scoreStr);
        }
        window.draw(scoreNum);
        
        if(gameEnd)
        {
            gameStart = false;
            window.draw(gameOverBox);
            window.draw(gameOverText);
        }

        window.display();
    }
}