#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>
#include "World.h"

using namespace sf;
using namespace std;

struct TAF_CREATOR {
public:
    TAF_CREATOR() {
        window.create(VideoMode(800, 600), "TAF Creator");
        window.setMouseCursorVisible(false);
        window.setMouseCursorGrabbed(true);

        deltaClock.restart();
        deltaTime = 0.f;

        world = new World(1);
        world->SetGlobalObjectBounds();
    }

    void Extominate_world() {
        delete world;
    }

    void Update()
    {
        world->update(window, deltaTime);
    }

    RenderWindow window;
    float deltaTime;
    Clock deltaClock;
private:
    World* world;
};

struct Level
{
    Level() {
        window.create(VideoMode(800, 600), "TAF Creator");
        window.setMouseCursorVisible(false);
        window.setMouseCursorGrabbed(true);

        deltaClock.restart();
        deltaTime = 0.f;

        world = new World(0);
        
        Player* Hi = new Player(Vector2f(100.f, 100.f), 50.f, 300, Color::Red); // ������� ���������)
        world->SetGlobalObjectBounds();
    }

    void Extominate_world() {
        delete world;
    }

    void Update()
    {   
        Hi.update(deltaTime, window, Hi);                                                        
        world->update(window, Hi, deltaTime);                                         // ��������� ��������
        Hi.draw(window);
        world->update(window, deltaTime);
    }
    
    Player Hi;
    RenderWindow window;
    float deltaTime;
    Clock deltaClock;
private:
    World* world;
};