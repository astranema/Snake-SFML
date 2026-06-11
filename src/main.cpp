#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window( sf::VideoMode( { 400, 400 } ), "SFML works!" );
	sf::CircleShape shape( 100.f );
	shape.setFillColor( sf::Color::Magenta );
	shape.setPosition( sf::Vector2f( { 100, 100 }));

	while ( window.isOpen() )
	{
		sf::CircleShape shape2( 100.f );
		shape2.setFillColor( sf::Color::Green );
		shape2.setPosition( sf::Vector2f( { 50, 100 }));
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		window.draw( shape );
		window.draw( shape2 );
		window.display();
	}
}
