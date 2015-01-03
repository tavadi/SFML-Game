#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();
	void		animate(sf::Time elapsedTime);
	void		shoot(sf::Vector2f position, float speed, std::vector<sf::Sprite> animations);
	std::vector<sf::Sprite> mAnimationSprites;
private:

	float mSpeed;
	size_t mAnimationCount;
	
};


#endif // PROJECTILE_HPP