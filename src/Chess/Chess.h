#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureLoader.h"
#include "IGameObject.h"

#include "AssetPath.h"

enum ChessType
{
  king = 0,
  queen,
  rook,
  knight,
  bishop,
  pawn
};

enum ChessColor
{
    black = 0,
    white
};

class Chess : public Engine::IGameObject
{
private:
    sf::Sprite m_sprite;
    sf::Texture m_texture;

private:
    sf::Vector2f m_mousePosition;

private:
    ChessType m_type;
    ChessColor m_color;

public:
    ChessType getType();
    ChessColor getColor();
    void setType(ChessType, ChessColor = white);

public:
    void start();

public:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

public:
    Chess(ChessType = pawn, ChessColor = white);
};
