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
	Vector2f position;
	bool isTaked;
	int ammo = 7;
private:

public:
	Revolver_basic(Sprite& m_sprite, bool isTaked, Vector2f position) {
		this->m_sprite = m_sprite;
		this->isTaked = isTaked;
		m_sprite.setPosition(position);
	}

	void update(float& dt, Player& player, RenderWindow& window) {
		if (m_sprite.getGlobalBounds().intersects(player.m_body.getGlobalBounds()) && player.haveWeapon) isTaked = true;
		if (isTaked) {
			m_sprite.setPosition(player.m_body.getPosition().x, player.m_body.getPosition().y);
			m_sprite.setRotation(player.m_body.getRotation());
		}
		draw(window);
	}

	void draw(RenderWindow& window) {
		window.draw(m_sprite);
	}

	void update(float& dt, RenderWindow& window) {

	}

private:

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
//        else return m_cooldown <= 0; // ����� ����� �� ��������
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
//        WeaponUpdate(pl, window, dt);          //���������� ���������� ������
//
//        BulletUpdate(window, dt, ass);         //���������� ���������� ����
//
//        fire(pl, window);                      //���� ������ ����� ������ ���� �� ��������
//
//        DeleteBullet(window, ass, dt);         //�������� ����
//
//        draw(window);                          //���������� ������
//
//    }
//    // ���������� ���������� ����
//    void BulletUpdate(RenderWindow& window, float dt, World ass) {
//        for (auto& Bullet : m_listBullets)                                                                           // �������� ������� � ������������� ����
//        {
//            Bullet.draw(window);                                                                                     // ���������� ����
//            Bullet.update(dt);
//        }
//        // ���������� ������ ������ ������ Particle
//        m_particle.UpdateParticles(dt, ass);
//    }
//    void DeleteBullet(RenderWindow& window, World ass, float dt) {
//        const float reflectionDelay = 0.05f; // �������� ����� ��������� ��������� ��������� (� ��������)
//        static float timeSinceLastReflection = 0.0f; // ����� ��������� � ���������� ���������
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
//                    // ���������� ����������� ����������� ����
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
//        window.draw(m_sprite); // ��������� ������
//        // ��������� ������ ������ ������ Particle
//        m_particle.DrawParticles(window);
//    }
//
//private:
//    Bullet9x18 m_bullet;
//    // ��� ����    
//    list<Bullet9x18> m_listBullets;
//};
//// �������
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
