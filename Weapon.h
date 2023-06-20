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
public:
	Sprite m_sprite;
	Clock clock;
	Clock removalTimer;

	Vector2f StartDropPosition;
	Vector2f DropPosition;

	bool isTaked;
	bool a = true;
	bool doTake = true;
	bool isKill = false;
	bool onPosition = true;
	bool oneKill = false;

	int ammo = 7;
	int ammoNum = 0;

	float epsilon = 1.0f;
	float reflectionCooldown = 0.0001;
	float removalCooldown = 0.001;
	float DropSight = 1.f;
	float DropSpeed = 800.f;
	float cooldown = 2.f;
	float cdFire = 0.3f;
	float time = 2.f;

	Particle Bullet_Particles;

private:
	list<Bullet9x18> m_listBullets;
	Bullet9x18 m_bullet;

public:
	virtual void update(float& dt, Player& player, RenderWindow& window, vector<FloatRect>& Object, vector<Enemy>& m_enemys) {
		oneKill = false;
		cooldown += dt;
		time += dt;
		if (!isTaked && onPosition == true) m_sprite.setPosition(DropPosition); // ������� �������/������������
		if (m_sprite.getGlobalBounds().intersects(player.m_body.getGlobalBounds()) && !player.haveWeapon && time > 2 && ammo != ammoNum) { // ��������
			isTaked = true;
			doTake = true;
			player.haveWeapon = true;
			onPosition = false;
		}
		if (isTaked && doTake) { // � �����
			m_sprite.setPosition(player.m_body.getPosition().x, player.m_body.getPosition().y);
			m_sprite.setRotation(player.m_body.getRotation());
			if (Mouse::isButtonPressed(Mouse::Right)) { // ����������
				player.haveWeapon = false;
				doTake = false;
				isTaked = false;
				time = 0;
				DropSight = 1.f;
				a = true;
			}
			if (Mouse::isButtonPressed(Mouse::Left) && ammoNum < ammo && cooldown > cdFire) {
				ammoNum++;
				cooldown = 0;
				sf::FloatRect bounds = m_sprite.getGlobalBounds(); // �������� ���������� �������������� �������������� �������
				sf::Vector2f center(bounds.left + 3 + bounds.width/ 2,bounds.top + 3 + bounds.height / 2); // ��������� ����� �������
				m_bullet.setPosition(center);
				m_bullet.SetRotation(m_sprite.getRotation() + 90);
				m_listBullets.push_back(m_bullet);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && ammoNum >= ammo && cooldown > cdFire) {
				player.haveWeapon = false;
				doTake = false;
				isTaked = false;
				time = 0;
				DropSight = 1.f;
				a = true;
			}
		}
		if (!doTake) { // ��������
			if (a) {//���������� 1 ���
				StartDropPosition = player.m_body.getPosition();
				DropPosition = player.m_aim.getPosition();
			}
			a = false;
			isKill = true;
			for (auto& obj : Object) { //�������� �� ������������
				if (m_sprite.getGlobalBounds().intersects(obj)) {
					DropSight = -1;
					time = 2.f;
				}
			}

			if (DropSight > 0.f) {//���������� ������ ������ ����� ��������
				sf::Vector2f direction = DropPosition - StartDropPosition;
				sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
				sf::Vector2f velocity = normalizedDirection * DropSpeed;
				sf::Vector2f displacement = velocity * 5.f * dt;

				sf::Vector2f currentPosition = m_sprite.getPosition();
				currentPosition += displacement;
				m_sprite.setPosition(currentPosition);

				DropSight -= dt * DropSight; // ��������� DropSight �� ���������, ���������� �� dt
				if (DropSight < 0.1) DropSight = -1;
			}
		}
		for (auto bullet = m_listBullets.begin(); bullet != m_listBullets.end(); ) {
			bullet->update(dt);
			bool shouldRemoveBullet = false;
			for (const auto& object : Object) {
				if (bullet->getGlobalBounds().intersects(object)) {
					// ��������� ���� ���������
					if (rand() % 100 <= 10) {
						oneKill = true;
						// ��������� �������� ���������
						if (clock.getElapsedTime().asSeconds() >= reflectionCooldown) {
							if (bullet->getPosition().y <= object.top + epsilon || bullet->getPosition().y >= object.top + object.height - epsilon) {
								// ���� ������ ����� ������� ��� ������ ������� �����
								float reflectionAngle = 2 * 90 - bullet->GetRotation() + rand() % 61 - 30;
								bullet->SetRotation(reflectionAngle);
								bullet->Bullet_Speed = bullet->Bullet_Speed / 2;
								Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle);
								// ��������� ��� ��������� ��������� ����...
							}
							else {
								// ���� ����������� � ������� �������� �����
								float reflectionAngle = 2 * 0 - bullet->GetRotation() + rand() % 61 - 30;
								bullet->SetRotation(reflectionAngle);
								bullet->Bullet_Speed = bullet->Bullet_Speed / 2;
								Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle);
								// ��������� ��� ��������� ��������� ����...
							}

							// ���������� ������ ��������
							clock.restart();
						}
					}
					else {
						shouldRemoveBullet = true;
						if (bullet->getPosition().y <= object.top + epsilon || bullet->getPosition().y >= object.top + object.height - epsilon) {
							// ���� ������ ����� ������� ��� ������ ������� �����
							float reflectionAngle = 2 * 90 - bullet->GetRotation();
							if (rand() % 100 <= 75)Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle + rand() % 30);
							// ��������� ��� ��������� ��������� ����...
						}
						else {
							// ���� ����������� � ������� �������� �����
							float reflectionAngle = 2 * 0 - bullet->GetRotation();
							if(rand() % 100 <= 75)Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle + rand() % 30);
							// ��������� ��� ��������� ��������� ����...
						}
					}
					
					break;
				}
			
			}
		
			for (auto& enem : m_enemys) {
				if (bullet->getGlobalBounds().intersects(enem.n_legs.getGlobalBounds())) {
					if (!oneKill) {
						enem.hp--;
						if (enem.isActive == false) {
							enem.newPointPosition = player.m_legs.getPosition();
							enem.isActive = true;
						}
					}
					else {
						enem.hp = 0;
					}
					shouldRemoveBullet = true;

				}
			}

			if (shouldRemoveBullet && removalTimer.getElapsedTime().asSeconds() >= removalCooldown) {
				bullet = m_listBullets.erase(bullet);
			}
			else {
				++bullet;
			}
			//}
		}
		for (const auto& object : Object) {
		Bullet_Particles.UpdateParticles(dt, object);
		}
		// ���������� ������ �������� ����
		if (removalTimer.getElapsedTime().asSeconds() >= removalCooldown) {
			removalTimer.restart();
		}

		draw(window);
	}

	virtual void draw(RenderWindow& window) {
		for (auto& bullet : m_listBullets) {
			bullet.draw(window);
		}
		window.draw(m_sprite);
		Bullet_Particles.DrawParticles(window);
	}

	virtual void update(float& dt, RenderWindow& window) {

	}
};

class  Revolver_basic : public Weapon
{
private:

	list<Bullet9x18> m_listBullets;
	Bullet9x18 m_bullet;

public:
	Revolver_basic(Texture& m_texture, bool isTaked, Vector2f position) {
		this->m_sprite.setTexture(m_texture);
		this->isTaked = isTaked;
		DropPosition = position;

		ammo = 7;
		ammoNum = 0;
		DropSight = 1.f;
		DropSpeed = 300.f;

		cooldown = 2.f;
	}
};

class  MiniCunn : public Weapon
{
private:

	list<Bullet9x18> m_listBullets;
	Bullet9x18 m_bullet;

	void draw(RenderWindow& window) {
		for (auto& bullet : m_listBullets) {
			bullet.draw(window);
		}
		window.draw(m_sprite);
		Bullet_Particles.DrawParticles(window);
	}

public:

	void update(float& dt, Player& player, RenderWindow& window, vector<FloatRect>& Object, vector<Enemy>& m_enemys) {
		oneKill = false;
		cooldown += dt;
		time += dt;
		if (!isTaked && onPosition == true) m_sprite.setPosition(DropPosition); // ������� �������/������������
		if (m_sprite.getGlobalBounds().intersects(player.m_body.getGlobalBounds()) && !player.haveWeapon && time > 2 && ammo != ammoNum) { // ��������
			isTaked = true;
			doTake = true;
			player.haveWeapon = true;
			onPosition = false;
		}
		if (isTaked && doTake) { // � �����
			m_sprite.setPosition(player.m_body.getPosition().x, player.m_body.getPosition().y);
			m_sprite.setRotation(player.m_body.getRotation());
			if (Mouse::isButtonPressed(Mouse::Right)) { // ����������
				player.haveWeapon = false;
				doTake = false;
				isTaked = false;
				time = 0;
				DropSight = 1.f;
				a = true;
			}
			// ������ ������ �������� ����� ��� ������� ����������
			if (Mouse::isButtonPressed(Mouse::Left) && ammoNum < ammo && cooldown > cdFire) {
				ammoNum++;
				cooldown = 0;

				sf::FloatRect bounds1 = m_sprite.getGlobalBounds(); // �������� ���������� �������������� �������������� ������� ����
				sf::Vector2f center1(bounds1.left + 5 + bounds1.width / 2, bounds1.top + 5 + bounds1.height / 2);
				m_bullet.setPosition(center1);
				m_bullet.SetRotation(m_sprite.getRotation() + 90);
				m_listBullets.push_back(m_bullet);

				sf::FloatRect bounds2 = m_sprite.getGlobalBounds(); // �������� ���������� �������������� �������������� ������� ����
				sf::Vector2f center2(bounds2.left - 6 + bounds2.width / 2, bounds2.top - 5 + bounds2.height / 2);
				m_bullet.setPosition(center2);
				m_bullet.SetRotation(m_sprite.getRotation() + 90);
				m_listBullets.push_back(m_bullet);
			}
			if (Mouse::isButtonPressed(Mouse::Left) && ammoNum >= ammo && cooldown > cdFire) {
				player.haveWeapon = false;
				doTake = false;
				isTaked = false;
				time = 0;
				DropSight = 1.f;
				a = true;
			}
		}
		if (!doTake) { // ��������
			if (a) {//���������� 1 ���
				StartDropPosition = player.m_body.getPosition();
				DropPosition = player.m_aim.getPosition();
			}
			a = false;
			isKill = true;
			for (auto& obj : Object) { //�������� �� ������������
				if (m_sprite.getGlobalBounds().intersects(obj)) {
					DropSight = -1;
					time = 2.f;
				}
			}

			if (DropSight > 0.f) {//���������� ������ ������ ����� ��������
				sf::Vector2f direction = DropPosition - StartDropPosition;
				sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
				sf::Vector2f velocity = normalizedDirection * DropSpeed;
				sf::Vector2f displacement = velocity * 5.f * dt;

				sf::Vector2f currentPosition = m_sprite.getPosition();
				currentPosition += displacement;
				m_sprite.setPosition(currentPosition);

				DropSight -= dt * DropSight; // ��������� DropSight �� ���������, ���������� �� dt
				if (DropSight < 0.1) DropSight = -1;
			}
		}
		for (auto bullet = m_listBullets.begin(); bullet != m_listBullets.end(); ) {
			bullet->update(dt);
			bool shouldRemoveBullet = false;
			for (const auto& object : Object) {
				if (bullet->getGlobalBounds().intersects(object)) {
					// ��������� ���� ���������
					if (rand() % 100 <= 10) {
						oneKill = true;
						// ��������� �������� ���������
						if (clock.getElapsedTime().asSeconds() >= reflectionCooldown) {
							if (bullet->getPosition().y <= object.top + epsilon || bullet->getPosition().y >= object.top + object.height - epsilon) {
								// ���� ������ ����� ������� ��� ������ ������� �����
								float reflectionAngle = 2 * 90 - bullet->GetRotation() + rand() % 61 - 30;
								bullet->SetRotation(reflectionAngle);
								bullet->Bullet_Speed = bullet->Bullet_Speed / 2;
								Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle);
								// ��������� ��� ��������� ��������� ����...
							}
							else {
								// ���� ����������� � ������� �������� �����
								float reflectionAngle = 2 * 0 - bullet->GetRotation() + rand() % 61 - 30;
								bullet->SetRotation(reflectionAngle);
								bullet->Bullet_Speed = bullet->Bullet_Speed / 2;
								Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle);
								// ��������� ��� ��������� ��������� ����...
							}

							// ���������� ������ ��������
							clock.restart();
						}
					}
					else {
						shouldRemoveBullet = true;
						if (bullet->getPosition().y <= object.top + epsilon || bullet->getPosition().y >= object.top + object.height - epsilon) {
							// ���� ������ ����� ������� ��� ������ ������� �����
							float reflectionAngle = 2 * 90 - bullet->GetRotation();
							if (rand() % 100 <= 75)Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle + rand() % 30);
							// ��������� ��� ��������� ��������� ����...
						}
						else {
							// ���� ����������� � ������� �������� �����
							float reflectionAngle = 2 * 0 - bullet->GetRotation();
							if (rand() % 100 <= 75)Bullet_Particles.Partickle_HLOPOK(bullet->getPosition(), reflectionAngle + rand() % 30);
							// ��������� ��� ��������� ��������� ����...
						}
					}

					break;
				}

			}

			for (auto& enem : m_enemys) {
				if (bullet->getGlobalBounds().intersects(enem.n_legs.getGlobalBounds())) {
					if (!oneKill) {
						enem.hp--;
						if (enem.isActive == false) {
							enem.newPointPosition = player.m_legs.getPosition();
							enem.isActive = true;
						}
					}
					else {
						enem.hp = 0;
					}
					shouldRemoveBullet = true;

				}
			}

			if (shouldRemoveBullet && removalTimer.getElapsedTime().asSeconds() >= removalCooldown) {
				bullet = m_listBullets.erase(bullet);
			}
			else {
				++bullet;
			}
			//}
		}
		for (const auto& object : Object) {
			Bullet_Particles.UpdateParticles(dt, object);
		}
		// ���������� ������ �������� ����
		if (removalTimer.getElapsedTime().asSeconds() >= removalCooldown) {
			removalTimer.restart();
		}

		draw(window);
	}

	MiniCunn(Texture& m_texture, bool isTaked, Vector2f position) {
		this->m_sprite.setTexture(m_texture);
		this->isTaked = isTaked;
		DropPosition = position;

		ammo = 100;
		ammoNum = 0;
		DropSight = 0.5f;
		DropSpeed = 300.f;
		cdFire = 0.1f;

		cooldown = 0.1f;
	}
};
