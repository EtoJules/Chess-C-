#include "Chess.h"

void Chess::start()
{
    TextureLoader textureLoader(ASSET_CHESS_PAHT);

    textureLoader.load(m_texture, sf::IntRect(64 * m_type, 64 * m_color, 64, 64));

    m_sprite.setTexture(m_texture);
    m_sprite.setScale(1.1, 1.1);
}

void Chess::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}

Chess::Chess(ChessType type, ChessColor color)
{
    m_type = type;
    m_color = color;
}

ChessType Chess::getType()
{
    return m_type;
}

ChessColor Chess::getColor()
{
    return m_color;
}

void Chess::setType(ChessType type, ChessColor color)
{
    m_type = type;
    m_color = color;
}