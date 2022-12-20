#pragma once
#include "Tile.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
private:
	std::vector<std::vector<Tile*>> tiles;
	int mineCount = 0;
	int flaggedTile = 0;
	int maxMineCount;
	int tileCount;
	bool showMineMode = false;
	bool lost = false;
	bool won = false;
	int row;
	int column;
	int tileToWin;
	sf::Sprite showMineSprite;
	sf::Sprite happySprite;
	sf::Sprite test1Sprite;
	sf::Sprite test2Sprite;
	sf::Sprite test3Sprite;
	sf::Sprite scoreSprite;
	sf::Sprite scoreSprite2;
	sf::Sprite scoreSprite3;
	sf::Sprite scoreSpriteNegative;

	sf::Texture hiddenTile;
	sf::Texture revealedTile;
	sf::Texture flag;
	sf::Texture smileyFace;
	sf::Texture lostFace;
	sf::Texture wonFace;
	sf::Texture mineButton;
	sf::Texture test1Button;
	sf::Texture test2Button;
	sf::Texture test3Button;
	sf::Texture mine;
	sf::Texture digits;
	sf::Texture number1;
	sf::Texture number2;
	sf::Texture number3;
	sf::Texture number4;
	sf::Texture number5;
	sf::Texture number6;
	sf::Texture number7;
	sf::Texture number8;


public:
	Board(int _row, int _column, int _tileCount, int _maxMineCount);
	~Board();
	void drawBoard(sf::RenderWindow& window);
	void setupBoard();
	void mouseClick(int x, int y, std::string left_right);
	void flagTile(Tile* tile);
	void handleReveal(Tile* tile);
	void setSpriteTexture(sf::Sprite* sprite, sf::Texture& text);
	void mineGenerator();
	void remainingMines();
	void setAdjacentTiles();
	void loseGame();
	void winGame();
	void loadBoard(std::string boardFile);

};
