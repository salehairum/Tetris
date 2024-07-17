#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
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
	void setMatrixSizeAndRotation();
	void fillMatrix_SetColor();

	//getters
	int getValueAtIndices(int, int);
	int getMatrixSize();
	int getColor();

	//rotation functions
	void rotation();
	void moveCorner(int**);
};