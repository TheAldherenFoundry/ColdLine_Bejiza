#pragma once
#include "Camera1488.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <list>
#include "Bullet.h"

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
		Kelab.followPlayer(player.m_legs.getPosition(), 0.04);
		Kelab.update(window);

		m_body.setPosition(m_legs.getPosition());

		// Используем установленный угол поворота прицела и смещение, чтобы установить его позицию
		m_aim.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		player.draw(window);
	}

	void update(float& deltaTime, RenderWindow& window, Player& player, bool x)
	{
		if (x)
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
		}
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
	Enemy(Vector2f position, float size, float speed, Color color, float rotate, Texture& texture, float weapCD, int passiveMod, int hp_) : n_speed(speed) {
		n_legs.setSize(Vector2f(size, size));
		n_legs.setOrigin(size / 2, size / 2);
		n_legs.setPosition(position);
		n_legs.setFillColor(Color::Yellow);

		n_body.setSize(Vector2f(size / 1.5, size / 1.5));
		n_body.setOrigin(size / 3, size / 3);
		n_body.setPosition(position);
		n_body.setFillColor(color);

		circle.setRadius(500.f);
		circle.setFillColor(sf::Color::Red);

		enemyHeight = size;
		enemyWidth = size;
		startPosition = position;
		startRotate = rotate;
		hp = hp_;

		passiveMode = passiveMod;

		cd = weapCD;

		n_sprite.setTexture(texture);
		n_sprite.setPosition(Vector2f(10000, 10000));

		n_body.setRotation(startRotate);
	}

	void Update(float& deltaTime, RenderWindow& window, vector<FloatRect>& Object, Player& player) {
		if (hp <= 0) isAlive = false;
		if (isAlive) {
		float circleX = (n_legs.getSize().x - circle.getRadius()) / 2.f + n_legs.getPosition().x;
		float circleY = (n_legs.getSize().y - circle.getRadius()) / 2.f + n_legs.getPosition().y;
		circle.setPosition(circleX - 250 , circleY - 250);
			if (!isActive) passive(deltaTime);
			else playerAttack(deltaTime, Object, player);
			Raycasts(Object, window, player);
			if (circle.getGlobalBounds().intersects(player.m_legs.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left) && isActive == false) {
				isActive = true;
				newPointPosition = player.m_legs.getPosition();
				time = 2.f;
			}
			if (isFire) a = true;
			if (a) {
				if (!isFire && newPointPosition.x == 0 && newPointPosition.y == 0) {
					newPointPosition = player.m_body.getPosition();
				}
			}
			if (!isFire) a = false;
			draw(window);
		}
	}

	void Update(float& deltaTime, RenderWindow& window, vector<FloatRect>& Object) {
		draw(window);
	}

	void Raycasts(vector<FloatRect>& Object, RenderWindow& window, Player& player) {
		VertexArray line[4];
		int maxLine = 4;
		int angle = 100;

		isFire = false;
		see = false;
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
				isFire = true;
				see = true;
				return; // Луч пересекся с препятствием
			}
		}

		line[1].position = endPoint;
		line[1].color = sf::Color::Red;
		return; // Луч достиг предела без столкновения с препятствием
	}

	void passive(float& dt) {
		if (!goStartRotate) {
			if (passiveMode == 0) {
				n_body.setRotation(startRotate);
			}
			if (passiveMode == 1) {
				if (temp > 0) {
					n_body.setRotation(n_body.getRotation() + 1);
					temp--;
				}
				if (temp <= 0) {
					n_body.setRotation(n_body.getRotation() - 1);
					temp--;
				}
				if (temp <= -90) {
					temp = 90;
				}
			}
			if (passiveMode == 2) {
				n_body.setRotation(n_body.getRotation() + 1);
			}
			n_sprite.setPosition(Vector2f(10000, 10000));
		}
		else {
			float currentRotation = n_body.getRotation();
			float angleDiff = startRotate - currentRotation;

			// Нормализация угла
			while (angleDiff > 180.0f)
				angleDiff -= 360.0f;
			while (angleDiff < -180.0f)
				angleDiff += 360.0f;

			// Интерполяция поворота
			float rotationStep = 100 * dt;

			if (std::abs(angleDiff) <= rotationStep)
			{
				n_body.setRotation(startRotate);
			}
			else
			{
				float rotationDirection = (angleDiff > 0.0f) ? 1.0f : -1.0f;
				float newRotation = currentRotation + rotationStep * rotationDirection;
				n_body.setRotation(newRotation);
			}
			if (n_body.getRotation() == startRotate) goStartRotate = false;
		}
	}

	void playerAttack(float& dt, vector<FloatRect>& Object, Player& player) {
		if (see) {
			float targetAngle = atan2(player.m_body.getPosition().y - n_body.getPosition().y, player.m_body.getPosition().x - n_body.getPosition().x);

			// Переводим углы в градусы
			float currentAngle = n_body.getRotation();
			float targetAngleDegrees = targetAngle * 180 / M_PI;

			// Вычисляем разницу между текущим и целевым углом поворота
			float angleDiff = targetAngleDegrees - currentAngle;

			// Нормализуем разницу углов в диапазон от -180 до 180 градусов
			if (angleDiff > 180) {
				angleDiff -= 360;
			}
			else if (angleDiff < -180) {
				angleDiff += 360;
			}

			// Определяем скорость поворота (здесь можно настроить подходящее значение)
			float rotationSpeed = 90.0f;

			// Интерполируем угол поворота плавно с помощью скорости
			float rotationStep = rotationSpeed * dt; // deltaTime - время между кадрами

			if (abs(angleDiff) <= rotationStep) {
				// Если разница углов меньше шага поворота, просто устанавливаем целевой угол
				n_body.setRotation(targetAngleDegrees);
			}
			else {
				// В противном случае, изменяем текущий угол на шаг поворота
				if (angleDiff > 0) {
					currentAngle += rotationStep;
				}
				else {
					currentAngle -= rotationStep;
				}

				// Устанавливаем новый угол поворота объекта
				n_body.setRotation(currentAngle);
			}
			time1 = 0;
		}
		else {
			time1 += dt;
		}

		if (!isFire && time1 > 2.f && dir == 0) {
			// Задаем начальную и конечную позиции
			sf::Vector2f startPositio = n_legs.getPosition();
			sf::Vector2f targetPosition = newPointPosition;

			// Задаем скорость перемещения (здесь можно настроить подходящее значение)
			float moveSpeed = 100.0f; // пикселей в секунду

			// Вычисляем вектор направления и длину перемещения
			sf::Vector2f direction = targetPosition - startPositio;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			// Нормализуем вектор направления
			if (distance > 0.0f) {
				direction /= distance;
			}

			// Вычисляем скорость перемещения на каждом кадре
			float moveDistance = moveSpeed * dt;

			// Проверяем, достигнута ли конечная позиция
			if (distance <= moveDistance) {
				// Если расстояние меньше или равно расстоянию, которое можно пройти за один кадр, перемещаемся в конечную позицию
				n_legs.setPosition(targetPosition);
				dir++;
			}
			else {
				// Иначе перемещаемся вдоль вектора направления на расстояние, соответствующее скорости перемещения на текущем кадре
				sf::Vector2f displacement = direction * moveDistance;
				n_legs.setPosition(startPositio + displacement);
			}

			// Вычисляем угол между текущим направлением объекта и вектором, указывающим на конечную позицию
			float angle = std::atan2(targetPosition.y - startPosition.y, targetPosition.x - startPosition.x) * 180 / M_PI;

			// Поворачиваем объект на вычисленный угол
			n_body.setRotation(angle);
		}

		if (!isFire && dir == 1 && time1 > 2.f) {
			if (numerator > 0) {
				n_body.setRotation(n_body.getRotation() + 1);
				if (numOff) {
					dir++;
				}
			}
			if (numerator <= 0) {
				n_body.setRotation(n_body.getRotation() - 1);
			}
			numerator--;
			if (numerator == -60) {
				numerator = 60;
				numOff = true;
			}
		}

		if (!isFire && dir == 2) {
			float targetAngle = atan2(startPosition.y - n_body.getPosition().y, startPosition.x - n_body.getPosition().x);

			// Переводим углы в градусы
			float currentAngle = n_body.getRotation();
			float targetAngleDegrees = targetAngle * 180 / M_PI;

			// Вычисляем разницу между текущим и целевым углом поворота
			float angleDiff = targetAngleDegrees - currentAngle;

			// Нормализуем разницу углов в диапазон от -180 до 180 градусов
			if (angleDiff > 180) {
				angleDiff -= 360;
			}
			else if (angleDiff < -180) {
				angleDiff += 360;
			}

			// Определяем скорость поворота (здесь можно настроить подходящее значение)
			float rotationSpeed = 90.0f;

			// Интерполируем угол поворота плавно с помощью скорости
			float rotationStep = rotationSpeed * dt; // deltaTime - время между кадрами

			if (abs(angleDiff) <= rotationStep) {
				// Если разница углов меньше шага поворота, просто устанавливаем целевой угол
				n_body.setRotation(targetAngleDegrees);
			}
			else {
				// В противном случае, изменяем текущий угол на шаг поворота
				if (angleDiff > 0) {
					currentAngle += rotationStep;
				}
				else {
					currentAngle -= rotationStep;
				}

				// Устанавливаем новый угол поворота объекта
				n_body.setRotation(currentAngle);
			}

			// Задаем начальную и конечную позиции
			sf::Vector2f startPositio = n_legs.getPosition();
			sf::Vector2f targetPosition = startPosition;

			// Задаем скорость перемещения (здесь можно настроить подходящее значение)
			float moveSpeed = 100.0f; // пикселей в секунду

			// Вычисляем вектор направления и длину перемещения
			sf::Vector2f direction = targetPosition - startPositio;
			float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

			// Нормализуем вектор направления
			if (distance > 0.0f) {
				direction /= distance;
			}

			// Вычисляем скорость перемещения на каждом кадре
			float moveDistance = moveSpeed * dt;

			// Проверяем, достигнута ли конечная позиция
			if (distance <= moveDistance) {
				// Если расстояние меньше или равно расстоянию, которое можно пройти за один кадр, перемещаемся в конечную позицию
				n_legs.setPosition(targetPosition);
				dir++;
			}
			else {
				// Иначе перемещаемся вдоль вектора направления на расстояние, соответствующее скорости перемещения на текущем кадре
				sf::Vector2f displacement = direction * moveDistance;
				n_legs.setPosition(startPositio + displacement);
			}
		}

		if (!isFire && dir == 3) {
			isActive = false;
			temp = 45;
			dir = 0;
			numOff = false;
			numerator = 60;
			goStartRotate = true;
			newPointPosition = Vector2f(0,0);
		}

		n_body.setPosition(n_legs.getPosition());

		// Стрельба

		n_sprite.setRotation(n_body.getRotation());
		n_sprite.setPosition(n_body.getPosition());
		if (isFire && cd > time) {
			time = 0;
			sf::FloatRect bounds = n_sprite.getGlobalBounds(); // Получаем глобальные ограничивающие прямоугольника спрайта
			sf::Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2); // Вычисляем центр спрайта
		}
		time += dt;
	}

	void drawLine(RenderWindow& window, VertexArray& line) {
		window.draw(line);
	}

	void draw(RenderWindow& window) {
		window.draw(n_legs);
		window.draw(n_body);
		window.draw(n_sprite);
	}

public:
	RectangleShape n_legs; // Ноги
	RectangleShape n_body; // Тело
	sf::CircleShape circle;
	Sprite n_sprite;
	bool isActive = false; // Это нужно чтобы в один момент он перестал двигаться и напал на игрока
	bool isFire = false;
	bool isAlive = true;
	bool a = false;
	bool see = false;
	bool onPos = false;
	bool numOff = false;
	bool II_Mode = 1;
	bool goStartRotate = false;
	int dir = 0;
	int passiveMode;
	int temp = 45;
	int hp = 3;
	float n_speed; // Скорость
	float cd;
	float time = 0;
	float time1 = 0;
	float numerator = 60;
	float enemySpeed = 100.0f; // Скорость врага
	float enemyHeight;
	float enemyWidth;
	float startRotate;
	sf::Vector2f enemyPosition; // Позиция врага
	sf::Vector2f startPosition; // Позиция врага
	sf::Vector2f newPointPosition = Vector2f(0,0);
	sf::Vector2f enemyDirection; // Направление движения врага
	list<Vector2f> listPoints;
};