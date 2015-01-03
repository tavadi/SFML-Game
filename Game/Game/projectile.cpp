#include "projectile.hpp"




Projectile::Projectile(sf::Sprite sprite, float projectileSpeed, sf::Vector2f position)
	: mProjectileSpeed(projectileSpeed)
	, posi(position)
{
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
	timePassed += elapsedTime;
	if (timePassed >= sf::seconds(1.0f))
	{
		std::cout << "ASD" << std::endl;
		mProjectileSprite.setPosition(posi.x,mProjectileSprite.getPosition().y + 10);
		timePassed -= sf::seconds(1.0f);
	}

}



void Projectile::setSprite(sf::Sprite sprite)
{
	this->mProjectileSprite = sprite;
}