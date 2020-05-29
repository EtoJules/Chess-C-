#pragma once

#include <unordered_map>
#include "IGameObject.h"
#include "Desk.h"
#include "Chess.h"

class DeskController : public Engine::IGameObject
{
private:
    Desk *m_desk;
    std::vector<Chess *> m_chessArray;

private:
    sf::Vector2f m_mousePosition;

private:
    Cell<Chess> *m_selectedCell;

    std::vector<std::pair<int, CellChar>> m_chessMoves;
    std::vector<sf::Color> m_selectedCellColour;
    sf::Color m_grabCellColour;

    bool m_isObjSelected;
    bool m_moveWithMouse;

private:
    void getMousePosition(sf::Event event);
    void grabObject(int, int);
    void putObject(int, int);
    void setupChessMoves(int x, int y);
    void addChessMove(int x, int y);
    void switchMove();

public:
    void start();
    void onMouseDown(sf::Event);
    void onMouseUp(sf::Event);
    void onMouseMove(sf::Event);

public:
    DeskController(Desk *, std::vector<Chess *>);
};