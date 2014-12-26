#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"

class Player : public sf::Transformable
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	sf::Sprite getSpriteRef();
	void animateSpirte(sf::Time timeSinceLastUpdate);
	void handleMovement(sf::Time timeSinceLastUpdate, Game game);
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);


private:
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
	

	bool					mIsMovingUp;
	bool					mIsMovingDown;
	bool					mIsMovingRight;
	bool					mIsMovingLeft;
	bool					mIsColliding;

};



#endif // PALYER_HPP