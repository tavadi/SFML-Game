#include "game.hpp"
#include "StringHelper.hpp"
#include <iostream>

const float Game::PlayerSpeed = 700.0f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

/*



---
Antidmg buff
unverwundbar
heal
timeslow
speed debuff, sollte man nicht einsammeln

tšuschung wie in darksouls , mimic kiste

*/


Game::Game()
	: mWindow(sf::VideoMode(640, 800), "SFML Game", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
	, mIsColliding(false)
	, mWorldView(sf::FloatRect(0, 0, 640, 720))
	, mScrollingSpeed(-480)
	, mTileMap(mWindow.getSize())
{

	if (!mTexture.loadFromFile("testchar.png"))
	{
		std::cout << "Could not load TestChar1" << std::endl;
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);
	mPlayer.setScale(0.5, 0.5);
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
	while (mWindow.pollEvent(event)) // 
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

	//Handle movement
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= PlayerSpeed;
	if (mIsMovingDown)
		movement.y += PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= PlayerSpeed;
	if (mIsMovingRight)
		movement.x += PlayerSpeed;

	mPlayer.move(movement * elapsedTime.asSeconds());
	mWorldView.move(0.0f,-10);
	mStatisticsText.move(0.0f, -10);

	collisionDetection();
}



void Game::collisionDetection()
{
	mCollisionSprites = mTileMap.getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != mCollisionSprites.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != mCollisionSprites[i].size(); j++)
		{
			mIsColliding = Collision::PixelPerfectTest(mPlayer, mCollisionSprites[i][j].getSpriteRef());
			
			if (mIsColliding == true){

				if (mCollisionSprites[i][j].getTileType() == "Wall")
				{
					mPlayer.setColor(sf::Color(255, 0, 0, 255));

					sf::Vector2f pushDir = (mPlayer.getPosition() - mCollisionSprites[i][j].getSpriteRef().getPosition());

					mPlayer.move(pushDir);
				}
				break;
			}
			else
			{
				mPlayer.setColor(sf::Color(0, 255, 0, 255));
			}
		}
	}
}




void Game::render()
{	
	mWindow.clear();
	mWindow.setView(mWorldView);
	mWindow.draw(mTileMap);
	mWindow.draw(mPlayer);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}




void Game::updateStatistics(sf::Time elapsedTime)
{
	//mStatisticsUpdateTime += elapsedTime;
	//mStatisticsNumFrames += 1;
	//if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	//{
	//	mStatisticsText.setString(
	//		"Frames / Second = " + toString(mStatisticsNumFrames) + "\n");

	//	mStatisticsUpdateTime -= sf::seconds(1.0f);
	//	mStatisticsNumFrames = 0;
	//}
}


void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}