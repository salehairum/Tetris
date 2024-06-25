#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Tetromino
{
	int n;
	int rotation[2];
	int** matrix;
	char shapeType;
	Color color;

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
	Color getColor();
};