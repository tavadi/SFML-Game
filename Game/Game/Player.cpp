#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)

{
	const float Player::PlayerSpeed = 600.0f;
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp1"));
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp2"));
	mAnimationSpritesUp.push_back(mTexutureManager.getSpriteRef("PlayerUp3"));
	for (size_t i = 0; i < mAnimationSpritesUp.size(); ++i)
	{
		mAnimationSpritesUp[i].setScale(5.0f, 5.0f);
	}
	this->mPlayerSprite = &mAnimationSpritesUp[0];

}



Player::~Player()
{
	
}

//TODO: FIX: figur bewegt sich nicht weil die jeweiligen sprites ihre eigene position haben

void Player::animateSpirte(sf::Time timeSinceLastUpdate)
{

	mElapsedTime += timeSinceLastUpdate;
	
	static int UpSideAnimCounter = 1;
	
	if (mCurrentAnimSprite == 2){
		UpSideAnimCounter = -1;
	}else 
	if (mCurrentAnimSprite == 0)
	{
		UpSideAnimCounter = 1;
	}

	if (mElapsedTime >= sf::seconds(0.2f))
	{
		mCurrentAnimSprite += UpSideAnimCounter;
		this->mPlayerSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
		mElapsedTime -= sf::seconds(0.2f);
	}

	mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());
}

sf::Sprite Player::getSpriteRef()
{
	return *mPlayerSprite;
}


void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
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


//TODO collisiondetection ist in der falschen klasse ... 
void Player::handleMovement(sf::Time elapsedTime, Game game)
{
	sf::Vector2f realMovement(0.f, 0.f);
	//Handle movement
	if (mIsMovingUp){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mAnimationSpritesUp[mCurrentAnimSprite]);
		movement.y -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (game.collisionDetection(testSprite) == false)
			{
				realMovement.y -= PlayerSpeed;
			}
	}
		
	if (mIsMovingDown){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mAnimationSpritesUp[mCurrentAnimSprite]);
		movement.y += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (game.collisionDetection(testSprite) == false)
		{
			realMovement.y += PlayerSpeed;
		}
	}
		
	if (mIsMovingLeft){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mAnimationSpritesUp[mCurrentAnimSprite]);
		movement.x -= PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (game.collisionDetection(testSprite) == false)
		{
			realMovement.x -= PlayerSpeed;
		}
		

	}
		
	if (mIsMovingRight){
		sf::Vector2f movement(0.f, 0.f);
		sf::Sprite testSprite(mAnimationSpritesUp[mCurrentAnimSprite]);
		movement.x += PlayerSpeed;
		testSprite.move(movement * elapsedTime.asSeconds());
		if (game.collisionDetection(testSprite) == false)
		{
			realMovement.x += PlayerSpeed;
		}
		
	}
	mAnimationSpritesUp[mCurrentAnimSprite].move(realMovement * elapsedTime.asSeconds());
}