#pragma once

#include "SFML/Graphics.hpp"

enum CellChar
{
    a = 0,
    b,
    c,
    d,
    e,
    f,
    g,
    h
};

template <class T>
class Cell
{
public:
    sf::RectangleShape m_rect;
    T *m_cellObj;

public:
    sf::RectangleShape &getRect();
    T &getCellObject();
    void setCellObject(T);

public:
    Cell();
};

#include "Cell.cpp"