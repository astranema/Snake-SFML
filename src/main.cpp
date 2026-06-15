#include <SFML/Graphics.hpp>
#include <iostream>

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
	Coords* coords;
	Node* next;
	Node* prev;
public:
	Node() {
		coords = nullptr;
		next = nullptr;
	}
	Node(int x, int y) {
		this->coords = new Coords(x, y);
		next = nullptr;
	}
	Node* get_next() {
		return next;
	}
	void set_next(Node* node) {
		this->next = node;
	}
	Coords* get_coords() {
		return this->coords;
	}
};
/* 
head = beginning of linked list
tail = end of linked list
next goes away from head towards tail
*/
class DoublyLinkedList {
private:
	Node* head;
	Node* tail;
public:
	DoublyLinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}
	Node* get_head() {
		return head;
	}
	Node* get_tail() {
		return tail;
	}
	void insert(Node* node) {
		// old head points towards new head
		if (head != nullptr) {
			head->set_next(node);
		}
		// updating head and tail
		head = node;
		if (tail == nullptr) {
			tail = node;
		}
	}
	void service() {
		if (tail == nullptr) {
			return;
		}
		Node* old_tail = tail;
		tail = tail->get_next();
		delete old_tail;
		if (tail == nullptr) {
			head = nullptr;
		}
	}
};

enum class Direction {
	Up,
	Down,
	Left,
	Right
};


void render_square_from_coords(sf::RenderWindow &window, Coords* coords, sf::Color color);
void render_squares_from_node(sf::RenderWindow &window, Node* node, sf::Color color);

int main()
{
	Direction direction = Direction::Right;
	Coords* apple_cords = new Coords(7, 5);
	sf::RenderWindow window( sf::VideoMode( { 800, 800 } ), "Snake" );
	DoublyLinkedList* snake = new DoublyLinkedList();
	snake->insert(new Node(2, 2));
	snake->insert(new Node(3, 2));
	snake->insert(new Node(6, 2));
	int i = 0;

	while ( window.isOpen() )
	{
		// checking for events
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
		// run frame
		if (i % 500 == 0) {
			// get new node x and y;
			Node* new_node = nullptr;
			int old_x = snake->get_head()->get_coords()->get_x();
			int old_y = snake->get_head()->get_coords()->get_y();
			if (direction == Direction::Up) {
				new_node = new Node(old_x, old_y - 1);
			}
			else if (direction == Direction::Down) {
				new_node = new Node(old_x, old_y + 1);
			}
			else if (direction == Direction::Left) {
				new_node = new Node(old_x - 1, old_y);
			}
			else if (direction == Direction::Right) {
				new_node = new Node(old_x + 1, old_y);
			}
			snake->insert(new_node);
			snake->service();
		}

		window.clear();
		// draws apple
		render_square_from_coords(window, apple_cords, sf::Color::Red);
		// draw snake
		render_squares_from_node(window, snake->get_tail(), sf::Color::Green);
		window.display();

		i += 1;
	}
}

void render_square_from_coords(sf::RenderWindow &window, Coords* coords, sf::Color color) {
	sf::RectangleShape square = sf::RectangleShape();
	square.setSize(sf::Vector2f(80, 80));
	square.setPosition(sf::Vector2f(static_cast<float>(80*coords->get_x()), static_cast<float>(80*coords->get_y())));
	square.setFillColor(color);
	window.draw(square);
}

// recursive
void render_squares_from_node(sf::RenderWindow &window, Node* node, sf::Color color) {
	if (node == nullptr) {
		return;
	}
	render_square_from_coords(window, node->get_coords(), color);
	render_squares_from_node(window, node->get_next(), color);
}