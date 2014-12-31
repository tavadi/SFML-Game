#include "player.hpp"
const float Player::PlayerSpeed = 600.0f;

Player::Player(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
	, anim(texturemanager)
{
	anim.loadAnimations(mAnimationSpritesUp, "PlayerUp", 3);
	//anim.loadAnimations(mAnimationSpritesRight, "PlayerRight", 3);
	//anim.loadAnimations(mAnimationSpritesDown, "PlayerDown", 3);
	anim.loadAnimations(mProjectilesSprites, "Projectile", 3);
	mCurrentProjectile = new Projectile(mProjectilesSprites);
	this->mGameObjectSprite = &mAnimationSpritesUp[0];
}

void Player::loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t numberofSprites)
{
	for (size_t i = 1; i < numberofSprites + 1; ++i)
	{
		std::string tempString = animName + std::to_string(i);
		sf::Sprite tempSprite = mTexutureManager.getSpriteRef(tempString);
		tempSprite.setScale(3.0f, 3.0f);
		animVec.push_back(tempSprite);
	}

}

Player::~Player()
{
	
}


void Player::shoot(sf::Time timeSinceLastUpdate, Projectile projectile)
{
		projectile.shoot(this->getPosition(), 10.0f);
		mProjectiles.push_back(projectile);
		std::cout << "Shooting" << std::endl;
}

//TODO: FIX: figur bewegt sich nicht weil die jeweiligen sprites ihre eigene position haben

void Player::update(sf::Time timeSinceLastUpdate,PlayerStats stats)
{
	for (std::vector<int>::size_type i = 0; i != mProjectiles.size(); i++)
	{
		mProjectiles[i].animate(timeSinceLastUpdate);
	}
	mElapsedTime += timeSinceLastUpdate;
	static int UpSideAnimCounter = 1;
	
	//Movement
	if (stats.isAlive == true && 
		(stats.mIsMovingDown == true ||
		stats.mIsMovingLeft == true ||
		stats.mIsMovingUp == true ||
		stats.mIsMovingRight == true))
	{
		if (mCurrentAnimSprite == 2){
			UpSideAnimCounter = -1;
		}
		else if (mCurrentAnimSprite == 0)
		{
			UpSideAnimCounter = 1;
		}
		if (mElapsedTime >= sf::seconds(0.20f))
		{
			mCurrentAnimSprite += UpSideAnimCounter;
			this->mGameObjectSprite = &mAnimationSpritesUp[mCurrentAnimSprite];
			mElapsedTime -= sf::seconds(0.20f);
		}
	}
	mAnimationSpritesUp[mCurrentAnimSprite].setPosition(this->getPosition());

	//Shooting
	static sf::Time shootElapsedTime;
	shootElapsedTime += timeSinceLastUpdate;
	if (stats.isShooting == true && shootElapsedTime >= sf::seconds(0.5f))
	{
		this->shoot(timeSinceLastUpdate, *mCurrentProjectile);
		shootElapsedTime -= shootElapsedTime;
	}

}




