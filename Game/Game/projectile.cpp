#include "projectile.hpp"

Projectile::Projectile(std::vector<sf::Sprite> animations)
	:mAnimationSprites(animations)
{
	this->mGameObjectSprite = &mAnimationSprites[0];
}

Projectile::~Projectile()
{
}

void Projectile::shoot(sf::Vector2f position, float speed)
{
	this->mGameObjectSprite = &mAnimationSprites[0];
	this->mAnimationSprites[0].setPosition(position);
	this->setPosition(position);
	this->mSpeed = speed;
}

void Projectile::animate(sf::Time elapsedTime)
{
	mElapsedTime += elapsedTime;
	if (mElapsedTime >= sf::seconds(0.5f))
	{
		mAnimationCount++;
		if (mAnimationCount == 3)
		{
			mAnimationCount = 0;
		}
		this->mAnimationSprites[mAnimationCount].setPosition(this->getPosition());
		this->mGameObjectSprite = &mAnimationSprites[mAnimationCount];
		mElapsedTime -= sf::seconds(0.5f);
	}
}

