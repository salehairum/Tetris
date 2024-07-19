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
	setMatrixSize();

	matrix = new int* [n];
	for (int i = 0; i < n; i++)
		matrix[i] = new int[n] {0};

	fillMatrix_SetColor();
}

void Tetromino::setMatrixSize()
{
	if (shapeType == 'I')
	{
		n = 4;
	}
	else if (shapeType == 'O')
	{
		n = 2;
	}
	else 
	{
		n = 3;
	}
}

void Tetromino::fillMatrix_SetColor()
{
	if (shapeType == 'I')
	{
		color = 0;
		for (int i = 0; i < n; i++)
			matrix[i][1] = 1;
	}
	else if (shapeType == 'O')
	{
		color = 6;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = 1;
	}
	else if (shapeType == 'S')
	{
		color = 3;
		matrix[1][0] = 1;
		matrix[2][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
	}
	else if (shapeType == 'Z')
	{
		color = 4;
		matrix[0][0] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'L')
	{
		color = 1;
		matrix[2][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'J')
	{
		color = 2;
		matrix[0][0] = 1;
		matrix[0][1] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
	}
	else if (shapeType == 'T')
	{
		color = 5;
		matrix[0][1] = 1;
		matrix[1][0] = 1;
		matrix[1][1] = 1;
		matrix[2][1] = 1;
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

int Tetromino::getColor()
{
	return color;
}

void Tetromino::moveCorner(int** copy)
{
	if (matrix[0][0])
	{
		copy[2][0] = 1;
	}
	else if (matrix[2][0])
	{
		copy[2][2] = 1;
	}
	else if (matrix[2][2])
	{
		copy[0][2] = 1;
	}
	else if (matrix[0][2])
	{
		copy[0][0] = 1;
	}
}

void Tetromino::rotation(int m[20][10], int& cRow, int& cCol)
{
	if (n == 2)	//'O' shape
		return; //no rotation
	int** copy=new int*[n];
	for (int i = 0; i < n; i++)
	{
		copy[i] = new int[n] {0};
	}
	if (n == 3)
	{
		copy[1][1] = 1;

		if (shapeType != 'T')	//has no corner pieces
			moveCorner(copy);

		//move other pieces
		if (matrix[1][0])
		{
			copy[2][1] = 1;
		}
		if (matrix[0][1])
		{
			copy[1][0] = 1;
		}
		if (matrix[1][2])
		{
			copy[0][1] = 1;
		}
		if (matrix[2][1])
		{
			copy[1][2] = 1;
		}
	}
	else
	{
		if (matrix[0][1])
			copy[2][0] = 1;
		if (matrix[2][0])
			copy[3][2] = 1;
		if (matrix[3][2])
			copy[1][3] = 1;
		if (matrix[1][3])
			copy[0][1] = 1;

		if (matrix[1][0])
			copy[3][1] = 1;
		if (matrix[3][1])
			copy[2][3] = 1;
		if (matrix[2][3])
			copy[0][2] = 1;
		if (matrix[0][2])
			copy[1][0] = 1;

		if (matrix[1][1])
			copy[2][1] = 1;
		if (matrix[2][1])
			copy[2][2] = 1;
		if (matrix[2][2])
			copy[1][2] = 1;
		if (matrix[1][2])
			copy[1][1] = 1;
	}

	if (collisionAtRotation(m, copy, n, cRow, cCol))
	{
		if (collisionAtRotation(m, copy, n, cRow + 1, cCol))
		{
			if (collisionAtRotation(m, copy, n, cRow + 1, cCol + 1))
			{
				if (collisionAtRotation(m, copy, n, cRow, cCol - 2))
				{
					if (collisionAtRotation(m, copy, n, cRow + 1, cCol - 2))
					{
						return;	//no rotation
					}
					else
					{
						cRow++;
						cCol -= 2;
					}
				}
				else
				{
					cCol -= 2;
				}
			}
			else
			{
				cRow++;
				cCol++;
			}
		}
		else cRow++;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			matrix[i][j] = copy[i][j];
}