#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Tile
{
private:
	sf::Sprite* hiddenTileSprite = new sf::Sprite; //sprite for hidden tile 
	sf::Sprite* revealedTileSprite = new sf::Sprite; //sprite for revealed tile
	sf::Sprite* flagSprite = new sf::Sprite; // sprite for flag
	bool flagged = false;
	bool revealed = false;
	bool mine = false;
	int adjMine = 0;
	std::vector<Tile*> adjacentTiles;

public:
	Tile(sf::Texture& hiddenTileTexture, sf::Texture& flagTexture); // a tile takes in a hidden tile or revealed tile and flag texture
	void moveSprites(float x, float y); //move sprite

	sf::Sprite* getHiddenTileSprite() //get sprite of hidden tile
	{
		return hiddenTileSprite;
	}

	sf::Sprite* getRevealedTileSprite() //get sprite of revealed tile
	{
		return revealedTileSprite;
	}

	sf::Sprite* getFlagSprite() //gte sprite of flag
	{ 
		return flagSprite; 
	}

	bool isRevealed() 
	{ 
		return revealed; 
	}

	bool isFlagged() 
	{
		return flagged;
	}

	bool isMine()
	{
		return mine;
	}

	void setIsMine(bool set)
	{ 
		mine = set; 
	}

	void setIsRevealed(bool set)
	{ 
		revealed = set;
	}

	void setIsFlagged(bool set)
	{ 
		flagged = set; 
	}

	void setAdjTiles(std::vector<Tile*>& adjTiles);

	int getAdjMines() 
	{ 
		return adjMine;
	}
	
	std::vector<Tile*>* getAdjTiles() 
	{
		return &adjacentTiles; 
	}


};

