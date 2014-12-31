#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "projectile.hpp"

class Player : public GameObject
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	void update(sf::Time timeSinceLastUpdate, PlayerStats stats);
	void shoot(sf::Time timeSinceLastUpdate, Projectile projectile);
	std::vector<Projectile> mProjectiles;
private:
	PlayerStats* playerStats;
	int mPlayerHealth;
	TextureManager mTexutureManager;
	AnimationManager anim;
	static const float		PlayerSpeed;
	std::vector<sf::Sprite> mAnimationSpritesUp;
	std::vector<sf::Sprite> mAnimationSpritesDown;
	std::vector<sf::Sprite> mAnimationSpritesLeft;
	std::vector<sf::Sprite> mAnimationSpritesRight;
	std::vector<sf::Sprite> mProjectilesSprites;
	
	Projectile* mCurrentProjectile;
	void loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t animCount);
	size_t mCurrentAnimSprite;
	
	


};



#endif // PALYER_HPP