#include "game.hpp"
#include "StringHelper.hpp"
#include <iostream>

const float Game::PlayerSpeed = 300.0f;
const float Game::CameraSpeed = -0.0f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

/*
---
Antidmg buff
unverwundbar
heal
timeslow
speed debuff, sollte man nicht einsammeln
t�uschung wie in darksouls , mimic kiste
*/


Game::Game()
	: mWindow(sf::VideoMode(640, 800), "Infinite Runner", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mWorldView(sf::FloatRect(0, 0, 640, 680))
	, mScrollingSpeed(-480)
	, mTileMap(mWindow.getSize(), mTextureManager)
	, mPlayer1(mTextureManager)
{


	mPlayer1.getSpriteRef().setPosition(100.f, 100.f);
	mPlayer1.getSpriteRef().setScale(4, 4);
	mPlayerStats.isAlive = false;
	mPlayerStats.mIsColliding = false;
	mPlayerStats.mIsMovingDown = false;
	mPlayerStats.mIsMovingUp = false;
	mPlayerStats.mIsMovingLeft = false;
	mPlayerStats.mIsMovingRight = false;
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
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
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
	mTileMap.updateTileMap(mWorldView.getCenter().y);
	sf::Vector2f realMovement(0.f, 0.f);
	//Handle movement
	
	if (mPlayerStats.mIsMovingUp){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1.getSpriteRef());
		movement.y -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (collisionDetection(testSprite) == false)
		{
			realMovement.y -= PlayerSpeed;
		}
	}

	if (mPlayerStats.mIsMovingDown){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1.getSpriteRef());
		movement.y += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (collisionDetection(testSprite) == false)
		{
			realMovement.y += PlayerSpeed;
		}
	}

	if (mPlayerStats.mIsMovingLeft){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1.getSpriteRef());
		movement.x -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (collisionDetection(testSprite) == false)
		{
			realMovement.x -= PlayerSpeed;
		}
	}

	if (mPlayerStats.mIsMovingRight){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1.getSpriteRef());
		movement.x += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (collisionDetection(testSprite) == false)
		{
			realMovement.x += PlayerSpeed;
		}
	}
	mPlayer1.move(realMovement * elapsedTime.asSeconds());
	mPlayer1.animateSpirte(elapsedTime, mPlayerStats);
	mWorldView.move(0.0f, CameraSpeed);
	mStatisticsText.move(0.0f, CameraSpeed);


}



bool Game::collisionDetection(sf::Sprite testSprite)
{
	sf::Sprite inSprite = testSprite;
	mCollisionSprites = mTileMap.getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != mCollisionSprites.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != mCollisionSprites[i].size(); j++)
		{
			mPlayerStats.mIsColliding = Collision::PixelPerfectTest(inSprite, mCollisionSprites[i][j].getSpriteRef());

			if (mPlayerStats.mIsColliding == true){

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


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mPlayerStats.mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mPlayerStats.mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mPlayerStats.mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mPlayerStats.mIsMovingRight = isPressed;
}