#ifndef TextureManager_HPP
#define TextureManager_HPP

#include <SFML/Graphics.hpp>



class TextureManager
{
public:
	TextureManager();
	~TextureManager();
	bool LoadTextures();
	sf::Sprite& getRef(const std::string& texture);
	std::map<std::string, sf::Sprite> getTiles() const; 

private:
	sf::Texture mTileSet;
	std::map<std::string, sf::Sprite> mTileSpirtes;
};


#endif // TextureManager_HPP