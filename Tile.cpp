#include "Tile.h"
#include <iostream>

Tile::Tile(sf::Texture& hiddenTileTexture, sf::Texture& flagTexture)
{
	hiddenTileSprite->setTexture(hiddenTileTexture); //first sprite for if tile is hidden or revealed
	revealedTileSprite->setTexture(hiddenTileTexture); //second sprite for numbers, mine
	flagSprite->setTexture(flagTexture); //flag sprite gets set to flag texture
	
}

void Tile::moveSprites(float x, float y)
{
	hiddenTileSprite->move(sf::Vector2f(x, y));
	revealedTileSprite->move(sf::Vector2f(x, y));
	flagSprite->move(sf::Vector2f(x, y));
}

void Tile::setAdjTiles(std::vector<Tile*>& adjTiles)
{
	adjacentTiles = adjTiles;
	adjMine = 0;
	for (int i = 0; i < adjTiles.size(); i++)
	{
		Tile* tempTile = adjTiles.at(i);
		if (tempTile->isMine())
		{
			adjMine++;
		}
	}
}


