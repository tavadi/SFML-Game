#include "game.hpp"
#include "StringHelper.hpp"
#include <iostream>

float Game::PlayerSpeed = 300.0f;
float Game::speedPowerUp = 40.0f;
float Game::CameraSpeed = -4.0f;
float Game::CameraMaxSpeed = -12;
const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);



Game::Game()
	: mWindow(sf::VideoMode(640, 800), "Infinite Runner", sf::Style::Close)
	, mTexture()
	, mPlayer()
	, mFont()
	//, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mScrollingSpeed(-480)
{
	mWorldView = new sf::View(sf::FloatRect(0, 0, 640, 680));
	mPlayer1 = new Player(mTextureManager);
	mTileMap = new TileMap(mWindow.getSize(), mTextureManager);
	mPlayer1->setPosition(250, -200);
	mPlayerStats.isAlive = true;
	mPlayerStats.mIsColliding = false;
	mPlayerStats.mIsMovingDown = false;
	mPlayerStats.mIsMovingUp = false;
	mPlayerStats.mIsMovingLeft = false;
	mPlayerStats.mIsMovingRight = false;
	mPlayerStats.isShooting = false;
	mPlayerStats.wantsToLeave = false;
	mFont.loadFromFile("Sansation.ttf");
	//mStatisticsText.setFont(mFont);
	//mStatisticsText.setPosition(5.f, 5.f);
	//mStatisticsText.setCharacterSize(20);
	//mStatisticsText.setColor(sf::Color(0, 255, 255));
	mWorldView->setCenter(mWorldView->getCenter().x, 0);
	mExplosionSound.loadFromFile("explosion.wav");
	mGotHitSound.loadFromFile("hit.wav");
	mPowerUpShieldSound.loadFromFile("powerupShield.wav");
	mPowerUpSpeedSound.loadFromFile("powerupSpeed.wav");
	mShootSound.loadFromFile("shoot.wav");
	mPlayerDeadSound.loadFromFile("WilhelmScream.wav");

	mSoundPlayer.setVolume(15.0f);
	if (!mBackgroundMusic.openFromFile("backgroundmusic.wav"))
	{
		std::cout << "error while loading backgroundmusic" << std::endl;
	}
	mBackgroundMusic.play();
}

Game::~Game()
{
	delete mPlayer1;
	delete mTileMap;
	delete mWorldView;
}





void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mPlayerStats.wantsToLeave == false)
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		//updateStatistics(elapsedTime);
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

	if (mPlayerStats.isAlive == false)
	{
		mSoundPlayer.setBuffer(mPlayerDeadSound);
		mSoundPlayer.play();
		delete mPlayer1;
		delete mTileMap;
		delete mWorldView;
		mWorldView = new sf::View(sf::FloatRect(0, 0, 640, 680));
		mWorldView->setCenter(mWorldView->getCenter().x, 0);
		mPlayer1 = new Player(mTextureManager);
		mTileMap = new TileMap(mWindow.getSize(), mTextureManager);
		mPlayer1->setPosition(250, -200);
		PlayerSpeed = 300.0f;
		CameraSpeed = -4.0f;
		mPlayerStats.isAlive = true;
		mPlayer1->getSpriteRef().setPosition(0,0);
	
		//mStatisticsText.setPosition(5.f, 5.f);
		mBackgroundMusic.stop();
		mBackgroundMusic.play();
	}


	float posDiffernce = mWorldView->getCenter().y - mPlayer1->getSpriteRef().getPosition().y;
	if (mPlayer1->getHealth() <= 0 || posDiffernce <= -400.0f)
	{
		mPlayerStats.isAlive = false;
		//std::cout << "PLAYER IS DEAD" << std::endl;

	}
	
	if (mTileMap->updateTileMap(mWorldView->getCenter().y, CameraSpeed) == true && CameraSpeed > CameraMaxSpeed)
	{
		CameraSpeed -= 0.5f;
	}

	sf::Vector2f realMovement(0.f, 0.f);
	//Handle movement
	if (mPlayerStats.mIsMovingUp){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1->getSpriteRef());
		movement.y -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (playerCollisionDetection(testSprite, elapsedTime) == false)
		{
			realMovement.y -= PlayerSpeed;
		}
	}

	if (mPlayerStats.mIsMovingDown){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1->getSpriteRef());
		movement.y += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (playerCollisionDetection(testSprite,elapsedTime) == false)
		{
			realMovement.y += PlayerSpeed;
		}
	}
	if (mPlayerStats.mIsMovingLeft){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1->getSpriteRef());
		movement.x -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (playerCollisionDetection(testSprite,elapsedTime) == false)
		{
			realMovement.x -= PlayerSpeed;
		}
	}

	if (mPlayerStats.mIsMovingRight){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mPlayer1->getSpriteRef());
		movement.x += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (playerCollisionDetection(testSprite, elapsedTime) == false)
		{
			realMovement.x += PlayerSpeed;
		}
	}

	std::vector<Projectile> projectiles = mPlayer1->getProjectiles();
	if (projectiles.size() != 0)
	{
		for (std::vector<int>::size_type i = 0; i != projectiles.size(); ++i)
		{
			if (ProjectileCollisionDetection(projectiles[i].getSpriteRef()) == true)
			{
				mPlayer1->removeProjectile(i);
			}
		}
	}
	mPlayer1->move(realMovement * elapsedTime.asSeconds());
	mPlayer1->update(elapsedTime, mPlayerStats);
	mWorldView->move(0.0f, CameraSpeed);
	//mStatisticsText.move(0.0f, CameraSpeed);
}


bool Game::ProjectileCollisionDetection(sf::Sprite testSprite)
{
	sf::Sprite inSprite = testSprite;
	mCollisionSprites = mTileMap->getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != mCollisionSprites.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != mCollisionSprites[i].size(); j++)
		{
			bool test = Collision::PixelPerfectTest(inSprite, mCollisionSprites[i][j].getSpriteRef());
			if (test == true)
			{
				if (mCollisionSprites[i][j].getTileType() == "Wall")
				{
					mSoundPlayer.setBuffer(mExplosionSound);
					mSoundPlayer.play();
					//std::cout << i << std::endl;
					mTileMap->updateTile(i, j, "Ice");
					return true;
				}
				
			}
		}
	}
	return false;

}


bool Game::playerCollisionDetection(sf::Sprite testSprite, sf::Time elapsedTime)
{
	static sf::Time lastTimeHitted;
	lastTimeHitted += elapsedTime;
	sf::Sprite inSprite = testSprite;
	mCollisionSprites = mTileMap->getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != mCollisionSprites.size(); i++)
	{
		for (std::vector<int>::size_type j = 0; j != mCollisionSprites[i].size(); j++)
		{
			mPlayerStats.mIsColliding = Collision::PixelPerfectTest(inSprite, mCollisionSprites[i][j].getSpriteRef());

			if (mPlayerStats.mIsColliding == true){

				if (mCollisionSprites[i][j].getTileType() == "Wall")
				{
					//mPlayer1.getSpriteRef().setColor(sf::Color(255, 0, 0, 255));
					//sf::Vector2f pushDir = (mPlayer.getPosition() - mCollisionSprites[i][j].getSpriteRef().getPosition());
					//mPlayer.move(pushDir);
					if (lastTimeHitted >= sf::seconds(2.0f))
					{
						mTileMap->updateTile(i, j, "Ice");
						mSoundPlayer.setBuffer(mGotHitSound);
						mSoundPlayer.play();
						mPlayer1->removeHealth(10);
						lastTimeHitted -= lastTimeHitted;
						//std::cout << "Player took damage, health left : " << mPlayer1->getHealth() << std::endl;
					}
					
				}
				else if (mCollisionSprites[i][j].getTileType() == "SpeedPowerUp")
				{
				
					mSoundPlayer.setBuffer(mPowerUpSpeedSound);
					mSoundPlayer.play();
					mTileMap->updateTile(i, j, "Ice");
					PlayerSpeed += speedPowerUp;
					mPlayer1->speedUp();
				}
				else if (mCollisionSprites[i][j].getTileType() == "ShieldPowerUp")
				{
					mSoundPlayer.setBuffer(mPowerUpShieldSound);
					mSoundPlayer.play();
					mTileMap->updateTile(i, j, "Ice");
					mPlayer1->addHealth(10);
				}
 				return true;
			}
			else
			{
				mPlayer1->getSpriteRef().setColor(sf::Color(0, 255, 0, 255));

			}
		}
	}
	return false;
}




void Game::render()
{
	mWindow.clear();
	mWindow.setView(*mWorldView);


	std::vector<std::vector<Tile>> tileMap1 = mTileMap->getSpritesToDraw();
	for (std::vector<int>::size_type i = 0; i != tileMap1.size(); ++i)
	{
		for (std::vector<int>::size_type j = 0; j != tileMap1[i].size(); ++j)
		{
			mWindow.draw(tileMap1[i][j].getSpriteRef());
		}
	}

	std::vector<std::vector<Tile>> tileMap2 = mTileMap->getCollisionSprites();
	for (std::vector<int>::size_type i = 0; i != tileMap2.size(); ++i)
	{
		for (std::vector<int>::size_type j = 0; j != tileMap2[i].size(); ++j)
		{
			mWindow.draw(tileMap2[i][j].getSpriteRef());
		}
	}


	std::vector<Projectile> projectiles = mPlayer1->getProjectiles();
	if (projectiles.size() != 0)
	{
		for (std::vector<int>::size_type i = 0; i != projectiles.size(); ++i)
		{
			mWindow.draw(projectiles[i].getSpriteRef());
		}
	}

	mWindow.draw(mPlayer1->getSpriteRef());
	//mWindow.draw(mStatisticsText);
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
		mPlayerStats.mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mPlayerStats.mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mPlayerStats.mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mPlayerStats.mIsMovingRight = isPressed;
	else if (key == sf::Keyboard::Space)
		mPlayerStats.isShooting = isPressed;
	else if (key == sf::Keyboard::Escape)
		mPlayerStats.wantsToLeave = true;
}