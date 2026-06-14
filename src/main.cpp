#include <SFML/Graphics.hpp>

// coordinates with two ints. 
class Coords {
private:
	int y;
	int x;
public:
	Coords() {
		set_x(0);
		set_y(0);
	}
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
// node of doubly linked list
class Node {
private:
	Coords coords;
	Node* next;
	Node* prev;
public:
	Node(int x, int y) {
		this->coords = Coords(x, y);
		next = nullptr;
		prev = nullptr;
	}
	Node* get_next() {
		return next;
	}
	void set_next(Node* node) {
		this->next = node;
	}
	Node* get_prev() {
		return prev;
	}
	void set_prev(Node* node) {
		this->prev = node;
	}
};
class DoublyLinkedList {
private:
	Node* head;
	Node* tail;
public:
	Node* get_head() {
		return head;
	}
	void set_head(Node* node) {
		this->head = node;
	}
	Node* get_tail() {
		return tail;
	}
	void set_tail(Node* node) {
		this->tail = node;
	}
	void push_head(Node* node) {
		Node* old_head = this->get_head();
		this->set_head(node);
		node->set_next(old_head);
		node->set_prev(nullptr);
	}
	void pop_tail() {
		Node* old_tail = this->get_tail();
		this->set_tail(old_tail->get_prev());
		delete old_tail;
		this->get_tail()->set_next(nullptr);
	}
};

enum class Direction {
	Up,
	Down,
	Left,
	Right
};


void render_square_from_coords(sf::RenderWindow &window, Coords coords, sf::Color color);

int main()
{
	Direction direction = Direction::Right;
	Coords apple_cords = Coords(7, 5);
	sf::RenderWindow window( sf::VideoMode( { 800, 800 } ), "Snake" );
	
	while ( window.isOpen() )
	{
		// checking if window must be closed
		// this is an = not an ==
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
			{
				window.close();
			}
			// managing keyboard inputs
			if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
				if (key_pressed->code == sf::Keyboard::Key::W)
				{
					direction = Direction::Up;
				}
				if (key_pressed->code == sf::Keyboard::Key::S)
				{
					direction = Direction::Down;
				}
				if (key_pressed->code == sf::Keyboard::Key::D)
				{
					direction = Direction::Right;
				}
				if (key_pressed->code == sf::Keyboard::Key::A)
				{
					direction = Direction::Left;
				}
			}
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
