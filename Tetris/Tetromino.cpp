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

	fillMatrix_SetColor();
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

void Tetromino::fillMatrix_SetColor()
{
	if (shapeType == 'I')
	{
		color = Color(0, 240, 240, 255);
		for (int i = 0; i < n; i++)
			matrix[i][1] = 1;
	}
	else if (shapeType == 'O')
	{
		color = Color(240, 240, 0, 255);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = 1;
	}
	else if (shapeType == 'S')
	{
		color = Color(0, 240, 0, 255);
		matrix[1][0] = 1;
		matrix[2][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
	}
	else if (shapeType == 'Z')
	{
		color = Color(240, 0, 0, 255);
		matrix[0][0] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'L')
	{
		color = Color(240, 160, 0, 255);
		matrix[2][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'J')
	{
		color = Color(0, 0, 240, 255);
		matrix[0][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'T')
	{
		color = Color(160, 0, 240, 255);
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

Color Tetromino::getColor()
{
	return color;
}