#include <SFML/Graphics.hpp>

// coordinates with two ints. 
class Coords {
private:
	int y;
	int x;
public:
	Coords(int x, int y) {
		set_x(x);
		set_y(y);
	}
	void set_x(int x) {
		this->x = x;
	}
	void set_y(int y) {
		this->y = y;
	}
	int get_x() {
		return this->x;
	}
	int get_y() {
		return this->y;
	}
};

void render_square_from_coords(sf::RenderWindow &window, Coords coords, sf::Color color);

int main()
{
	Coords apple_cords = Coords(7, 5);
	sf::RenderWindow window( sf::VideoMode( { 800, 800 } ), "Snake" );
	
	while ( window.isOpen() )
	{
		// checking if window must be closed
		// this is an = not an ==
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		// draws apple
		render_square_from_coords(window, apple_cords, sf::Color::Red);
		window.display();
	}
}

void render_square_from_coords(sf::RenderWindow &window, Coords coords, sf::Color color) {
	sf::RectangleShape square = sf::RectangleShape();
	square.setSize(sf::Vector2f(80, 80));
	square.setPosition(sf::Vector2f(static_cast<float>(80*coords.get_x()), static_cast<float>(80*coords.get_y())));
	square.setFillColor(color);
	window.draw(square);
}
