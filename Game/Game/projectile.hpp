#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Projectile 
{
public:
	Projectile(sf::Sprite sprite, float projectileSpeed, sf::Vector2f position);
	~Projectile();
	sf::Sprite& getSpriteRef();
	void update(sf::Time elapsedTime);
	void setSprite(sf::Sprite sprite);

private:
	sf::Sprite mProjectileSprite;
	float mProjectileSpeed;
	sf::Vector2f posi;
};




#endif // PROJECTILE_HPP