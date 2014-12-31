#ifndef AnimationManager_HPP
#define AnimationManager_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"


class AnimationManager
{
public:
	AnimationManager(TextureManager& texturemanager);

	~AnimationManager();
	

	void loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t animCount);
	void playAnimation(sf::Time elapsedTime);

private:
	TextureManager mTexutureManager;
	sf::Sprite* mGameObjectSprite;
};


#endif // AnimationManager_HPP