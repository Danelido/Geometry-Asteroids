#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class ResourceManager
{

private:
	static std::map<std::string, sf::Texture> textureMap;
	static std::map<std::string, sf::Font> fontMap;


public:
	ResourceManager();
	virtual ~ResourceManager();
	static void addTexture(std::string id, std::string path);
	static void addFont(std::string id, std::string path);
	static sf::Texture& getTexture(std::string id);
	static sf::Font& getFont(std::string id);
	static sf::Image getImage(std::string id);

};

#endif
