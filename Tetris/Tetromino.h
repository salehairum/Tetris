#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameFunctions.h"
using namespace std;
using namespace sf;

class Tetromino
{
	int n;
	int** matrix;
	char shapeType;
	int color;

public:
	//constructors
	Tetromino();
	Tetromino(char);

	//initialization functions
	void setMatrixSize();
	void fillMatrix_SetColor();

	//getters
	int getValueAtIndices(int, int);
	int getMatrixSize();
	int getColor();

	//rotation functions
	void rotation(int [20][10], int&, int&);
	void moveCorner(int**);
};