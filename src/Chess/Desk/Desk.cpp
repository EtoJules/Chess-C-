#include "Desk.h"

void Desk::start()
{
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            m_cell[x][y].getRect().setPosition(x * 75, (8 - y) * 75);
            m_cell[x][y].getRect().setSize(sf::Vector2f(75, 75));
            m_cell[x][y].m_cellObj = NULL;

            if ((x % 2 == 0) == (y % 2 == 0))
            {
                m_cell[x][y].getRect().setFillColor(sf::Color::Black);
            }
            else
            {
                m_cell[x][y].getRect().setFillColor(sf::Color::White);
            }
        }
    }
}

sf::Vector2f Desk::getCellPosition(int number, CellChar character)
{
    return m_cell[character][number].getRect().getPosition() + getPosition();
}

Cell<Chess> &Desk::getCell(int number, CellChar caracter)
{
    return m_cell[caracter][number];
}

void Desk::putToDesk(Chess *chess, int number, CellChar character)
{
    chess->setPosition(getCellPosition(number, character));
    m_cell[character][number].m_cellObj = chess;
}

void Desk::moveCellObject(int fromNum, CellChar fromChar, int toNum, CellChar toChar)
{
    if(fromNum == toNum && fromChar == toChar) return;
    
    Chess *temp = m_cell[fromChar][fromNum].m_cellObj;

    if (temp != NULL)
    {
        temp->setPosition(getCellPosition(toNum, toChar));
        m_cell[toChar][toNum].m_cellObj = temp;
        m_cell[fromChar][fromNum].m_cellObj = NULL;
    }
}

void Desk::removeFromDesk(int number, CellChar character)
{
    m_cell[character][number].m_cellObj = NULL;
}

int Desk::getWidth()
{
    return 8;
}

int Desk::getHeight()
{
    return 8;
}

void Desk::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            target.draw(m_cell[x][y].m_rect, states);
        }
    }
}
