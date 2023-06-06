#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;

#ifndef M_PI
#define M_PI 3.14159265358979323846 //Pi
#endif

class Bullet
{
	public:
	Bullet() { // добавл€ем конструктор, который принимает патрон и сохран€ет его в свойстве patrone
		m_bullet.setSize(Vector2f(5.f, 10.f));
		m_bullet.setFillColor(Color::Red);
		m_bullet.setOutlineThickness(1.f);
		m_bullet.setOutlineColor(Color::Black);
	}
	Bullet(string name, string TYPES, float Bbullet_Speed, int N_power)
	{
		Name = name;
		type = TYPES;
		Bullet_Speed = Bbullet_Speed;
		Npower = N_power;
	}
public:
	void setShouldDelete(bool a)
	{
		ShouldDelete = a;
	}
	bool getShouldDelete() const {
		return ShouldDelete;
	}
	Vector2f getPosition() const {
		// –еализаци€ получени€ позиции пули
		return m_bullet.getPosition();
	}

	FloatRect getGlobalBounds() const {
		// –еализаци€ получени€ глобальных границ пули
		return m_bullet.getGlobalBounds();
	}
	void setFillColor(Color a)
	{
		m_bullet.setFillColor(a);
	}
	void setSize(Vector2f a) 
	{
		m_bullet.setSize(a);
	}
	void update(float dt)
	{
		float direction = (GetRotation() - 90) * M_PI / 180;
		setPosition(getPosition() + Vector2f(cos(direction) * Bullet_Speed * dt, sin(direction) * Bullet_Speed * dt));
		m_direction = (getPosition() + Vector2f(cos(direction) * Bullet_Speed * dt, sin(direction) * Bullet_Speed * dt));
	}
	FloatRect getGlobalBounds()
	{
		return m_bullet.getGlobalBounds();
	}
	Vector2f GetDirect() const
	{
		return m_direction;
	}
	Vector2f getPosition()
	{
		return m_bullet.getPosition();
	}
	void setPosition(Vector2f s)
	{
		m_bullet.setPosition(s);
	}
	float GetTimeSinceSpawn() const {
		return m_bulletTimer.getElapsedTime().asSeconds();
	}
	float GetRotation()
	{
		return m_bullet.getRotation();
	}
	void SetRotation(float s)
	{
		BulletRotate = s;
		m_bullet.setRotation(s);
	}
	void draw(RenderWindow& window)
	{
		window.draw(m_bullet);
	}
	void SetDirect(Vector2f s)
	{
		m_direction = s;
	}
	void UpdatePosition(float dt) {
		// ¬ычисление вектора перемещени€ пули
		sf::Vector2f displacement = m_direction * Bullet_Speed * dt;
		cout << displacement.x << "  " << displacement.y << endl;
		// ќбновление позиции пули
		m_bullet.setPosition(displacement);
	}
	Vector2f getSize() {
		return m_bullet.getSize();
	}
	void Reflect(const Vector2f& normal) {
		float dotProduct = 2.f * (m_direction.x * normal.x + m_direction.y * normal.y);
		m_direction = m_direction - dotProduct * normal;
	}
	// ќпределение метода Reflect() дл€ отражени€ пули
	float GetReflect() const {
		return -m_bullet.getRotation() + 90;
	}
	// ќпределение метода IsOutOfBounds() дл€ проверки выхода пули за границы окна
	bool IsOutOfBounds(const Vector2u& windowSize) const {
		Vector2f position = getPosition();
		return (position.x < 0 || position.x > windowSize.x || position.y < 0 || position.y > windowSize.y);
	}
	//bool CollidesWith(const std::vector<Wall>& obstacles) const {
	//	sf::FloatRect bulletBounds = getGlobalBounds();

	//	for (const auto& obstacle : obstacles) {
	//		if (bulletBounds.intersects(obstacle.getGlobalBounds())) {
	//			return true; // ѕул€ столкнулась с преп€тствием
	//		}
	//	}

	//	return false; // ѕул€ не столкнулась с преп€тствием
	//}
protected:
	RectangleShape m_bullet;
	std::string Name;
	std::string type;
	Clock m_bulletTimer;

	float Bullet_Speed = 3500;
	float Npower;
	float BulletRotate;

	Vector2f m_direction; // Ќаправление движени€ пули

	bool ShouldDelete;
};

class Bullet9x18 : public Bullet {
public:
	Bullet9x18() : Bullet("9x18mm", "AP", 3250.f, 25) {
		// »нициализируем свойства пули калибра 9x18
		m_bullet.setFillColor(Color::Red);
		m_bullet.setSize(Vector2f(7.f, 12.f));
	}
};