#include "game.hpp"
#include "StringHelper.hpp"
#include <iostream>

const float Game::PlayerSpeed = 400.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(1920,1400), "SFML Game", sf::Style::Close)
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
	, mTileMap(mWindow.getSize())
{
	if (!mTexture.loadFromFile("testchar.png"))
	{
		// Handle loading error
	}

	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);

	mFont.loadFromFile("Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
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
}











void Game::render()
{	
	mWindow.clear();
	mWindow.draw(mTileMap);
	mWindow.draw(mPlayer);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}









void Game::updateStatistics(sf::Time elapsedTime)
{



	//handle collision
	std::vector<sf::Sprite> mCollisionSprites = mTileMap.getCollisionSprites();

	bool collision = false;
	for (unsigned int i = 0; i < mCollisionSprites.size(); ++i)
	{
		collision = Collision::CircleTest(mPlayer, mCollisionSprites[i]);
		if (collision == true){
			mPlayer.setColor(sf::Color(255, 0, 0, 255));

			std::cout << "COLLIOSN" << std::endl;

		}

		
		
	}



	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
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