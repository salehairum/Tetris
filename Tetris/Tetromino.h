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

public:
	//constructors
	Tetromino();
	Tetromino(char);

	//initialization functions
	void setMatrixSizeAndRotation();
	void fillMatrix();

	//getters
	int getValueAtIndices(int, int);
	int getMatrixSize();
};