#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "TextureManager.hpp"
#include "TileMap.hpp"
#include "Collision.h"


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
	void					collisionDetection();

private:
	static const float		PlayerSpeed;
	static const sf::Time	TimePerFrame;

	sf::RenderWindow		mWindow;
	sf::Texture				mTexture;
	sf::Sprite				mPlayer;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;




	std::size_t				mStatisticsNumFrames;
	bool					mIsMovingUp;
	bool					mIsMovingDown;
	bool					mIsMovingRight;
	bool					mIsMovingLeft;
	bool					mIsColliding;
	TileMap					mTileMap;


	std::vector<Tile> mCollisionSprites;
};


#endif // GAME_HPP