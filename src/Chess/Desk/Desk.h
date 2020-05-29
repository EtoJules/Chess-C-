#pragma once

#include "IGameObject.h"
#include "Cell.h"
#include "Chess.h"

class Desk : public Engine::IGameObject
{
private:
    Cell<Chess> m_cell[8][8];

public:
    void start();

public:
    sf::Vector2f getCellPosition(int, CellChar);
    Cell<Chess> &getCell(int, CellChar);

public:
    void putToDesk(Chess *, int, CellChar);
    void moveCellObject(int, CellChar, int, CellChar);
    void removeFromDesk(int, CellChar);

public:
    int getWidth();
    int getHeight();

public:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
};