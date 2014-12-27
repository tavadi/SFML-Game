#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "playerStats.hpp"

class Player : public sf::Transformable
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	sf::Sprite getSpriteRef();
	void animateSpirte(sf::Time timeSinceLastUpdate, PlayerStats stats);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


private:
	PlayerStats* playerStats;
	sf::Sprite* mPlayerSprite;
	int mPlayerHealth;
	TextureManager mTexutureManager;
	static const float		PlayerSpeed;
	std::vector<sf::Sprite> mAnimationSpritesUp;
	std::vector<sf::Sprite> mAnimationSpritesDown;
	std::vector<sf::Sprite> mAnimationSpritesLeft;
	std::vector<sf::Sprite> mAnimationSpritesRight;
	sf::Time mElapsedTime;
	size_t mCurrentAnimSprite;
	


};



#endif // PALYER_HPP