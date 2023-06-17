#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

using namespace sf;
using namespace std;

vector<Texture> Textures_wall;
vector<Texture> Textures_Weapon;
vector<Texture> Textures_OMD;

/// ТЕКСТУРЫ СТЕНЫ
Texture Wall_1;
Texture Wall_2;
Texture Wall_1_2;
Texture Wall_2_2;


/// ТЕКСТУРЫ ЧАСТИЦ
Texture P1;
Texture P2;
Texture P3;
Texture P4;
Texture P5;
Texture P6;
Texture P7;
/// ТЕКСТУРЫ ЧАСТИЦ

/// ТЕКСТУРЫ ПУЛИ
Texture Bullet_9x18;
/// ТЕКСТУРЫ ПУЛИ

/// ТЕКСТУРЫ ОРУЖИЯ
Texture REVOLVER_BASIC;

// Тестуры остального
Texture OMD_1;
Texture OMD_2;
Texture OMD_3;
Texture OMD_4;
Texture OMD_5;
Texture OMD_6;
Texture OMD_7;
Texture OMD_8;
Texture OMD_9;
Texture OMD_10;
Texture OMD_11;

struct TEXTURES_MODULE
{
	TEXTURES_MODULE()
	{
		Wall_1.loadFromFile("image/Wall/Wall_Red_Brick_Main.png");
		Wall_1_2.loadFromFile("image/Wall/Wall_Red_Brick_UZEL.png");
		Wall_2.loadFromFile("image/Wall/Wall_White_Brick_Main.png");
		Wall_2_2.loadFromFile("image/Wall/Wall_White_Brick_UZEL.png");

		Textures_wall.push_back(Wall_1);
		Textures_wall.push_back(Wall_1_2);
		Textures_wall.push_back(Wall_2);
		Textures_wall.push_back(Wall_2_2);

		P1.loadFromFile("image/Particles/Particle_1.png");
		P2.loadFromFile("image/Particles/Particle_2.png");
		P3.loadFromFile("image/Particles/Particle_3.png");
		P4.loadFromFile("image/Particles/Particle_4.png");
		P5.loadFromFile("image/Particles/Particle_5.png");
		P6.loadFromFile("image/Particles/Particle_6.png");
		P7.loadFromFile("image/Particles/Particle_7.png");

		Bullet_9x18.loadFromFile("image/Particles/Bullet.png");

		REVOLVER_BASIC.loadFromFile("image/Revolver.png");

		Textures_Weapon.push_back(REVOLVER_BASIC);

		OMD_1.loadFromFile("image/Mebelgrad/Divan_1.png");
		OMD_2.loadFromFile("image/Mebelgrad/Divan_2.png");
		OMD_3.loadFromFile("image/Mebelgrad/Divan_3.png");
		OMD_4.loadFromFile("image/Mebelgrad/kolonki.png");
		OMD_5.loadFromFile("image/Mebelgrad/Kreslo_1.png");
		OMD_6.loadFromFile("image/Mebelgrad/Kreslo_2.png");
		OMD_7.loadFromFile("image/Mebelgrad/Kreslo_3.png");
		OMD_8.loadFromFile("image/Mebelgrad/Kreslo_4.png");
		OMD_9.loadFromFile("image/Mebelgrad/shtora.png");
		OMD_10.loadFromFile("image/Mebelgrad/Table_TV.png");
		OMD_11.loadFromFile("image/Mebelgrad/bed_1.png");
		
		Textures_OMD.push_back(OMD_1);
		Textures_OMD.push_back(OMD_2);
		Textures_OMD.push_back(OMD_3);
		Textures_OMD.push_back(OMD_4);
		Textures_OMD.push_back(OMD_5);
		Textures_OMD.push_back(OMD_6);
		Textures_OMD.push_back(OMD_7);
		Textures_OMD.push_back(OMD_8);
		Textures_OMD.push_back(OMD_9);
		Textures_OMD.push_back(OMD_10);
		Textures_OMD.push_back(OMD_11);
	}

	vector<Texture>& GetAllOMDTextures()
	{
		
			return Textures_OMD;
		
	}

	const sf::Texture* Give_Me_Random_Praticle_Texture()
	{
		// Массив доступных текстур
		const sf::Texture* textures[] = { &P1, &P2, &P3, &P4, &P5, &P6, &P7 };

		// Получаем случайный индекс текстуры
		int randomIndex = rand() % (sizeof(textures) / sizeof(textures[0]));
		// Возвращаем указатель на случайную текстуру
		return textures[randomIndex];
	}

	// 1 - Револьвер....
	Texture& GetWeaponTexture(int x)
	{
		return REVOLVER_BASIC;
	}

	// 1 - Red, 2 - Red_Uzel, 3 - White, 4 - White_Uzel
	Texture& GetWallTexture(int x)
	{
		switch (x)
		{
		case 1:
			return Wall_1;
			break;
		case 2:
			return Wall_1_2;
			break;
		case 3:
			return Wall_2;
			break;
		case 4:
			return Wall_2_2;
			break;
		default:
			return Wall_1;
		}
	}
	Texture& GetOMDTexture(int x)
	{
		switch (x)
		{
		case 1:
			return OMD_1;
			break;
		case 2:
			return OMD_2;
			break;
		case 3:
			return OMD_3;
			break;
		case 4:
			return OMD_4;
			break;
		case 5:
			return OMD_5;
			break;
		case 6:
			return OMD_6;
			break;
		case 7:
			return OMD_7;
			break;
		case 8:
			return OMD_8;
			break;
		case 9:
			return OMD_9;
			break;
		case 10:
			return OMD_10;
			break;
		case 11:
			return OMD_11;
			break;

		}
	}
	const Texture GetBulletTexture(int x) // 1 - 9x18....
	{
		switch (x)
		{
		case 1:
			return Bullet_9x18;
			break;
		}
	}
};