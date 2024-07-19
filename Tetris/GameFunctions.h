#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Tetromino.h"
using namespace sf;

class Tetromino;

const int rows = 20;
const int cols = 10;

char randomTetrominoGenerator(char [4], char[7]);

void collisionBottom(int [rows][cols], int, int, bool&);

void collisionOnLeft(int[rows][cols], int, int, bool&, bool&);

void collisionOnRight(int [rows][cols], int, int, bool&, bool&);

bool collisionAtRotation(int [rows][cols], int**, int, int, int);

void drawCells(RenderWindow&, RectangleShape&, int [rows][cols], Color [7]);

void drawTetrominoes(RenderWindow& w, RectangleShape&, Tetromino* t, int [rows][cols], int, int, bool&, bool&, bool&, Color [7]);

void shiftCellsDown(int[rows][cols], int);

void clearLine(int [rows][cols]);