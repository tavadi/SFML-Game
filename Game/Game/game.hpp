#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "Collision.h"
#include "player.hpp"


class Game : private sf::NonCopyable
{ 
public:
	Game();
	void					run();
	bool					collisionDetection(sf::Sprite testSprite);

private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();

	void					updateStatistics(sf::Time elapsedTime);


private:

	static const float		CameraSpeed;
	static const sf::Time	TimePerFrame;
	float					mScrollingSpeed;

	sf::RenderWindow		mWindow;
	sf::Texture				mTexture;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	sf::View				mWorldView;
	bool					mIsColliding;



	std::size_t				mStatisticsNumFrames;

	TextureManager			mTextureManager;
	TileMap					mTileMap;
	Player					mPlayer1;
	


	std::vector<std::vector<Tile>> mCollisionSprites;
};


#endif // GAME_HPP