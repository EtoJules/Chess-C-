template <class T>
sf::RectangleShape &Cell<T>::getRect()
{
    return m_rect;
}

template <class T>
T &Cell<T>::getCellObject()
{
    return m_cellObj;
}


template<class T>
void Cell<T>::setCellObject(T cellObj) 
{
    m_cellObj = cellObj;
}

template <class T>
Cell<T>::Cell()
{
    m_cellObj = NULL;
}