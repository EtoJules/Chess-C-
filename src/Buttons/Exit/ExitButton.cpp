#include "ExitButton.h"

void ExitButton::start()
{
    m_font.loadFromFile(ASSET_FONT_PATH);
    m_isMouseOnButton = false;

    m_defaultColor = sf::Color::White;
    m_hoverColor = sf::Color::Red;

    m_TextButton.setFont(m_font);
    m_TextButton.setString(m_buttonName);
    m_TextButton.setCharacterSize(m_buttonSize);
    m_TextButton.setFillColor(sf::Color::Black);
    m_TextButton.setStyle(sf::Text::Regular);

    m_buttonBackground.setSize(sf::Vector2f(m_TextButton.getLocalBounds().width + 7, m_TextButton.getLocalBounds().height *1.8));
    m_buttonBackground.setFillColor(m_defaultColor);

    m_TextButton.setPosition(m_buttonBackground.getPosition().x / 2,
                             m_buttonBackground.getPosition().y / 2);
}

void ExitButton::onMouseMove(sf::Event event)
{
    m_mousePosition.x = event.mouseMove.x;
    m_mousePosition.y = event.mouseMove.y;

    if ((m_mousePosition.x < getPosition().x + m_buttonBackground.getSize().x &&
         m_mousePosition.x > getPosition().x) &&
        (m_mousePosition.y < getPosition().y + m_buttonBackground.getSize().y &&
         m_mousePosition.y > getPosition().y))
    {
        m_buttonBackground.setFillColor(m_hoverColor);
        m_isMouseOnButton = true;
    }
    else
    {
        m_buttonBackground.setFillColor(m_defaultColor);
        m_isMouseOnButton = false;
    }
}

void ExitButton::onMouseUp(sf::Event event) 
{
    if (event.mouseButton.button == sf::Mouse::Left)
    {
        if (m_isMouseOnButton == true)
        {
            Engine::Window::get().close();
        }
    }
}

void ExitButton::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_buttonBackground, states);
    target.draw(m_TextButton, states);
}

ExitButton::ExitButton(std::string text, int size) 
{
    m_buttonName = text;
    m_buttonSize = size;
}