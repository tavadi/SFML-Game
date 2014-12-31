#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "playerStats.hpp"
#include "AnimationManager.hpp"


class GameObject : public sf::Transformable
{
public:
	sf::Sprite* mGameObjectSprite;
	sf::Sprite getSpriteRef();
	sf::Time mElapsedTime;
	
};
#endif // GAMEOBJECT_HPP