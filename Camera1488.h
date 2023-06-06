#pragma once
#include <SFML/Graphics.hpp>

class CameraRoll
{
public:
    CameraRoll()
    {
        m_view.zoom(1.f);
    }

    void setCenter(const sf::Vector2f& center)
    {
        m_view.setCenter(center);
    }

    void setSize(const sf::Vector2f& size)
    {
        m_view.setSize(size);
    }
    void setZoom(float zoom)
    {
        m_view.zoom(zoom);
    }
    void followPlayer(const sf::Vector2f& playerPosition, float smoothness)
    {
        sf::Vector2f currentPosition = m_view.getCenter();
        sf::Vector2f targetPosition = playerPosition;

        // Вычисляем новую позицию камеры с использованием интерполяции
        sf::Vector2f newPosition = currentPosition + (targetPosition - currentPosition) * smoothness;

        // Устанавливаем новую позицию камеры
        m_view.setCenter(newPosition);
    }
    void update(sf::RenderWindow & x)
    {
        m_view.setSize(sf::Vector2f(x.getSize().x / 2, x.getSize().y / 2));
        x.setView(m_view);
    }
    void applyRecoil(const sf::Vector2f& recoil)
    {
        m_view.move(-recoil);
    }
    void constrainCursorWithinWindow(sf::RenderWindow& window)
    {
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2i mousePosition = sf::Mouse::getPosition();

        if (mousePosition.x < 0)
            mousePosition.x = 0;
        else if (mousePosition.x >= static_cast<int>(windowSize.x))
            mousePosition.x = static_cast<int>(windowSize.x) - 1;

        if (mousePosition.y < 0)
            mousePosition.y = 0;
        else if (mousePosition.y >= static_cast<int>(windowSize.y))
            mousePosition.y = static_cast<int>(windowSize.y) - 1;

        sf::Mouse::setPosition(mousePosition);
    }
    sf::View m_view;
};