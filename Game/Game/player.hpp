#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Projectile.hpp"

class Player : public GameObject
{
public:
	Player::Player(TextureManager& texturemanager);
	Player::~Player();
	std::string getTileType() const;
	sf::Sprite getSpriteToDraw() const;
	void update(sf::Time timeSinceLastUpdate, PlayerStats stats);
	void shoot(sf::Time timeSinceLastUpdate);
	std::vector<Projectile>& getProjectiles();
	void removeProjectile(float i);
private:
	PlayerStats* playerStats;
	int mPlayerHealth;
	TextureManager mTexutureManager;
	AnimationManager anim;
	static const float		PlayerSpeed;
	std::vector<sf::Sprite> mAnimationSpritesUp;
	std::vector<sf::Sprite> mAnimationSpritesProjectile;
	std::vector<Projectile> mProjectiles;
	size_t mCurrentAnimSprite;
	sf::Time shootRate;
	sf::Time shootLength;
	sf::Time shootElapsedTime;
	


};



#endif // PLAYER_HPP