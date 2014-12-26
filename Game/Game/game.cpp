#include "game.hpp"
#include "StringHelper.hpp"
#include <iostream>


const float Game::CameraSpeed = -10.0f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

/*
---
Antidmg buff
unverwundbar
heal
timeslow
speed debuff, sollte man nicht einsammeln
täuschung wie in darksouls , mimic kiste
*/


Game::Game()
	: mWindow(sf::VideoMode(640, 800), "Infinite Runner", sf::Style::Close)
	, mTexture()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mWorldView(sf::FloatRect(0, 0, 640, 680))
	, mScrollingSpeed(-0)
	, mTileMap(mWindow.getSize(),mTextureManager)
	, mPlayer1(mTextureManager)
	, mIsColliding(false)
{


	mPlayer1.getSpriteRef().setPosition(100.f, 100.f);
	mPlayer1.getSpriteRef().setScale(4, 4);
	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);
	mStatisticsText.setColor(sf::Color(0, 255, 255));
	mWorldView.setCenter(mWorldView.getCenter().x, 0.0f);
}







void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		updateStatistics(elapsedTime);
		render();
	}
}





void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			mPlayer1.handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			mPlayer1.handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}








//Pass time to calculate frame independent movement speed
void Game::update(sf::Time elapsedTime)
{
	mPlayer1.handleMovement(elapsedTime);
	mPlayer1.animateSpirte(elapsedTime);
	mTileMap.updateTileMap(mWorldView.getCenter().y);
	

	mWorldView.move(0.0f, -2);
	mStatisticsText.move(0.0f, -2);
}



bool Game::collisionDetection(sf::Sprite testSprite)
{
	sf::Sprite inSprite = testSprite;
	mCollisionSprites = mTileMap.getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != mCollisionSprites.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != mCollisionSprites[i].size(); j++)
		{
			mIsColliding = Collision::PixelPerfectTest(inSprite, mCollisionSprites[i][j].getSpriteRef());
			
			if (mIsColliding == true){

				if (mCollisionSprites[i][j].getTileType() == "Wall")
				{
					mPlayer1.getSpriteRef().setColor(sf::Color(255, 0, 0, 255));

					//sf::Vector2f pushDir = (mPlayer.getPosition() - mCollisionSprites[i][j].getSpriteRef().getPosition());

					//mPlayer.move(pushDir);
				}
				return true;
			}
			else
			{
				mPlayer1.getSpriteRef().setColor(sf::Color(0, 255, 0, 255));
				
			}
		}
	}
	return false;
}




void Game::render()
{	
	mWindow.clear();
	mWindow.setView(mWorldView);
	std::vector<std::vector<Tile>> tileMap = mTileMap.getSpritesToDraw();
	for (std::vector<int>::size_type i = 0; i != tileMap.size(); ++i)
	{
		for (std::vector<int>::size_type j = 0; j != tileMap[i].size(); ++j)
		{
			mWindow.draw(tileMap[i][j].getSpriteRef());
		}
	}


	mWindow.draw(mPlayer1.getSpriteRef());
	mWindow.draw(mStatisticsText);
	mWindow.display();
}




void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}


