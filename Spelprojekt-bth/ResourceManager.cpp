#include "ResourceManager.h"


std::map<std::string, sf::Texture> ResourceManager::textureMap;
std::map<std::string, sf::Font> ResourceManager::fontMap;

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

void ResourceManager::addTexture(std::string id, std::string path)
{
	sf::Texture texture;
	if (!texture.loadFromFile(path))
	{
		printf("Couldnt load texture\n");
	}

	textureMap[id] = texture;
}

void ResourceManager::addFont(std::string id, std::string path)
{
	sf::Font font;
	if (!font.loadFromFile(path))
	{
		printf("Couldnt load texture\n");
	}

	fontMap[id] = font;
}

sf::Texture& ResourceManager::getTexture(std::string id)
{
	if (textureMap.find(id) == textureMap.end())
	{
		printf("Couldnt find texture with ID: %s\n", id.c_str());
	}
	return textureMap[id];

}

sf::Font& ResourceManager::getFont(std::string id)
{
	if (fontMap.find(id) == fontMap.end())
	{
		printf("Couldnt find font with ID: %s\n", id.c_str());
	}
	return fontMap[id];
}

sf::Image ResourceManager::getImage(std::string id)
{
	if (textureMap.find(id) == textureMap.end())
	{
		printf("Couldnt find texture with ID: %s\n", id.c_str());
	}
	return textureMap[id].copyToImage();
}
