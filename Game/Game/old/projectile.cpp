#include "projectile.hpp"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::shoot(sf::Vector2f position, float speed, std::vector<sf::Sprite> animations)
{
	//this->mGameObjectSprite = &mAnimationSprites[0];
	//this->mAnimationSprites[0].setPosition(position);
	//this->setPosition(position);
	//this->mSpeed = speed;
	//this->mAnimationSprites = animations;
	for (std::vector<int>::size_type i = 0; i != animations.size(); ++i)
	{
		mAnimationSprites.push_back(animations[i]);
	}
	this->mGameObjectSprite = &mAnimationSprites[0];
	this->setPosition(20.0f,5.0f);
	std::cout << this->getPosition().x << "  -  " << this->getPosition().y << std::endl;
	for (int i = 0; i < mAnimationSprites.size(); ++i)
	{
		this->mAnimationSprites[i].setPosition(this->getPosition());
	}
}

void Projectile::animate(sf::Time elapsedTime)
{
	mElapsedTime += elapsedTime;
	float offset = this->getPosition().y + 20.0f;
	sf::Vector2f movement(this->getPosition().x, offset);
	mAnimationSprites[0].move(movement * elapsedTime.asSeconds());
	//if (mElapsedTime >= sf::seconds(0.5f))
	//{
	//	mAnimationCount++;
	//	if (mAnimationCount == 3)
	//	{
	//		mAnimationCount = 0;
	//	}

	//	this->mAnimationSprites[mAnimationCount].setPosition(this->getPosition());
	//	this->mGameObjectSprite = &mAnimationSprites[mAnimationCount];
	//	mElapsedTime -= sf::seconds(0.5f);
	//}
	
}

