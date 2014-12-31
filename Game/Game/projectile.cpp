#include "projectile.hpp"

Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::shoot(sf::Vector2f position, float rotation, float speed)
{
	this->setPosition(position);
	this->mSpeed = speed;

}

void Projectile::animate(sf::Time elapsedTime)
{
	
}


sf::Sprite Projectile::getSpriteRef()
{
	return *mPorjectileSprite;
}