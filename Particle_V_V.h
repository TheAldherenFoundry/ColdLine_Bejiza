#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Textures.h"

using namespace sf;
using namespace std;

class Particle
{
private:
    bool isBehindWall(Vector2f position, Vector2f wallCenter, Vector2f wallBackPosition)
    {
        // Проверяем, находится ли точка position за стеной
        // Предполагаем, что стена представляет собой отрезок между wallCenter и wallBackPosition
        // Если точка находится справа от стены, то она считается за стеной
        // Используем скалярное произведение и векторное произведение для определения положения точки относительно стены

        Vector2f wallDirection = wallBackPosition - wallCenter;
        Vector2f pointDirection = position - wallCenter;

        float crossProduct = wallDirection.x * pointDirection.y - wallDirection.y * pointDirection.x;
        float dotProduct = wallDirection.x * pointDirection.x + wallDirection.y * pointDirection.y;

        return crossProduct >= 0 && dotProduct >= 0;
    }
    Vector2f reflectVector(Vector2f vector, Vector2f normal)
    {
        // Отражаем вектор vector относительно заданной нормали normal
        // Используем формулу отражения вектора: reflectedVector = vector - 2 * dotProduct(vector, normal) * normal

        float dotProduct = vector.x * normal.x + vector.y * normal.y;
        Vector2f reflectedVector = vector - 2.f * dotProduct * normal;

        return reflectedVector;
    }

    sf::Vector2f normalize(const sf::Vector2f& vector)
    {
        float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (length != 0.0f)
        {
            return sf::Vector2f(vector.x / length, vector.y / length);
        }
        return vector;
    }

    bool isParticleCollidingWithWall(const sf::Shape& particle, const sf::RectangleShape& wall)
    {
        sf::FloatRect particleBounds = particle.getGlobalBounds();
        sf::FloatRect wallBounds = wall.getGlobalBounds();

        return particleBounds.intersects(wallBounds);
    }
public:
    void Partickle_HLOPOK(Vector2f position, float reflectAngle)
{
    int numParticles = m_minPractlk + static_cast<int>(std::rand()) / (static_cast<float>(RAND_MAX) / (m_maxPractlk - m_minPractlk));
    for (int i = 0; i < numParticles; ++i)
    {
        float velocityMagnitude = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * maxSpeed; // Случайная величина скорости

        sf::RectangleShape particle; // Создаем круговую частицу
        particle.setSize(sf::Vector2f(rand() % 12, rand() % 6));
        particle.setPosition(position);
        particle.setTexture(PARTICLE.Give_Me_Random_Praticle_Texture());

        // Генерируем случайный угол для направления частицы отраженного от пули
        float deviationAngle = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * 60.0f - 30.0f; // Отклонение от -30 до +30 градусов
        float angle = reflectAngle + deviationAngle;
        float radian = angle * 3.14159f / 180.f;

        // Вычисляем вектор скорости на основе случайной величины и угла
        sf::Vector2f velocity(std::cos(radian), std::sin(radian));
        velocity *= velocityMagnitude;

        // Добавляем частицу и ее параметры в соответствующие списки
        m_particles.push_back(new sf::RectangleShape(std::move(particle)));
        m_particleVelocities.push_back(velocity);
        m_particleLifetimes.push_back(particleLifetime);

        float lifetime = m_minLifetime + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX) / (m_maxLifetime - m_minLifetime));
        m_particleLifetimes.push_back(lifetime);
    }
}

    //Обновление частиц
    void UpdateParticles(float deltaTime, const sf::FloatRect& object)
    {
        sf::FloatRect bounds; // Границы стены

        for (int i = static_cast<int>(m_particles.size()) - 1; i >= 0; --i)
        {
            float alpha = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX); // Генерируем случайное значение прозрачности

            m_particles[i]->setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * alpha))); // Применяем прозрачность к цвету

            // Обновляем положение частицы на основе скорости
            m_particles[i]->move(m_particleVelocities[i] * deltaTime);

            float angle = std::atan2(m_particleVelocities[i].y, m_particleVelocities[i].x) * 180.f / 3.14159f;
            m_particles[i]->setRotation(angle);

            // Уменьшаем время жизни частицы
            m_particleLifetimes[i] -= deltaTime;

            // Если время жизни частицы истекло, удаляем ее
            if (m_particleLifetimes[i] <= 0)
            {
                m_particles.erase(m_particles.begin() + i);
                m_particleVelocities.erase(m_particleVelocities.begin() + i);
                m_particleLifetimes.erase(m_particleLifetimes.begin() + i);
                continue; // Пропускаем остаток цикла для удаленной частицы
            }

            if (m_particleLifetimes[i] <= 0.2) {
                // Проверяем столкновение с объектом
                sf::FloatRect particleBounds = m_particles[i]->getGlobalBounds();
                sf::FloatRect objectBounds = object;

                if (particleBounds.intersects(objectBounds))
                {

                    m_particles.erase(m_particles.begin() + i);
                    m_particleVelocities.erase(m_particleVelocities.begin() + i);
                    m_particleLifetimes.erase(m_particleLifetimes.begin() + i);

                    continue; // Пропускаем остаток цикла для удаленной частицы
                    // Отражаем частицу от объекта
                    if (m_particleVelocities[i].x > 0 && particleBounds.left + particleBounds.width > objectBounds.left)
                        m_particleVelocities[i].x *= -1;
                    else if (m_particleVelocities[i].x < 0 && particleBounds.left < objectBounds.left + objectBounds.width)
                        m_particleVelocities[i].x *= -1;

                    if (m_particleVelocities[i].y > 0 && particleBounds.top + particleBounds.height > objectBounds.top)
                        m_particleVelocities[i].y *= -1;
                    else if (m_particleVelocities[i].y < 0 && particleBounds.top < objectBounds.top + objectBounds.height)
                        m_particleVelocities[i].y *= -1;

                    break; // Прерываем цикл, чтобы не проверять столкновение с остальными объектами
                }
            }
        }
    }
    //Обновление частиц
    void UpdateParticles(float deltaTime, const sf::RectangleShape& object)
    {
        sf::FloatRect bounds; // Границы стены

        for (int i = static_cast<int>(m_particles.size()) - 1; i >= 0; --i)
        {
            float alpha = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX); // Генерируем случайное значение прозрачности

            m_particles[i]->setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * alpha))); // Применяем прозрачность к цвету

            // Обновляем положение частицы на основе скорости
            m_particles[i]->move(m_particleVelocities[i] * deltaTime);

            float angle = std::atan2(m_particleVelocities[i].y, m_particleVelocities[i].x) * 180.f / 3.14159f;
            m_particles[i]->setRotation(angle);

            // Уменьшаем время жизни частицы
            m_particleLifetimes[i] -= deltaTime;
            
            // Если время жизни частицы истекло, удаляем ее
            if (m_particleLifetimes[i] <= 0)
            {
                m_particles.erase(m_particles.begin() + i);
                m_particleVelocities.erase(m_particleVelocities.begin() + i);
                m_particleLifetimes.erase(m_particleLifetimes.begin() + i);
                continue; // Пропускаем остаток цикла для удаленной частицы
            }

            if (m_particleLifetimes[i] <= 0.2) {
                // Проверяем столкновение с объектом
                sf::FloatRect particleBounds = m_particles[i]->getGlobalBounds();
                sf::FloatRect objectBounds = object.getGlobalBounds();

                if (particleBounds.intersects(objectBounds))
                {

                    m_particles.erase(m_particles.begin() + i);
                    m_particleVelocities.erase(m_particleVelocities.begin() + i);
                    m_particleLifetimes.erase(m_particleLifetimes.begin() + i);

                    continue; // Пропускаем остаток цикла для удаленной частицы
                    // Отражаем частицу от объекта
                    if (m_particleVelocities[i].x > 0 && particleBounds.left + particleBounds.width > objectBounds.left)
                        m_particleVelocities[i].x *= -1;
                    else if (m_particleVelocities[i].x < 0 && particleBounds.left < objectBounds.left + objectBounds.width)
                        m_particleVelocities[i].x *= -1;

                    if (m_particleVelocities[i].y > 0 && particleBounds.top + particleBounds.height > objectBounds.top)
                        m_particleVelocities[i].y *= -1;
                    else if (m_particleVelocities[i].y < 0 && particleBounds.top < objectBounds.top + objectBounds.height)
                        m_particleVelocities[i].y *= -1;

                    break; // Прерываем цикл, чтобы не проверять столкновение с остальными объектами
                }
            }
        }
    }

    //Обновление частиц
    void UpdateParticles(float deltaTime, const sf::Sprite& object)
    {
        sf::FloatRect bounds; // Границы стены

        for (int i = static_cast<int>(m_particles.size()) - 1; i >= 0; --i)
        {
            float alpha = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX); // Генерируем случайное значение прозрачности

            m_particles[i]->setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(255 * alpha))); // Применяем прозрачность к цвету

            // Обновляем положение частицы на основе скорости
            m_particles[i]->move(m_particleVelocities[i] * deltaTime);

            float angle = std::atan2(m_particleVelocities[i].y, m_particleVelocities[i].x) * 180.f / 3.14159f;
            m_particles[i]->setRotation(angle);

            // Уменьшаем время жизни частицы
            m_particleLifetimes[i] -= deltaTime;

            // Если время жизни частицы истекло, удаляем ее
            if (m_particleLifetimes[i] <= 0)
            {
                m_particles.erase(m_particles.begin() + i);
                m_particleVelocities.erase(m_particleVelocities.begin() + i);
                m_particleLifetimes.erase(m_particleLifetimes.begin() + i);
                continue; // Пропускаем остаток цикла для удаленной частицы
            }

            if (m_particleLifetimes[i] <= 0.4) {
                // Проверяем столкновение с объектом
                sf::FloatRect particleBounds = m_particles[i]->getGlobalBounds();
                sf::FloatRect objectBounds = object.getGlobalBounds();

                if (particleBounds.intersects(objectBounds))
                {

                    m_particles.erase(m_particles.begin() + i);
                    m_particleVelocities.erase(m_particleVelocities.begin() + i);
                    m_particleLifetimes.erase(m_particleLifetimes.begin() + i);

                    continue; // Пропускаем остаток цикла для удаленной частицы
                    // Отражаем частицу от объекта
                    if (m_particleVelocities[i].x > 0 && particleBounds.left + particleBounds.width > objectBounds.left)
                        m_particleVelocities[i].x *= -1;
                    else if (m_particleVelocities[i].x < 0 && particleBounds.left < objectBounds.left + objectBounds.width)
                        m_particleVelocities[i].x *= -1;

                    if (m_particleVelocities[i].y > 0 && particleBounds.top + particleBounds.height > objectBounds.top)
                        m_particleVelocities[i].y *= -1;
                    else if (m_particleVelocities[i].y < 0 && particleBounds.top < objectBounds.top + objectBounds.height)
                        m_particleVelocities[i].y *= -1;

                    break; // Прерываем цикл, чтобы не проверять столкновение с остальными объектами
                }
            }
        }
    }
    // Отрисовка частиц
    void DrawParticles(RenderWindow& window)
    {
        for (const auto& particle : m_particles)
        {
            window.draw(*particle); 
        }
    }

private:
    vector<sf::Shape*> m_particles; // Хранение частиц
    vector<sf::Vector2f> m_particleVelocities; // Скорости частиц
    vector<float> m_particleLifetimes; // Времена жизни частиц
    TEXTURES_MODULE PARTICLE;

    const int numParticles = 0; // Количество частиц
    const float particleSpeed = 10.f; // Скорость частиц (пиксели в секунду)
    const float maxSpeed = 30.f;
    const float particleLifetime = 0.3; // Время жизни частицы (в секундах)

    float m_minLifetime = 0.9; // Минимальное время жизни частицы
    float m_maxLifetime = 2.5; // Максимальное время жизни частицы

    int m_minPractlk = 10; // Минимальное кол-во частиц
    int m_maxPractlk = 300; // Максимальное кол-во частиц
};