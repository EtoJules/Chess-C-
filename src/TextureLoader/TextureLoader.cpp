#include "TextureLoader.h"

void TextureLoader::load(sf::Texture &texture, sf::IntRect rect) 
{
    if (!texture.loadFromFile(m_filePath, rect))
    {
        system("pause");
    }
}

TextureLoader::TextureLoader(std::string filePath) 
{
    m_filePath = filePath;
}