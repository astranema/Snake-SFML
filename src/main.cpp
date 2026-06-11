#include <SFML/Graphics.hpp>

int main()
{

	sf::RenderWindow window( sf::VideoMode( { 800, 800 } ), "Snake" );

	while ( window.isOpen() )
	{
		// this is an = not an ==
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		// all draws
		window.display();
	}
}
