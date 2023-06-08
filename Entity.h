#pragma once
#include "Camera1488.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <list>

using namespace sf;
using namespace std;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

template <typename T>
Vector2<T> normalize(const Vector2<T>& source)
{
	const T length = sqrt(source.x * source.x + source.y * source.y);
	return length > 0 ? source / length : source;
}

class Entity
{

};

class Player : public Entity
{
public:
	Player()
	{

	}
	// Конструктор принимает начальную позицию игрока, его размер и цвет
	Player(Vector2f position, float size, float speed, Color color) : speed(speed) {
		m_legs.setSize(Vector2f(size, size));
		m_legs.setOrigin(size / 2, size / 2);
		m_legs.setPosition(position);
		m_legs.setFillColor(Color::Cyan);

		m_body.setSize(Vector2f(size / 1.5, size / 1.5));
		m_body.setOrigin(size / 3, size / 3);
		m_body.setPosition(position);
		m_body.setFillColor(color);

		m_aim.setSize(Vector2f(10, 10));;
		m_aim.setFillColor(Color::Green);

		m_speed = speed;
		m_bodyOffset = Vector2f(-size / 4.f, size / 4.f);
		//m_aimOffset = Vector2f(size / 4.f, -size / 4.f);

		this->size = size;
	}


	// Метод draw отрисовывает игрока на заданном окне
	void draw(RenderWindow& window) const
	{
		window.draw(m_legs);
		window.draw(m_body);
		window.draw(m_aim);                                            //   89191949864 - номер Ерошенкова
	}

	void GiveMeMovePLS()
	{
		// Дай мне ходить!

		CanIMoveLEFT = 1;
		CanIMoveRIGHT = 1;
		CanIMoveUP = 1;
		CanIMoveDAUN = 1;

	};



	void update(float& deltaTime, RenderWindow& window, Player& player)
	{
		// Передвижение клавиатурой
		Movement(deltaTime, player);
		// Поворот
		player.playerRotate(deltaTime, window, player);
		// Камера
		Kelab.followPlayer(player.m_legs.getPosition(), 0.02);
		Kelab.update(window);

		m_body.setPosition(m_legs.getPosition());

		// Используем установленный угол поворота прицела и смещение, чтобы установить его позицию
		m_aim.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		player.draw(window);
	}

	void Movement(float& deltaTime, Player& player) {
		// Передвижение клавиатурой
		if (Keyboard::isKeyPressed(Keyboard::D) && CanIMoveRIGHT) { MoveKeybordX = 1 * deltaTime * speed; }
		if (Keyboard::isKeyPressed(Keyboard::A) && CanIMoveLEFT) { MoveKeybordX = -1 * deltaTime * speed; }
		if (Keyboard::isKeyPressed(Keyboard::W) && CanIMoveUP) { MoveKeybordY = 1 * deltaTime * speed; }
		if (Keyboard::isKeyPressed(Keyboard::S) && CanIMoveDAUN) { MoveKeybordY = -1 * deltaTime * speed; }
		if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) || (Keyboard::isKeyPressed(Keyboard::D) && CanIMoveRIGHT == 0) || (Keyboard::isKeyPressed(Keyboard::A) && CanIMoveLEFT == 0)) { MoveKeybordX = 0 * deltaTime * speed; }
		if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W) && CanIMoveUP == 0) || (Keyboard::isKeyPressed(Keyboard::S) && CanIMoveDAUN == 0)) { MoveKeybordY = 0 * deltaTime * speed; }

		//Само передвижение
		m_legs.move(Vector2f(MoveKeybordX, -MoveKeybordY));

		player.GiveMeMovePLS();
	}

	void playerRotate(float& deltaTime, RenderWindow& window, Player& player) {
		//Поворот тела и прицела
		bodyRotation(window, player);
		//Поворот ног
		legsRotation(deltaTime, player);
	}

	//Поворот ног
	void legsRotation(float& deltaTime, Player& player) {
		float Rotate = 0;
		if (Keyboard::isKeyPressed(Keyboard::W)) Rotate = 0;
		if (Keyboard::isKeyPressed(Keyboard::A)) Rotate = -90;
		if (Keyboard::isKeyPressed(Keyboard::S)) Rotate = 180;
		if (Keyboard::isKeyPressed(Keyboard::D)) Rotate = 90;
		if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) Rotate = 45;
		if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S)) Rotate = 135;
		if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) Rotate = -135;
		if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::W)) Rotate = -45;
		player.m_legs.setRotation(Rotate);
	}

	//Поворот тела и прицела
	void bodyRotation(sf::RenderWindow& window, Player& player)
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Получаем позицию мыши относительно окна
		sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition); // Преобразуем в мировые координаты

		sf::Vector2f direction = worldMousePosition - player.m_body.getPosition(); // Вычисляем вектор направления курсора
		// Вычисляем угол поворота
		float rotation = std::atan2(direction.y, direction.x) * 180.f / M_PI; // Вычисляем угол поворота

		player.m_body.setRotation(rotation);
		
	}

public:
	CameraRoll Kelab;
	// Фигура, используемая для отрисовки игрока
	RectangleShape m_legs;
	RectangleShape m_body;
	RectangleShape m_aim;

	bool CanIMoveLEFT = 1;
	bool CanIMoveRIGHT = 1;
	bool CanIMoveUP = 1;
	bool CanIMoveDAUN = 1;

	bool haveWeapon = false;

	float MoveKeybordX = 0;
	float MoveKeybordY = 0;

	float MouseX = 0;
	float MouseY = 0;

	string tag = "Player";

private:
	Vector2f movementDir;
	Vector2f m_aimOffset;
	Vector2f m_bodyOffset;
	Vector2f velocity;
	float m_aimRotation;
	float m_aimDistance;
	float m_speed;
	float speed = 10;
	float size;
};

class Enemy : public Entity
{
public:
	Enemy(Vector2f position, float size, float speed, Color color, float rotate) : n_speed(speed) {
		n_legs.setSize(Vector2f(size, size));
		n_legs.setOrigin(size / 2, size / 2);
		n_legs.setPosition(position);
		n_legs.setFillColor(Color::Cyan);

		n_body.setSize(Vector2f(size / 1.5, size / 1.5));
		n_body.setOrigin(size / 3, size / 3);
		n_body.setPosition(position);
		n_body.setFillColor(color);

		n_body.setRotation(rotate);
	}

	void Update(float& deltaTime, RenderWindow& window, vector<FloatRect>& Object, Player& player) {
		if(!isActive) n_body.setRotation(n_body.getRotation() + 100 * deltaTime);
		else n_body.setRotation((atan2(player.m_body.getPosition().y - n_body.getPosition().y, player.m_body.getPosition().x - n_body.getPosition().x)) * 180 / M_PI);
		Raycasts(Object, window, player);

		draw(window);
	}
	void Update(float& deltaTime, RenderWindow& window, vector<FloatRect>& Object) {
		draw(window);
	}

	void Raycasts(vector<FloatRect>& Object, RenderWindow& window, Player& player) {
		VertexArray line[45];
		int maxLine = 45;
		int angle = 180;

		int temp;
		for (int i = 0; i < angle; i += angle/maxLine)
		{
			line[i / (angle / maxLine)].setPrimitiveType(Lines);
			line[i / (angle / maxLine)].resize(2); // Изменение размера массива вершин

			temp = (angle / 2) - i;
			float rotationRadians = (n_body.getRotation() + temp) * M_PI / 180.0f; // Конвертация градусов в радианы
			sf::Vector2f direction(std::cos(rotationRadians), std::sin(rotationRadians));
			Raycast(n_body.getPosition(), direction, 500, line[i / (angle / maxLine)], Object, player);
			drawLine(window, line[i / (angle / maxLine)]);
		}
	}

	void Raycast(const sf::Vector2f& origin, const sf::Vector2f& direction, float maxDistance,sf::VertexArray& line, vector<FloatRect>& Object, Player& player)
	{
		line[0].position = n_body.getPosition();
		line[0].color = Color::Red;
		sf::Vector2f endPoint = origin + direction * maxDistance;

		// Проходим по всем точкам луча
		for (float distance = 0.0f; distance <= maxDistance; distance += 1.0f)
		{
			sf::Vector2f point = origin + direction * distance;

			for (auto& objt : Object)
			{
				// Проверяем, попадает ли точка в пределы препятствия
				if (objt.contains(point))
				{
					line[1].position = point;
					line[1].color = sf::Color::Red;
					return; // Луч пересекся с препятствием
				}
			}

			if (player.m_body.getGlobalBounds().contains(point))
			{
				line[1].position = point;
				line[1].color = sf::Color::Blue;
				isActive = true;
				return; // Луч пересекся с препятствием
			}
		}

		line[1].position = endPoint;
		line[1].color = sf::Color::Red;
		return; // Луч достиг предела без столкновения с препятствием
	}

	void drawLine(RenderWindow& window, VertexArray& line) {
		window.draw(line);
	}

	void draw(RenderWindow& window) {
		window.draw(n_legs);
		window.draw(n_body);
	}

private:
	RectangleShape n_legs; // Ноги
	RectangleShape n_body; // Тело
	bool isActive = false; // Это нужно чтобы в один момент он перестал двигаться и напал на игрока
	float n_speed; // Скорость
};

/////////////////////////////////
/// Враг пока что только бегает по точкам.
///
/////////////////////////////////

//int temp = 100;
//for (int i = 0; i < temp; i++)
//{
//	temp = (temp / 2) - i;
//	float rotationRadians = (n_body.getRotation() + temp) * M_PI / 180.0f; // Конвертация градусов в радианы
//	sf::Vector2f direction(std::cos(rotationRadians), std::sin(rotationRadians));
//	Raycast(n_body.getPosition(), direction, 400, line, Object, player);
//	temp = 100;
// 
// Версия 1.12
// Добавлен класс CameraRoll, теперь камера следует за игроком (Есть еще метод отдачи оружия находится в Makarov->void fire ).
// Чтобы менять чувстт. камеры это в DimaUpdate значение float