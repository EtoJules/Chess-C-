#include "DeskController.h"

void DeskController::start()
{
    m_desk->setPosition(300, -40);
    for (int i = 0; i < 8; ++i)
    {
        m_chessArray[i]->setType(pawn);
        m_desk->putToDesk(m_chessArray[i], 1, (CellChar)i);

        m_chessArray[16 + i]->setType(pawn, black);
        m_desk->putToDesk(m_chessArray[16 + i], 6, (CellChar)i);
    }
    m_chessArray[8]->setType(rook, white);
    m_chessArray[9]->setType(knight, white);
    m_chessArray[10]->setType(bishop, white);
    m_chessArray[11]->setType(queen, white);
    m_chessArray[12]->setType(king, white);
    m_chessArray[13]->setType(bishop, white);
    m_chessArray[14]->setType(knight, white);
    m_chessArray[15]->setType(rook, white);

    m_chessArray[24]->setType(rook, black);
    m_chessArray[25]->setType(knight, black);
    m_chessArray[26]->setType(bishop, black);
    m_chessArray[27]->setType(queen, black);
    m_chessArray[28]->setType(king, black);
    m_chessArray[29]->setType(bishop, black);
    m_chessArray[30]->setType(knight, black);
    m_chessArray[31]->setType(rook, black);
    for (int i = 8; i < 16; ++i)
    {
        m_desk->putToDesk(m_chessArray[i], 0, (CellChar)(i - 8));

        m_desk->putToDesk(m_chessArray[16 + i], 7, (CellChar)(i - 8));
    }
    m_grabCellColour = sf::Color(120, 123, 123);
    m_selectedCell = NULL;
    m_isObjSelected = false;
    m_moveWithMouse = false;
}

void DeskController::onMouseDown(sf::Event event)
{
    for (int x = 0; x < m_desk->getWidth(); ++x)
    {
        for (int y = 0; y < m_desk->getHeight(); ++y)
        {
            if ((m_mousePosition.x < m_desk->getCellPosition(x, (CellChar)x).x + m_desk->getCell(x, (CellChar)y).m_rect.getSize().x &&
                 m_mousePosition.x > m_desk->getCellPosition(x, (CellChar)x).x) &&
                (m_mousePosition.y < m_desk->getCellPosition(y, (CellChar)y).y + m_desk->getCell(x, (CellChar)y).m_rect.getSize().y &&
                 m_mousePosition.y > m_desk->getCellPosition(y, (CellChar)y).y))
            {
                if (m_isObjSelected == false)
                {
                    m_selectedCell = &m_desk->getCell(y, (CellChar)x);
                    if (m_selectedCell->m_cellObj != NULL)
                    {
                        grabObject(x, y);
                    }
                }
            }
        }
    }
}

void DeskController::onMouseUp(sf::Event event)
{
    for (int x = 0; x < m_desk->getWidth(); ++x)
    {
        for (int y = 0; y < m_desk->getHeight(); ++y)
        {
            if ((m_mousePosition.x < m_desk->getCellPosition(x, (CellChar)x).x + m_desk->getCell(x, (CellChar)y).m_rect.getSize().x &&
                 m_mousePosition.x > m_desk->getCellPosition(x, (CellChar)x).x) &&
                (m_mousePosition.y < m_desk->getCellPosition(y, (CellChar)y).y + m_desk->getCell(x, (CellChar)y).m_rect.getSize().y &&
                 m_mousePosition.y > m_desk->getCellPosition(y, (CellChar)y).y))
            {
                if (m_isObjSelected == true)
                {
                    for (auto iter = m_chessMoves.begin(); iter != m_chessMoves.end(); ++iter)
                    {
                        if (iter->first == y && iter->second == x)
                        {
                            if (m_desk->getCell(y, (CellChar)x).m_cellObj != NULL &&
                                m_desk->getCell(y, (CellChar)x).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                            {
                                m_desk->getCell(y, (CellChar)x).m_cellObj->setPosition(50, 200);
                                m_desk->removeFromDesk(y, (CellChar)x);
                            }

                            putObject(x, y);
                        }
                    }
                }
            }
        }
    }
}

void DeskController::onMouseMove(sf::Event event)
{
    getMousePosition(event);

    if (m_moveWithMouse == true && m_selectedCell != NULL && m_selectedCell->m_cellObj != NULL)
    {
        m_selectedCell->m_cellObj->setPosition(m_mousePosition.x - 32 * m_selectedCell->m_cellObj->getScale().x,
                                               m_mousePosition.y - 32 * m_selectedCell->m_cellObj->getScale().y);
    }
}

DeskController::DeskController(Desk *desk, std::vector<Chess *> chessArray)
{
    m_desk = desk;
    m_chessArray = chessArray;
    m_selectedCell = NULL;
    m_isObjSelected = false;
    m_moveWithMouse = false;
}

void DeskController::getMousePosition(sf::Event event)
{
    m_mousePosition.x = event.mouseMove.x;
    m_mousePosition.y = event.mouseMove.y;
}

void DeskController::grabObject(int x, int y)
{
    m_selectedCellColour.clear();
    m_chessMoves.clear();

    setupChessMoves(x, y);

    for (auto iter = m_chessMoves.begin(); iter != m_chessMoves.end(); ++iter)
    {
        m_grabCellColour = sf::Color(m_desk->getCell(iter->first, (CellChar)iter->second).m_rect.getFillColor().r, 120, 40);
        m_selectedCellColour.push_back(m_desk->getCell(iter->first, (CellChar)iter->second).m_rect.getFillColor());
        m_desk->getCell(iter->first, (CellChar)iter->second).m_rect.setFillColor(m_grabCellColour);
    }

    m_selectedCell->m_cellObj->setScale(1.3, 1.3);
    m_isObjSelected = true;
    m_moveWithMouse = true;
}

void DeskController::putObject(int x, int y)
{
    int i = 0;
    //m_selectedCell->m_rect.setFillColor(m_selectedCellColour);
    for (auto iter = m_chessMoves.begin(); iter != m_chessMoves.end(); ++iter)
    {
        sf::Color fillColor = m_selectedCellColour[i];
        m_desk->getCell(iter->first, (CellChar)iter->second).m_rect.setFillColor(fillColor);
        m_selectedCellColour.pop_back();
        ++i;
    }

    m_selectedCell->m_cellObj->setScale(1, 1);
    m_desk->moveCellObject(m_chessMoves.begin()->first, m_chessMoves.begin()->second, y, (CellChar)x);
    m_selectedCell = NULL;
    m_isObjSelected = false;
    m_moveWithMouse = false;
}

void DeskController::setupChessMoves(int x, int y)
{
    ChessColor chessType = m_selectedCell->m_cellObj->getColor();

    switch (m_selectedCell->m_cellObj->getType())
    {
    case pawn:
        addChessMove(y, x);

        if (m_selectedCell->m_cellObj->getColor() == white)
        {

            if (x < 8 && y + 1 < 8 && x >= 0 && y + 1 >= 0)
            {
                if (m_desk->getCell(y + 1, (CellChar)(x)).m_cellObj == NULL)
                {
                    addChessMove(y + 1, x);
         
                }
            }
            if (x + 1 < 8 && y + 1 < 8 && x + 1 >= 0 && y + 1 >= 0)
            {
                if (m_desk->getCell(y + 1, (CellChar)(x + 1)).m_cellObj != NULL &&
                    m_desk->getCell(y + 1, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + 1, x + 1);
                }
            }

            if (x - 1 < 8 && y + 1 < 8 && x - 1 >= 0 && y + 1 >= 0)
            {
                if (m_desk->getCell(y + 1, (CellChar)(x - 1)).m_cellObj != NULL &&
                    m_desk->getCell(y + 1, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + 1, x - 1);
                }
            }
        }
        else
        {
            if (y == 6)
            {
                addChessMove(y - 2, x);
            }
            if (x < 8 && y - 1 < 8 && x >= 0 && y - 1 >= 0)
            {
                if (m_desk->getCell(y - 1, (CellChar)(x)).m_cellObj == NULL)
                {
                    addChessMove(y - 1, x);

                }
            }
            if (x + 1 < 8 && y - 1 < 8 && x + 1 >= 0 && y - 1 >= 0)
            {
                if (m_desk->getCell(y - 1, (CellChar)(x + 1)).m_cellObj != NULL &&
                    m_desk->getCell(y - 1, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - 1, x + 1);
                }
            }

            if (x - 1 < 8 && y - 1 < 8 && x - 1 >= 0 && y - 1 >= 0)
            {
                if (m_desk->getCell(y - 1, (CellChar)(x - 1)).m_cellObj != NULL &&
                    m_desk->getCell(y - 1, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - 1, x - 1);
                }
            }
        }

        break;

    case bishop:
        addChessMove(y, x);

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y + i < 8 && x + i >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x + i);
                    break;
                }
            }
            addChessMove(y + i, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y + i < 8 && x - i >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x - i);
                    break;
                }
            }
            addChessMove(y + i, x - i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y - i < 8 && x + i >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x + i);
                    break;
                }
            }
            addChessMove(y - i, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y - i < 8 && x - i >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x - i);
                    break;
                }
            }
            addChessMove(y - i, x - i);
        }

        break;

    case knight:
        addChessMove(y, x);
        if (x + 2 < 8 && y + 1 < 8 && x + 2 >= 0 && y + 1 >= 0)
        {
            if (m_desk->getCell(y + 1, (CellChar)(x + 2)).m_cellObj == NULL)
            {
                addChessMove(y + 1, x + 2);
            }
            else if (m_desk->getCell(y + 1, (CellChar)(x + 2)).m_cellObj != NULL &&
                     m_desk->getCell(y + 1, (CellChar)(x + 2)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 1, x + 2);
            }
        }

        if (x - 2 < 8 && y + 1 < 8 && x - 2 >= 0 && y + 1 >= 0)
        {
            if (m_desk->getCell(y + 1, (CellChar)(x - 2)).m_cellObj == NULL)
            {
                addChessMove(y + 1, x - 2);
            }
            else if (m_desk->getCell(y + 1, (CellChar)(x - 2)).m_cellObj != NULL &&
                     m_desk->getCell(y + 1, (CellChar)(x - 2)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 1, x - 2);
            }
        }

        if (x + 2 < 8 && y - 1 < 8 && x + 2 >= 0 && y - 1 >= 0)
        {
            if (m_desk->getCell(y - 1, (CellChar)(x + 2)).m_cellObj == NULL)
            {
                addChessMove(y - 1, x + 2);
            }
            else if (m_desk->getCell(y - 1, (CellChar)(x + 2)).m_cellObj != NULL &&
                     m_desk->getCell(y - 1, (CellChar)(x + 2)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 1, x + 2);
            }
        }

        if (x - 2 < 8 && y - 1 < 8 && x - 2 >= 0 && y - 1 >= 0)
        {
            if (m_desk->getCell(y - 1, (CellChar)(x + 2)).m_cellObj == NULL)
            {
                addChessMove(y - 1, x - 2);
            }
            else if (m_desk->getCell(y - 1, (CellChar)(x - 2)).m_cellObj != NULL &&
                     m_desk->getCell(y - 1, (CellChar)(x - 2)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 1, x - 2);
            }
        }

        if (x + 1 < 8 && y + 2 < 8 && x + 1 >= 0 && y + 2 >= 0)
        {
            if (m_desk->getCell(y + 2, (CellChar)(x + 1)).m_cellObj == NULL)
            {
                addChessMove(y + 2, x + 1);
            }
            else if (m_desk->getCell(y + 2, (CellChar)(x + 1)).m_cellObj != NULL &&
                     m_desk->getCell(y + 2, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 2, x + 1);
            }
        }

        if (x - 1 < 8 && y + 2 < 8 && x - 1 >= 0 && y + 2 >= 0)
        {
            if (m_desk->getCell(y + 2, (CellChar)(x - 1)).m_cellObj == NULL)
            {
                addChessMove(y + 2, x - 1);
            }
            else if (m_desk->getCell(y + 2, (CellChar)(x - 1)).m_cellObj != NULL &&
                     m_desk->getCell(y + 2, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 2, x - 1);
            }
        }

        if (x + 1 < 8 && y - 2 < 8 && x + 1 >= 0 && y - 2 >= 0)
        {
            if (m_desk->getCell(y - 2, (CellChar)(x + 1)).m_cellObj == NULL)
            {
                addChessMove(y - 2, x + 1);
            }
            else if (m_desk->getCell(y - 2, (CellChar)(x + 1)).m_cellObj != NULL &&
                     m_desk->getCell(y - 2, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 2, x + 1);
            }
        }

        if (x - 1 < 8 && y - 2 < 8 && x - 1 >= 0 && y - 2 >= 0)
        {
            if (m_desk->getCell(y - 2, (CellChar)(x - 1)).m_cellObj == NULL)
            {
                addChessMove(y - 2, x - 1);
            }
            else if (m_desk->getCell(y - 2, (CellChar)(x - 1)).m_cellObj != NULL &&
                     m_desk->getCell(y - 2, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 2, x - 1);
            }
        }

        break;

    case rook:
        addChessMove(y, x);

        for (int i = 1; i < 8; ++i)
        {
            if (x < 8 && y + i < 8 && x >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x);
                    break;
                }
            }
            addChessMove(y + i, x);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x < 8 && y - i < 8 && x >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x);
                    break;
                }
            }
            addChessMove(y - i, x);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y < 8 && x + i >= 0 && y >= 0)
            {
                if (m_desk->getCell(y, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y, x + i);
                    break;
                }
            }
            addChessMove(y, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y < 8 && x - i >= 0 && y >= 0)
            {
                if (m_desk->getCell(y, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y, x - i);
                    break;
                }
            }
            addChessMove(y, x - i);
        }

        break;

    case queen:
        addChessMove(y, x);

        for (int i = 1; i < 8; ++i)
        {
            if (x < 8 && y + i < 8 && x >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x);
                    break;
                }
            }
            addChessMove(y + i, x);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x < 8 && y - i < 8 && x >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x);
                    break;
                }
            }
            addChessMove(y - i, x);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y < 8 && x + i >= 0 && y >= 0)
            {
                if (m_desk->getCell(y, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y, x + i);
                    break;
                }
            }
            addChessMove(y, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y < 8 && x - i >= 0 && y >= 0)
            {
                if (m_desk->getCell(y, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y, x - i);
                    break;
                }
            }
            addChessMove(y, x - i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y + i < 8 && x + i >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x + i);
                    break;
                }
            }
            addChessMove(y + i, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y + i < 8 && x - i >= 0 && y + i >= 0)
            {
                if (m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y + i, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y + i, x - i);
                    break;
                }
            }
            addChessMove(y + i, x - i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x + i < 8 && y - i < 8 && x + i >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x + i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x + i);
                    break;
                }
            }
            addChessMove(y - i, x + i);
        }

        for (int i = 1; i < 8; ++i)
        {
            if (x - i < 8 && y - i < 8 && x - i >= 0 && y - i >= 0)
            {
                if (m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj->getColor() == m_selectedCell->m_cellObj->getColor())
                {
                    break;
                }
                if (m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj != NULL &&
                    m_desk->getCell(y - i, (CellChar)(x - i)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
                {
                    addChessMove(y - i, x - i);
                    break;
                }
            }
            addChessMove(y - i, x - i);
        }

        break;

    case king:
        addChessMove(y, x);

        if (x < 8 && y + 1 < 8 && x >= 0 && y + 1 >= 0)
        {
            if (m_desk->getCell(y + 1, (CellChar)(x)).m_cellObj == NULL)
            {
                addChessMove(y + 1, x);
            }
            else if (m_desk->getCell(y + 1, (CellChar)(x)).m_cellObj != NULL &&
                     m_desk->getCell(y + 1, (CellChar)x).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 1, x);
            }
        }

        if (x + 1 < 8 && y + 1 < 8 && x + 1 >= 0 && y + 1 >= 0)
        {
            if (m_desk->getCell(y + 1, (CellChar)(x + 1)).m_cellObj == NULL)
            {
                addChessMove(y + 1, x + 1);
            }
            else if (m_desk->getCell(y + 1, (CellChar)(x + 1)).m_cellObj != NULL &&
                     m_desk->getCell(y + 1, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 1, x + 1);
            }
        }

        if (x - 1 < 8 && y + 1 < 8 && x - 1 >= 0 && y + 1 >= 0)
        {
            if (m_desk->getCell(y + 1, (CellChar)(x - 1)).m_cellObj == NULL)
            {
                addChessMove(y + 1, x - 1);
            }
            else if (m_desk->getCell(y + 1, (CellChar)(x - 1)).m_cellObj != NULL &&
                     m_desk->getCell(y + 1, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y + 1, x - 1);
            }
        }

        if (x - 1 < 8 && y - 1 < 8 && x - 1 >= 0 && y - 1 >= 0)
        {
            if (m_desk->getCell(y - 1, (CellChar)(x - 1)).m_cellObj == NULL)
            {
                addChessMove(y - 1, x - 1);
            }
            else if (m_desk->getCell(y - 1, (CellChar)(x - 1)).m_cellObj != NULL &&
                     m_desk->getCell(y - 1, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 1, x - 1);
            }
        }

        if (x + 1 < 8 && y - 1 < 8 && x + 1 >= 0 && y - 1 >= 0)
        {
            if (m_desk->getCell(y - 1, (CellChar)(x + 1)).m_cellObj == NULL)
            {
                addChessMove(y - 1, x + 1);
            }
            else if (m_desk->getCell(y - 1, (CellChar)(x + 1)).m_cellObj != NULL &&
                     m_desk->getCell(y - 1, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 1, x + 1);
            }
        }

        if (x < 8 && y - 1 < 8 && x >= 0 && y - 1 >= 0)
        {
            if (m_desk->getCell(y - 1, (CellChar)(x)).m_cellObj == NULL)
            {
                addChessMove(y - 1, x);
            }
            else if (m_desk->getCell(y - 1, (CellChar)(x)).m_cellObj != NULL &&
                     m_desk->getCell(y - 1, (CellChar)(x)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y - 1, x);
            }
        }

        if (x + 1 < 8 && y < 8 && x + 1 >= 0 && y >= 0)
        {
            if (m_desk->getCell(y, (CellChar)(x + 1)).m_cellObj == NULL)
            {
                addChessMove(y, x + 1);
            }
            else if (m_desk->getCell(y, (CellChar)(x + 1)).m_cellObj != NULL &&
                     m_desk->getCell(y, (CellChar)(x + 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y, x + 1);
            }
        }

        if (x - 1 < 8 && y < 8 && x - 1 >= 0 && y >= 0)
        {
            if (m_desk->getCell(y, (CellChar)(x - 1)).m_cellObj == NULL)
            {
                addChessMove(y, x - 1);
            }
            else if (m_desk->getCell(y, (CellChar)(x - 1)).m_cellObj != NULL &&
                     m_desk->getCell(y, (CellChar)(x - 1)).m_cellObj->getColor() != m_selectedCell->m_cellObj->getColor())
            {
                addChessMove(y, x - 1);
            }
        }

        break;

    default:
        break;
    }
}

void DeskController::addChessMove(int x, int y)
{
    if (x < 8 && y < 8 && x >= 0 && y >= 0)
    {
        m_chessMoves.push_back(std::pair<int, CellChar>(x, (CellChar)y));
    }
}

void DeskController::switchMove()
{
}