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


private:
	void					processEvents();
	void					update(sf::Time elapsedTime);
	void					render();
	void					updateStatistics(sf::Time elapsedTime);
	void					handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	bool					collisionDetection(sf::Sprite testSprite);

private:
	static const float		PlayerSpeed;
	static const float		CameraSpeed;
	static const sf::Time	TimePerFrame;
	float					mScrollingSpeed;

	sf::RenderWindow		mWindow;
	sf::Texture				mTexture;
	sf::Sprite				mPlayer;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	sf::View				mWorldView;




	std::size_t				mStatisticsNumFrames;

	TextureManager			mTextureManager;
	TileMap					mTileMap;
	Player					mPlayer1;
	PlayerStats				mPlayerStats;



	std::vector<std::vector<Tile>> mCollisionSprites;
};


#endif // GAME_HPP