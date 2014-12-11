#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"


class Player
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	sf::Sprite& getSpriteRef();
	void animateSpirte(sf::Time timeSinceLastUpdate);


private:
	sf::Sprite mPlayerSprite;
	int mPlayerHealth;
	TextureManager mTexutureManager;
	std::vector<sf::Sprite> mAnimationSpritesUp;
	std::vector<sf::Sprite> mAnimationSpritesDown;
	std::vector<sf::Sprite> mAnimationSpritesLeft;
	std::vector<sf::Sprite> mAnimationSpritesRight;
	sf::Time mElapsedTime;
	size_t mCurrentAnimSprite;

};



#endif // PALYER_HPP