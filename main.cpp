#include<SFML/Graphics.hpp>
#include"Game.h"

int main()
{


    Game game(800, 800, "PaddleGame");
    game.run();

    return 0;
}