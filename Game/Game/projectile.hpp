#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Projectile : public GameObject
{
public:
	Projectile(std::vector<sf::Sprite> animations);
	~Projectile();
	void		animate(sf::Time elapsedTime);
	void		shoot(sf::Vector2f position, float speed);

private:
	std::vector<sf::Sprite> mAnimationSprites;
	float mSpeed;
	size_t mAnimationCount;
	
};


#endif // PROJECTILE_HPP