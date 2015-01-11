#include "projectile.hpp"




Projectile::Projectile(sf::Sprite sprite, float projectileSpeed, sf::Vector2f position)
	: mProjectileSpeed(projectileSpeed)
	, posi(position)
{

	sprite.setScale(2.0f,2.0f);
	sprite.setPosition(position);
	this->setSprite(sprite);

}

Projectile::~Projectile()
{
}

sf::Sprite& Projectile::getSpriteRef()
{
	return this->mProjectileSprite;
}


void Projectile::update(sf::Time elapsedTime)
{
	static sf::Time timePassed;
	static sf::Time aliveTime;
		timePassed += elapsedTime;
		aliveTime += elapsedTime;
		sf::Vector2f movement(0, mProjectileSpeed);
		mProjectileSprite.move(movement * elapsedTime.asSeconds());
		if (timePassed >= sf::seconds(1.0f))
		{

			timePassed -= sf::seconds(1.0f);
		}
}



void Projectile::setSprite(sf::Sprite sprite)
{
	this->mProjectileSprite = sprite;
}