#include "Board.h"
#include "Random.h"
#include <iostream>
#include <fstream>

Board::Board(int _row, int _column, int _tileCount, int _maxMineCount) 
{
    maxMineCount = _maxMineCount;
    row = _row;
    column = _column;
    tileCount = _tileCount;
    tileToWin = tileCount - maxMineCount;
    if (!hiddenTile.loadFromFile("images/tile_hidden.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!revealedTile.loadFromFile("images/tile_revealed.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!flag.loadFromFile("images/flag.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!test1Button.loadFromFile("images/test_1.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!test2Button.loadFromFile("images/test_2.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!test3Button.loadFromFile("images/Test_3.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!smileyFace.loadFromFile("images/face_happy.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!mineButton.loadFromFile("images/debug.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!mine.loadFromFile("images/mine.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!digits.loadFromFile("images/digits.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number1.loadFromFile("images/number_1.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number2.loadFromFile("images/number_2.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number3.loadFromFile("images/number_3.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number4.loadFromFile("images/number_4.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number5.loadFromFile("images/number_5.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number6.loadFromFile("images/number_6.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number7.loadFromFile("images/number_7.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!number8.loadFromFile("images/number_8.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!lostFace.loadFromFile("images/face_lose.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }
    if (!wonFace.loadFromFile("images/face_win.png"))
    {
        std::cout << "Error loading image" << std::endl;
    }

    tiles = std::vector<std::vector<Tile*>>(row, std::vector<Tile*>(column)); //setting vector equal to size of the board
    happySprite.setTexture(smileyFace);
    happySprite.setPosition(sf::Vector2f(32 * (column/2), 32 * row));
    showMineSprite.setTexture(mineButton);
    showMineSprite.setPosition(sf::Vector2f(32 * (column/2 + 4), 32 * row));
    test1Sprite.setTexture(test1Button);
    test1Sprite.setPosition(sf::Vector2f(32 * (column/2 + 6), 32 * row));
    test2Sprite.setTexture(test2Button);
    test2Sprite.setPosition(sf::Vector2f(32 * (column/2 + 8), 32 * row));
    test3Sprite.setTexture(test3Button);
    test3Sprite.setPosition(sf::Vector2f(32 * (column/2 + 10), 32 * row));
    scoreSprite.setTexture(digits);
    scoreSprite.setPosition(sf::Vector2f(21, 32 * row));
    scoreSprite2.setTexture(digits);
    scoreSprite2.setPosition(sf::Vector2f(42, 32 * row));
    scoreSprite3.setTexture(digits);
    scoreSprite3.setPosition(sf::Vector2f(64, 32 * row));
    scoreSpriteNegative.setTexture(digits);
    scoreSpriteNegative.setPosition(sf::Vector2f(0, 32 * row));
    setupBoard();
}

Board::~Board() 
{
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++) 
        {
            delete tiles[x][y];
        }
    }
}

void Board::drawBoard(sf::RenderWindow& window)
{
    int count = 0;
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {

            Tile* tile = tiles[x][y];
          
            if (showMineMode) 
            {
                window.draw(*tile->getHiddenTileSprite());
                if (tile->isFlagged() && !tile->isRevealed())
                {
                    window.draw(*tile->getFlagSprite());
                }
                if (tile->isMine() || tile->isRevealed()) 
                {
                    window.draw(*tile->getRevealedTileSprite());
                  
                }
                
            }
            else if (lost)
            {
                window.draw(*tile->getHiddenTileSprite());
                if (tile->isRevealed() && tile->isMine())
                {
                    window.draw(*tile->getFlagSprite());
                    window.draw(*tile->getRevealedTileSprite());
                }
                else if (tile->isRevealed())
                {
                    {
                        window.draw(*tile->getRevealedTileSprite());
                    }
                }
                else
                {
                    if (tile->isFlagged())
                    {
                        window.draw(*tile->getFlagSprite());
                    }
                }
            }
            else
            {
                window.draw(*tile->getHiddenTileSprite());
                if (tile->isRevealed())
                {
                    window.draw(*tile->getRevealedTileSprite());
                }
                else
                {
                    if (tile->isFlagged())
                    {
                        window.draw(*tile->getFlagSprite());
                    }
                }

            }
            count++;
            if (count == tileCount)
            {
                y = column;
                x = row;
            }
        }
    }
    remainingMines();
    window.draw(happySprite);
    window.draw(showMineSprite);
    window.draw(test1Sprite);
    window.draw(test2Sprite);
    window.draw(test3Sprite);
    window.draw(scoreSprite);
    window.draw(scoreSprite2);
    window.draw(scoreSprite3);
    window.draw(scoreSpriteNegative);
}

void Board::setupBoard()
{
    int count = 0;
    lost = false;
    won = false;
    flaggedTile = 0;
    tileToWin = tileCount - maxMineCount;
    setSpriteTexture(&happySprite, smileyFace);
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {
           
            tiles[x][y] = new Tile(hiddenTile, flag);
            //tiles[x][y]->setIsFlagged(false);
            tiles[x][y]->moveSprites(y * 32, x * 32);
            count++;
            if (count == tileCount)
            {
                y = column;
                x = row;
            }
        }
    }
    mineCount = 0;
    mineGenerator();
    setAdjacentTiles();
}

void Board::mouseClick(int x, int y, std::string left_right)
{
    if (y > row * 32 && y < row * 32 + 60)
    {
        if (x > ((column/2 + 4) * 32) && x < ((column/2 + 6) * 32) && !won && !lost)
        {
            if (!showMineMode)
            {
                showMineMode = true;
            }
            else
            {
                showMineMode = false;
            }
        }
        if (x > ((column / 2) * 32) && x < ((column / 2 + 2) * 32))
        {
            setupBoard();
        }
        
        if (x > ((column /2 + 6) *32) && x < ((column/2 + 8) * 32))
        {
            loadBoard("boards/testboard1.brd");
        }
       
        if (x > ((column / 2 + 8) * 32) && x < ((column / 2 + 10) * 32))
        {
            loadBoard("boards/testboard2.brd");
        }
        
        if (x > ((column / 2 + 10) * 32) && x < ((column / 2 + 12) * 32))
        {
            loadBoard("boards/testboard3.brd");
        }

    }
   
    else if (y <= row * 32 && !lost && !won) 
    {
        Tile* clickedTile = tiles[y / 32][x / 32];
        if (left_right == "left") {
            if (!clickedTile->isFlagged() && !clickedTile->isRevealed()) 
            {
                handleReveal(clickedTile);
            }
        }
        else if (left_right == "right") 
        {
            flagTile(clickedTile);
        }
    }

}

void Board::flagTile(Tile* tile)
{
    if (!tile->isRevealed())
    {
        if (tile->isFlagged())
        {
            tile->setIsFlagged(false);
            flaggedTile--;
        }
        else
        {
            tile->setIsFlagged(true);
            flaggedTile++;
        }
    }
}

void Board::handleReveal(Tile* tile)
{
    tile->setIsRevealed(true);
    setSpriteTexture(tile->getHiddenTileSprite(), revealedTile);
   
    if (tile->isMine())
    {
        loseGame();
    }
    else
    {
        tileToWin--;
        if (tile->getAdjMines() == 0)
        {
            std::vector<Tile*>* adjTiles = tile->getAdjTiles();
            for (int i = 0; i < adjTiles->size(); i++)
            {
               
                if (!adjTiles->at(i)->isRevealed())
                {
                    if (!adjTiles->at(i)->isFlagged())
                    {
                        handleReveal(adjTiles->at(i));
                    }
                    else
                    {
                        std::vector<Tile*>* tempTiles = adjTiles->at(i)->getAdjTiles();
                        for (int i = 0; i < tempTiles->size(); i++)
                        {

                            if (!tempTiles->at(i)->isRevealed())
                            {
                                if (!tempTiles->at(i)->isFlagged())
                                {
                                    handleReveal(tempTiles->at(i));
                                }
                            }
                        }
                    }
                }
            }
        }
        if (tileToWin == 0)
        {
            winGame();
        }
    }
}

void Board::setSpriteTexture(sf::Sprite* sprite, sf::Texture& text) 
{
    sprite->setTexture(text);
}

void Board::mineGenerator()
{
    while (mineCount < maxMineCount)
    {
        int randX = Random::Int(0, row-1);
        int randY = Random::Int(0, column-1);
        Tile* randTile = tiles[randX][randY];
        if (!randTile->isMine())
        {
            randTile->setIsMine(true);
            setSpriteTexture(randTile->getRevealedTileSprite(), mine);
            mineCount++;
        }
    }
}

void Board::remainingMines()
{
    int remainingMines = mineCount - flaggedTile;
    int temp = remainingMines;
    if (remainingMines < 0)
    {
        scoreSpriteNegative.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));

        if (remainingMines <= -999)
        {
            scoreSprite.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
        }
        else if (remainingMines < -99)
        {
            temp = -1 * (remainingMines);
            while (temp >= 10)
            {
                temp /= 10;
            }
            scoreSprite.setTextureRect(sf::IntRect(21 * (temp), 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * (-1 * ((remainingMines / 10) % 10)), 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (-1 * (remainingMines % 10)), 0, 21, 32));
        }
        else if (remainingMines >= -99 && remainingMines < -9)
        {
            scoreSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * (-1 * (remainingMines / 10)), 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (-1 * (remainingMines % 10)), 0, 21, 32));
        }
        else if (remainingMines >= -9)
        {
            scoreSprite.setTextureRect(sf::IntRect(0, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(0, 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (-1 * (remainingMines % 10)), 0, 21, 32));
        }
    }
    else
    {
        scoreSpriteNegative.setTextureRect(sf::IntRect(21 * 10, 0, 0, 0));
        if (remainingMines >= 999)
        {
            scoreSprite.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
        }
        else if (remainingMines >= 100)
        {
            temp = remainingMines;
            while (temp >= 10)
            {
                temp /= 10;
            }
            scoreSprite.setTextureRect(sf::IntRect(21 * (temp), 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * ((remainingMines / 10) % 10), 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (remainingMines % 10), 0, 21, 32));
        }
        else if (remainingMines >= 10)
        {
            scoreSprite.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * (remainingMines / 10), 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (remainingMines % 10), 0, 21, 32));
        }
        else if (remainingMines <= 9)
        {
            scoreSprite.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
            scoreSprite2.setTextureRect(sf::IntRect(21 * 0, 0, 21, 32));
            scoreSprite3.setTextureRect(sf::IntRect(21 * (remainingMines % 10), 0, 21, 32));
        }
       
    }
} 

void Board::setAdjacentTiles()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            std::vector<Tile*> adjTile;
            Tile* tempTile;
            if (i - 1 >= 0)
            {
                if (j + 1 < column)
                {
                    tempTile = tiles[i - 1][j + 1];
                    adjTile.push_back(tempTile);
                }
                if (j - 1 >= 0)
                {
                    tempTile = tiles[i - 1][j - 1];
                    adjTile.push_back(tempTile);
                }
                tempTile = tiles[i - 1][j];
                adjTile.push_back(tempTile);
            }
            if (i + 1 < row)
            {
                if (j + 1 < column)
                {
                    tempTile = tiles[i + 1][j + 1];
                    adjTile.push_back(tempTile);
                }
                if (j - 1 >= 0)
                {
                    tempTile = tiles[i + 1][j - 1];
                    adjTile.push_back(tempTile);
                }
                tempTile = tiles[i + 1][j];
                adjTile.push_back(tempTile);
            }
            if (j + 1 < column)
            {
                tempTile = tiles[i][j + 1];
                adjTile.push_back(tempTile);
            }
            if (j - 1 >= 0)
            {
                tempTile = tiles[i][j - 1];
                adjTile.push_back(tempTile);
            }
            tempTile = tiles[i][j];
            
            tempTile->setAdjTiles(adjTile);
            if (!tempTile->isMine())
            {
                if (tempTile->getAdjMines() == 0)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), revealedTile);
                }
                else if (tempTile->getAdjMines() == 1)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number1);
                }
                else if (tempTile->getAdjMines() == 2)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number2);
                }
                else if (tempTile->getAdjMines() == 3)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number3);
                }
                else if (tempTile->getAdjMines() == 4)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number4);
                }
                else if (tempTile->getAdjMines() == 5)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number5);
                }
                else if (tempTile->getAdjMines() == 6)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number8);
                }
                else if (tempTile->getAdjMines() == 7)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number7);
                }
                else if (tempTile->getAdjMines() == 8)
                {
                    setSpriteTexture(tempTile->getRevealedTileSprite(), number8);
                }
                
            }
        }
    }
}

void Board::winGame()
{
    won = true;
    flaggedTile = mineCount;
    setSpriteTexture(&happySprite, wonFace);
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {
            if (tiles[x][y]->isMine())
            {
                tiles[x][y]->setIsFlagged(true);
            }
        }
    }
}

void Board::loseGame()
{
    lost = true;

    setSpriteTexture(&happySprite, lostFace);
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {
            if (tiles[x][y]->isMine())
            {
                tiles[x][y]->setIsFlagged(true);
                setSpriteTexture(tiles[x][y]->getHiddenTileSprite(), revealedTile);
                tiles[x][y]->setIsRevealed(true);
            }
        }
    }
}

void Board::loadBoard(std::string boardFile)
{
    flaggedTile = 0;
    lost = false;
    won = false;
    mineCount = 0;
    setSpriteTexture(&happySprite, smileyFace);
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {

            tiles[x][y] = new Tile(hiddenTile, flag);
            tiles[x][y]->moveSprites(y * 32, x * 32);
        }
    }
    std::string line;
    std::ifstream boardStream(boardFile);
    std::vector<std::string> storageVec;
    if (boardStream.is_open())
    {
        while (std::getline(boardStream, line))
        {
            storageVec.push_back(line);
        }
    }
    for (int x = 0; x < row; x++)
    {
        for (int y = 0; y < column; y++)
        {
            tiles[x][y]->setIsRevealed(false);
           
            if (storageVec[x][y] == '0')
            {
                tiles[x][y]->setIsMine(false);
                setSpriteTexture(tiles[x][y]->getRevealedTileSprite(), revealedTile);
            }
            else if (storageVec[x][y] == '1')
            {
              
                tiles[x][y]->setIsMine(true);
                setSpriteTexture(tiles[x][y]->getRevealedTileSprite(), mine);
                mineCount++;
            }
           
        }
    }
    tileToWin = tileCount - mineCount;
    setAdjacentTiles();

    
}

