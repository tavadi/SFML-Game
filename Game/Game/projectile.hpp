#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "AnimationManager.hpp"


class Projectile : public sf::Transformable
{
public:
	Projectile();
	~Projectile();
	void		animate(sf::Time elapsedTime);
	void		shoot(sf::Vector2f position, float rotation, float speed);

private:
	sf::Sprite* mPorjectileSprite;
	std::vector<sf::Sprite> mAnimationSprites;
	sf::Sprite getSpriteRef();
	float mSpeed;
	
};


#endif // PALYER_HPP