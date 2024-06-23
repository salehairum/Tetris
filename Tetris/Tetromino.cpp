#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tetromino.h"
using namespace std;
using namespace sf;

Tetromino::Tetromino()
{}

Tetromino::Tetromino(char sType)
{
	shapeType = sType;
	setMatrixSizeAndRotation();

	matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n] {0};

	fillMatrix();
}

void Tetromino::setMatrixSizeAndRotation()
{
	if (shapeType == 'I')
	{
		n = 4;
		/*rotation[0] = 1;
		rotation[1] = 1;*/
	}
	else if (shapeType == 'O')
	{
		n = 2;/*
		rotation[0] = 1;
		rotation[1] = 1;*/
	}
	else 
	{
		n = 3;
		rotation[0] = 1;
		rotation[1] = 1;
	}
}

void Tetromino::fillMatrix()
{
	if (shapeType == 'I')
	{
		for (int i = 0; i < n; i++)
			matrix[1][i] = 1;
	}
	else if (shapeType == 'O')
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = 1;
	}
	else if (shapeType == 'S')
	{
		matrix[0][1] = 1;
		matrix[0][2] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
	}
	else if (shapeType == 'Z')
	{
		matrix[0][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
		matrix[1][2] = 1;
	}
	else if (shapeType == 'L')
	{
		matrix[0][2] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[1][2] = 1;
	}
	else if (shapeType == 'J')
	{
		matrix[0][0] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[1][2] = 1;
	}
	else if (shapeType == 'T')
	{
		matrix[0][1] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[1][2] = 1;
	}
}

int Tetromino::getValueAtIndices(int i, int j)
{
	return matrix[i][j];
}

int Tetromino::getMatrixSize()
{
	return n;
}