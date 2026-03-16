#include "BitmapStore.h"
#include <cassert>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <format>

bool BitmapStore::Instantiated = false;
const std::string BitmapStore::PlaceholderGraphicsFilepath = "graphics/placeholder.png";

BitmapStore::BitmapStore()
{
    assert(!Instantiated);
    Instantiated = true;    
}

sf::Texture& BitmapStore::getTexture(const std::string& filepath)
{
    auto search = m_Textures.find(filepath);

    if (search == m_Textures.end())
    {
        bool result = m_Textures[filepath].loadFromFile(filepath);

#ifdef _DEBUG
        if (!result)
        {
            std::cout << std::format("[BitmapStore - 27] Texture not found for filepath: {}", filepath);
        }
#endif // _DEBUG
    }

    return m_Textures[filepath];
}
