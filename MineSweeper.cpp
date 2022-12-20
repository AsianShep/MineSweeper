#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Board.h"
#include "Tile.h"

int main()
{
    int count = 1;
    int column;
    int row;
    int mineCount;
    std::ifstream boardFile("boards/config.cfg");
    if (boardFile.is_open())
    {
        std::string line;
        while (getline(boardFile, line))
        {
            std::istringstream stream(line);
            int value;
            std::string sValue;
           
            std::getline(stream, sValue);
            value = stoi(sValue);
            
            if (count == 1)
            {
                column = value;
            }

            if (count == 2)
            {
                row = value;
            }

            if (count == 3)
            {
                mineCount = value;
            }
            count++;

        }
    }

    int tileCount = column * row;
    int width = column * 32;
    int height = row * 32 + 100;
    
    Board board(row, column, tileCount, mineCount);
    sf::RenderWindow window(sf::VideoMode(width, height), "MineSweeper");
   
    while (window.isOpen())

    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonReleased) 
            {
                if (event.mouseButton.button == sf::Mouse::Left) 
                {
                    board.mouseClick(event.mouseButton.x, event.mouseButton.y, "left");
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    board.mouseClick(event.mouseButton.x, event.mouseButton.y, "right");
                }
            }
        }
        window.clear(); 
        board.drawBoard(window);
        window.display();
    }
    return 0;
}