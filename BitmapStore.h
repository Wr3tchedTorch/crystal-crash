#pragma once
#include <unordered_map>
#include <SFML/Graphics/Texture.hpp>
#include <string>

class BitmapStore
{
private:
	std::unordered_map<std::string, sf::Texture> m_Textures;

	static bool Instantiated;

public:
	BitmapStore();
	sf::Texture& getTexture(const std::string& filepath);
};

