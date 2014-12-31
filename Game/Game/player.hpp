#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "playerStats.hpp"
#include "AnimationManager.hpp"
class projectile
{


};




class Player : public sf::Transformable
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	sf::Sprite getSpriteRef();
	void animateSpirte(sf::Time timeSinceLastUpdate, PlayerStats stats);
	void shoot(sf::Time timeSinceLastUpdate, projectile projectile);

private:
	PlayerStats* playerStats;
	sf::Sprite* mPlayerSprite;
	int mPlayerHealth;
	TextureManager mTexutureManager;
	AnimationManager anim;
	static const float		PlayerSpeed;
	std::vector<sf::Sprite> mAnimationSpritesUp;
	std::vector<sf::Sprite> mAnimationSpritesDown;
	std::vector<sf::Sprite> mAnimationSpritesLeft;
	std::vector<sf::Sprite> mAnimationSpritesRight;
	std::vector<sf::Sprite> mProjectiles;
	void loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t animCount);
	sf::Time mElapsedTime;
	size_t mCurrentAnimSprite;
	
	


};



#endif // PALYER_HPP