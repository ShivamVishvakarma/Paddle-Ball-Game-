#include"Game.h"
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<string>
#include<sstream>
#define M_PI 3.1415926535897932

std::string toString(int num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}



Game::Game(int w, int h, std::string title)
{
    window = new sf::RenderWindow(sf::VideoMode(w, h), title);
    width = w;
    height = h;

    paddle.setSize(sf::Vector2f(100.0f, 20.0f));
    paddle.setFillColor(sf::Color::White);
    paddle.setPosition(sf::Vector2f(400, h - 40.f));

    ball.setRadius(9.0f);
    ball.setFillColor(sf::Color(sf::Color::Blue));
    ball.setOutlineThickness(1.0f);
    ball.setOutlineColor(sf::Color::White);

    defaultSpeed = 500.0f;
    angle = 0.0f;
    speed = sf::Vector2f(0.0f, 0.0f);
    bool isNotFirstTurn = true;
    int check = 0;

    font.loadFromFile("arial.ttf");

    score_text.setFont(font);
    score_text.setCharacterSize(30);
    score_text.setFillColor(sf::Color::White);
    score_text.setPosition(sf::Vector2f(7, 7));
    score_text.setString("Score: 0");

    gameover.setFont(font);
    gameover.setCharacterSize(80);
    gameover.setFillColor(sf::Color::Yellow);
    gameover.setPosition(sf::Vector2f(190, 200));
    gameover.setString("Game Over");

    final_score.setFont(font);
    final_score.setCharacterSize(40);
    final_score.setFillColor(sf::Color::White);
    final_score.setPosition(sf::Vector2f(270, 330));
    final_score.setString("Final Score: ");


}

Game::~Game()
{
    delete window;
}

void Game::reset()
{
    speed = sf::Vector2f(0.0f, 0.0f);
    score_text.setString("Score: 0");
    score = 0;
    isNotFirstTurn = false;
    check = 1;

}


void Game::event(sf::Event e)
{
    if (e.type == sf::Event::Closed)
        window->close();
    else if (e.type == sf::Event::MouseMoved)
    {

        paddle.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x - (paddle.getSize().x / 2), height - 40));

        if (paddle.getPosition().x < 0)
            paddle.setPosition(sf::Vector2f(0, paddle.getPosition().y));
        else if (paddle.getPosition().x > width - paddle.getSize().x)
            paddle.setPosition(sf::Vector2f(width - paddle.getSize().x, paddle.getPosition().y));
    }
    else if (e.type == sf::Event::MouseButtonPressed)
    {
        if (isNotFirstTurn == false)
        {
            ball.setPosition(sf::Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y));

            angle = (-20 - (rand() % 140)) * (M_PI / 180.0);
            speed.x = cos(angle) * defaultSpeed;
            speed.y = sin(angle) * defaultSpeed;
            isNotFirstTurn = true;
        }

    }




}

void Game::update(float dt)
{

    if (speed.y == 0.0f)
        ball.setPosition(sf::Vector2f(paddle.getPosition().x + (paddle.getSize().x / 2) - ball.getRadius(), paddle.getPosition().y - paddle.getSize().y));
    else
    {
        ball.setPosition(sf::Vector2f(ball.getPosition().x + speed.x * dt, ball.getPosition().y + speed.y * dt));

        //Ball-Boundary Collsion
        if (ball.getPosition().x <= 0.0f)
        {
            ball.setPosition(sf::Vector2f(0.0f, ball.getPosition().y));
            speed.x = abs(speed.x);
        }
        else if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= width)
        {
            ball.setPosition(sf::Vector2f(width - (ball.getRadius() * 2.0f), ball.getPosition().y));
            speed.x = -abs(speed.x);
        }

        if (ball.getPosition().y <= 0.0f)
        {
            ball.setPosition(sf::Vector2f(ball.getPosition().x, 0.0f));
            speed.y = abs(speed.y);
        }
        else if (ball.getPosition().y + (ball.getRadius() * 2.0f) >= height)
        {
            int store_score = score;
            final_score.setString("Final Score : " + toString(store_score));

            reset();


        }




        if (ball.getPosition().x + (ball.getRadius() * 2.0f) >= paddle.getPosition().x
            && ball.getPosition().y + (ball.getRadius() * 2.0f) >= paddle.getPosition().y
            && ball.getPosition().x < paddle.getPosition().x + paddle.getSize().x
            && ball.getPosition().y < paddle.getPosition().y + paddle.getSize().y)
        {


            ball.setPosition(sf::Vector2f(ball.getPosition().x, paddle.getPosition().y - (ball.getRadius() * 2.0f)));
            speed.y = -abs(speed.y);

            score += 1;
            score_text.setString("Score : " + toString(score));


        }

    }

}

void Game::render()
{
    window->draw(paddle);
    window->draw(ball);
    window->draw(score_text);

    if (check == 1) {

        window->clear();
        window->draw(gameover);
        window->draw(final_score);

    }

}

void Game::run()
{
    sf::Clock gameClock;
    float deltaTime = 0.0f;



    int score = 0;

    while (window->isOpen())
    {

        gameClock.restart();
        sf::Event e;
        while (window->pollEvent(e))
        {
            event(e);
        }


        update(deltaTime);


        window->clear();


        render();

        window->display();


        deltaTime = gameClock.getElapsedTime().asSeconds();


    }


}