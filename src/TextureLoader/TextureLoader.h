#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class TextureLoader
{
private:
    std::string m_filePath;

public:
    void load(sf::Texture &texture, sf::IntRect rect);

public:
    TextureLoader(std::string filePath);
};