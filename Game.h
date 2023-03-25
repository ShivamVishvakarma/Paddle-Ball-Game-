#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	sf::RenderWindow* window = NULL;
	sf::Event e;
	int width;
	int height;

	sf::CircleShape ball;
	sf::RectangleShape paddle;

	float defaultSpeed;
	float angle;
	sf::Vector2f speed;
	int score;
	int check;
	bool isNotFirstTurn;

	sf::Font font;
	sf::Text score_text;
	sf::Text gameover;
	sf::Text final_score;




public:
	Game(int w, int h, std::string title);
	~Game();
	void reset();

	void event(sf::Event e);
	void update(float dt);
	void render();

	void run();

};
