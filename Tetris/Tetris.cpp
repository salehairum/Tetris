#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

const int rows = 20;
const int cols = 8;
const int unit = 40;

int main()
{
	//Window
	RenderWindow window(VideoMode((cols+10)*unit, rows * unit), "Tetris", Style::Close | Style::Resize);

	//cells for the window
	RectangleShape cell(Vector2f(1.0f, 1.0f));
	cell.setFillColor(Color::White);
	cell.setOutlineColor(Color::Black);
	cell.setScale(unit, unit);

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

	}
}