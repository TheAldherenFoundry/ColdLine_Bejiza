#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include "Bullet.h"
#include "Particle_V_V.h"
#include "Textures.h"
#include <list>
#include "Entity.h"



using namespace sf;
using namespace std;


class Weapon {

};

class  Revolver_basic : public Weapon
{
public:
	Sprite m_sprite;
	Vector2f StartDropPosition;
	Vector2f DropPosition;
	bool isTaked;
	bool a = true;
	bool doTake = true;
	bool isKill = false;
	bool onPosition = true;
	int ammo = 7;
	int ammoNum = 0;
	float DropSight = 1.f;
	float DropSpeed = 800.f;
	float cooldown = 2.f;
	float time = 2.f;
private:
	list<Bullet9x18> m_listBullets;
	Bullet9x18 m_bullet;

public:
	Revolver_basic(Sprite& m_sprite, bool isTaked, Vector2f position) {
		this->m_sprite = m_sprite;
		this->isTaked = isTaked;
		DropPosition = position;
	}

	void update(float& dt, Player& player, RenderWindow& window, vector<FloatRect>& Object) {
		cooldown += dt;
		time += dt;
		if (!isTaked && onPosition == true) m_sprite.setPosition(DropPosition); // Позиция лежания/выкидываения
		if (m_sprite.getGlobalBounds().intersects(player.m_body.getGlobalBounds()) && !player.haveWeapon && time > 2) { // Поднятие
			isTaked = true;
			doTake = true;
			player.haveWeapon = true;
			onPosition = false;
		}
		if (isTaked && doTake) { // В руках
			m_sprite.setPosition(player.m_body.getPosition().x, player.m_body.getPosition().y);
			m_sprite.setRotation(player.m_body.getRotation());
			if (Mouse::isButtonPressed(Mouse::Right)) { // Выкидываем
				player.haveWeapon = false;
				doTake = false;
				isTaked = false;
				time = 0;
				DropSight = 1.f;
				a = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && ammoNum < ammo && cooldown > 0.3) {
				ammoNum++;
				cooldown = 0;
				sf::FloatRect bounds = m_sprite.getGlobalBounds(); // Получаем глобальные ограничивающие прямоугольника спрайта
				sf::Vector2f center(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2); // Вычисляем центр спрайта
				m_bullet.setPosition(center);
				m_bullet.SetRotation(m_sprite.getRotation() + 90);
				m_listBullets.push_back(m_bullet);
			}
		}
		if (!doTake) { // Выкинуто
			if (a) {//выполяется 1 раз
				StartDropPosition = player.m_body.getPosition();
				DropPosition = player.m_aim.getPosition();
			}
			a = false;
			isKill = true;
			for (auto& obj : Object) { //Проверка на столкновения
				if (m_sprite.getGlobalBounds().intersects(obj)) {

					sf::Vector2f directionVector = m_sprite.getPosition() - StartDropPosition;
					sf::Vector2f normalizedDirection = directionVector / std::sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);

					sf::Vector2f displacement = normalizedDirection * sqrt(DropPosition.x * StartDropPosition.x + DropPosition.y * StartDropPosition.y);;

					StartDropPosition = DropPosition;
					DropPosition = m_sprite.getPosition() + displacement;
				}
			}

			if (DropSight > 0.f) {//обновление полета оружия когда выкинуто
				sf::Vector2f direction = DropPosition - StartDropPosition;
				sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
				sf::Vector2f velocity = normalizedDirection * DropSpeed;
				sf::Vector2f displacement = velocity * dt;

				sf::Vector2f currentPosition = m_sprite.getPosition();
				currentPosition += displacement;
				m_sprite.setPosition(currentPosition);

				DropSight -= dt * DropSight; // Уменьшаем DropSight со скоростью, умноженной на dt
				if (DropSight < 0.1) DropSight = -1;
			}
		}
		for (auto& bullet : m_listBullets) { // Обновление пуль
			bullet.update(dt);
		}
		draw(window);
	}

	void draw(RenderWindow& window) {
		for (auto& bullet : m_listBullets) {
			bullet.draw(window);
		}
		window.draw(m_sprite);
	}

	void update(float& dt, RenderWindow& window) {

	}
};


//class Makarov : public Weapon {
//public:
//    Makarov() : Weapon()
//    {
//
//    }
//
//    Makarov(int Bullts, bool weapTake, Vector2f Pos) : Weapon(Bullts, weapTake, Pos)
//    {
//        Bullets = Bullts;
//        m_weapIsTaked = weapTake;
//
//        if (!weapTake)m_sprite.setPosition(Pos);
//
//    }
//
//    bool canFire() {
//        if (Bullets <= 0)return false;
//        else return m_cooldown <= 0; // Вывод можно ли стрелять
//    }
//    void fire(Player& pl, RenderWindow& window) {
//        if (Mouse::isButtonPressed(Mouse::Left) && m_weapIsTaked) {
//            if (canFire()) {
//                m_cooldown = m_fireRate;
//                Bullet9x18 bulletCopy;
//                bulletCopy.setSize(Vector2f(6.f, 12.f));
//                bulletCopy.setFillColor(Color::Red);
//                bulletCopy.setPosition(pl.getPosition());
//                bulletCopy.SetRotation(Rotate(pl, window));
//                m_listBullets.push_back(bulletCopy);
//            }
//        }
//    }
//
//    void update(float dt, Player& pl, RenderWindow& window, World ass)
//    {
//        WeaponUpdate(pl, window, dt);          //Покадровое обновление оружия
//
//        BulletUpdate(window, dt, ass);         //Покадровое обновление пуль
//
//        fire(pl, window);                      //Если нажата левая кнопка мыши то стреляет
//
//        DeleteBullet(window, ass, dt);         //Удаление пуль
//
//        draw(window);                          //Прорисовка оружия
//
//    }
//    // Покадровое обновление пуль
//    void BulletUpdate(RenderWindow& window, float dt, World ass) {
//        for (auto& Bullet : m_listBullets)                                                                           // Изменяем позицию и прорисовываем пулю
//        {
//            Bullet.draw(window);                                                                                     // прорисовка пули
//            Bullet.update(dt);
//        }
//        // Обновление частиц внутри класса Particle
//        m_particle.UpdateParticles(dt, ass);
//    }
//    void DeleteBullet(RenderWindow& window, World ass, float dt) {
//        const float reflectionDelay = 0.05f; // Задержка перед следующей проверкой отражения (в секундах)
//        static float timeSinceLastReflection = 0.0f; // Время прошедшее с последнего отражения
//
//        for (auto it = m_listBullets.begin(); it != m_listBullets.end();) {
//            bool shouldDelete = false;
//            auto& bullet = *it;
//
//            if (bullet.getPosition().x < 0 || bullet.getPosition().x > window.getSize().x
//                || bullet.getPosition().y < 0 || bullet.getPosition().y > window.getSize().y) {
//                shouldDelete = true;
//            }
//
//            bool collidedWithWall = false;
//            FloatRect bulletBounds = bullet.getGlobalBounds();
//            for (auto& wall : ass.m_walls) {
//                if (bulletBounds.intersects(wall.getGlobalBounds())) {
//                    collidedWithWall = true;
//                    Vector2f wallCenter = wall.getPosition() + Vector2f(wall.getSize().x / 2.f, wall.getSize().y / 2.f);
//                    Vector2f bulletDirection = wallCenter - bullet.getPosition();
//                    float bulletAngle = atan2(bulletDirection.y, bulletDirection.x) * 180.f / static_cast<float>(M_PI);
//                    float reflectedAngle = 180.f - bulletAngle;
//
//                    m_particle.Partickle_HLOPOK(bullet.getPosition(), reflectedAngle);
//
//                    // Зеркальное отображение направления пули
//                    bullet.SetDirect(Vector2f(-bullet.GetDirect().x, -bullet.GetDirect().y));
//
//                    break;
//                }
//            }
//
//            if (shouldDelete && timeSinceLastReflection >= reflectionDelay) {
//                it = m_listBullets.erase(it);
//                timeSinceLastReflection = 0.0f;
//            }
//            else if (collidedWithWall && timeSinceLastReflection >= reflectionDelay) {
//                timeSinceLastReflection = 0.0f;
//                ++it;
//            }
//            else {
//                timeSinceLastReflection += dt;
//                ++it;
//            }
//        }
//    }
//    void draw(RenderWindow& window) {
//        window.draw(m_sprite); // Отрисовка орудия
//        // Отрисовка частиц внутри класса Particle
//        m_particle.DrawParticles(window);
//    }
//
//private:
//    Bullet9x18 m_bullet;
//    // Это лист    
//    list<Bullet9x18> m_listBullets;
//};
//// хаймарс
//
//
//
//class Shotgun : public Weapon {
//public:
//
//    Shotgun(Texture& texture, Texture& bullet, int Bullts, bool weapTake) : Weapon(texture, 1.5f, weapTake)
//    {
//
//    }
//};
