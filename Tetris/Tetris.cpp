#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

//window and cell variables
const int rows = 20;
const int cols = 10;
const float cellSize = 8.0;
const float scale = 4.0;
const float unit = cellSize*scale; 
const float outline = 4.0;

int main()
{
	//Window
	RenderWindow window(VideoMode((cols+10)*unit, rows * unit), "Tetris", Style::Close | Style::Resize);

	//cells for the window
	RectangleShape cell(Vector2f(unit, unit));
	cell.setFillColor(Color(0,0, 255, 100));
	cell.setOutlineColor(Color::Black);
	cell.setOutlineThickness(outline);
	

	while (window.isOpen())
	{
		Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == evnt.Closed)
				window.close();
			else if (evnt.type == evnt.Resized)
				cout << "Resize";
		}

		window.clear();

		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				cell.setPosition(Vector2f(i*unit, j*unit));
				window.draw(cell);
			}
		}

		window.display();
	}
}