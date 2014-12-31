#include "AnimationManager.hpp"

AnimationManager::AnimationManager(TextureManager& texturemanager)
	:mTexutureManager(texturemanager)
{


}

AnimationManager::~AnimationManager()
{


}

void AnimationManager::loadAnimations(std::vector<sf::Sprite>& animVec, const std::string& animName, const size_t animCount)
{
	for (size_t i = 1; i < animCount + 1; ++i)
	{
		std::string tempString = animName + std::to_string(i);
		sf::Sprite tempSprite = mTexutureManager.getSpriteRef(tempString);
		tempSprite.setScale(3.0f, 3.0f);
		animVec.push_back(tempSprite);
	}

}
