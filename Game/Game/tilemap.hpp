#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <string>

#include <SFML/Graphics.hpp>

class TileMap{

public:


	TileMap();

	~TileMap();

	bool loadTileMap();


private:
	sf::VertexArray m_vertices;
	sf::Texture	tileMapTexture;
	int width;
	int height;
};



#endif // TILEMAP_HPP
