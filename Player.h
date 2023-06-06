#pragma once
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Joystick.hpp>
#include <iostream>

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

class Player
{
public:
    // ����������� ��������� ��������� ������� ������, ��� ������ � ����
    Player(Vector2f position, float size, float speed, Color color) : speed(speed) {
        m_legs.setSize(Vector2f(size, size));
        m_legs.setOrigin(size / 2, size / 2);
        m_legs.setPosition(position);
        m_legs.setFillColor(Color::Cyan);

        m_body.setSize(Vector2f(size / 1.5, size / 1.5));
        m_body.setOrigin(size / 3, size / 3);
        m_body.setPosition(position);
        m_body.setFillColor(color);

        m_aim.setSize(Vector2f(10, 10));
        m_aim.setOrigin(0.f, 0.f);
        m_aim.setFillColor(Color::Black);

        m_speed = speed;
        m_bodyOffset = Vector2f(-size / 4.f , size / 4.f );
        //m_aimOffset = Vector2f(size / 4.f, -size / 4.f);
        m_aimDistance = size + 300;

        this->size = size;
    }


    // ����� move ���������� ������ �� �������� ��������
    void move(const Vector2f& offset)
    {
        m_legs.move(offset);
    }

    // ����� draw ������������ ������ �� �������� ����
    void draw(RenderWindow& window) const
    {
        window.draw(m_legs);
        window.draw(m_body);
        window.draw(m_aim);                                            //   89191949864 - ����� ����������
    }

    void setPosition(float x, float y) {
        m_legs.setPosition(x, y);
        m_body.setPosition(x, y);
    }

    Vector2f getPosition() const {
        return m_legs.getPosition();
    }

    FloatRect getGlobalBounds() const {
        return m_legs.getGlobalBounds();
    }

    void setDirection(Vector2f direction)
    {
        movementDir = direction;
    }

    Vector2f getDirection()
    {
        return movementDir;
    }

    Vector2f getSize()
    {
        return m_legs.getSize();
    }

    void GiveMeMovePLS()
    {
        // ��� ��� ������!

        CanIMoveLEFT = 1;
        CanIMoveRIGHT = 1;
        CanIMoveUP = 1;
        CanIMoveDAUN = 1;

    };

    void handleGamepadInput(Joystick::Axis xAxis, Joystick::Axis yAxis, float deltaTime)
    {
        // �������� ��������� ������ �������� �� ���� x � y
        float x = Joystick::getAxisPosition(0, xAxis);
        float y = Joystick::getAxisPosition(0, yAxis);
        const float joystickThreshold = 50.f;

        // ��������� ����������� �������� ��������� � ����������� �� ��������� ������ ��������
        Vector2f movementDir;
        if (abs(x) > joystickThreshold || abs(y) > joystickThreshold) {
            movementDir = normalize(Vector2f(x, y));
        }

        // ������������ ���� ��������� � ����������� ��������
        if (movementDir.x != 0.f || movementDir.y != 0.f) {
            float angle = atan2(movementDir.y, movementDir.x) * 180.f / M_PI;
            m_legs.setRotation(angle);
        }

        // �������� ��������� �� ��� x
        if (x > joystickThreshold && CanIMoveRIGHT) {
            move(Vector2f(speed * deltaTime, 0.f));
        }
        else if (x < -joystickThreshold && CanIMoveLEFT) {
            move(Vector2f(-speed * deltaTime, 0.f));
        }

        // �������� ��������� �� ��� y
        if (y > joystickThreshold && CanIMoveDAUN) {
            move(Vector2f(0.f, speed * deltaTime));
        }
        else if (y < -joystickThreshold && CanIMoveUP) {
            move(Vector2f(0.f, -speed * deltaTime));
        }

        float u = Joystick::getAxisPosition(0, Joystick::V);
        float V = Joystick::getAxisPosition(0, Joystick::U);

        // ������������ ���� ��������� � ����������� ������� ����� ��������
        if (abs(u) > joystickThreshold || abs(V) > joystickThreshold) {
            Vector2f bodyDir = normalize(Vector2f(V, u));
            float bodyAngle = atan2(bodyDir.y, bodyDir.x) * 180.f / M_PI;
            m_body.setRotation(bodyAngle);
            m_aimRotation = bodyAngle;
        }

        // ������������ ���� ��������� � ����������� ������� ����� ��������
        if (abs(u) > joystickThreshold || abs(V) > joystickThreshold) {
            Vector2f bodyDir = normalize(Vector2f(V, u));
            float bodyAngle = atan2(bodyDir.y, bodyDir.x) * 180.f / M_PI;
            m_body.setRotation(bodyAngle);
            m_aimRotation = bodyAngle;
        }
    }

    void update(float deltaTime)
    {
        m_legs.move(velocity * deltaTime);

        // ������������� ������� ���� �� ������� ��� � ������ m_bodyOffset
        m_body.setPosition(m_legs.getPosition());

        // ������������� ������� ������� �� ������� ���� � ������ aimOffset
        Vector2f aimPos = m_body.getPosition() + m_aimOffset;
        m_aim.setPosition(aimPos);

        // ������������� ����� �������
        m_aim.setOrigin(m_aim.getLocalBounds().width / 2.f, m_aim.getLocalBounds().height / 2.f);

        // ������������� ���� �������� ������� �� m_aimRotation
        m_aim.setRotation(m_aimRotation);

        // ��������� ����� ������� ������
        Vector2f newPosition = m_legs.getPosition() + velocity * deltaTime;

        // ������� ��������� �������, ��������������� ����� ������� ������
        FloatRect newBounds = m_body.getGlobalBounds();
        newBounds.left = newPosition.x - m_bodyOffset.x;
        newBounds.top = newPosition.y - m_bodyOffset.y;

        // ��������� ������� ������ � ��� ��������
        m_legs.setPosition(newPosition);
        m_body.setPosition(m_legs.getPosition());

        // ���������� ������������� ���� �������� ������� � ��������, ����� ���������� ��� �������
        Transform aimTransform;
        aimTransform.rotate(m_aimRotation);
        Vector2f aimDirection = aimTransform.transformPoint(Vector2f(0.f, -m_aimDistance));
        m_aim.setPosition(m_body.getPosition() + m_aimOffset + aimDirection);
    }

    void DimaUpdate(float deltaTime, const RenderWindow& window, Player& player)
    {
        // ������������ �����������
        if (Keyboard::isKeyPressed(Keyboard::D) && CanIMoveRIGHT) { MoveKeybordX = 1 * deltaTime * speed; }
        if (Keyboard::isKeyPressed(Keyboard::A) && CanIMoveLEFT) { MoveKeybordX = -1 * deltaTime * speed; }
        if (Keyboard::isKeyPressed(Keyboard::W) && CanIMoveUP) { MoveKeybordY = 1 * deltaTime * speed; }
        if (Keyboard::isKeyPressed(Keyboard::S) && CanIMoveDAUN) { MoveKeybordY = -1 * deltaTime * speed; }
        if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) || (Keyboard::isKeyPressed(Keyboard::D) && CanIMoveRIGHT == 0) || (Keyboard::isKeyPressed(Keyboard::A) && CanIMoveLEFT == 0)) { MoveKeybordX = 0 * deltaTime * speed; }
        if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W) && CanIMoveUP == 0) || (Keyboard::isKeyPressed(Keyboard::S) && CanIMoveDAUN == 0)) { MoveKeybordY = 0 * deltaTime * speed; }
        //���� ������������
        move(Vector2f(MoveKeybordX, -MoveKeybordY));
        //�������� ������� ����
        Vector2i position = Mouse::getPosition(window);
        //�������� ���������� ������� ������������ player
        float MouseX = position.x - player.getPosition().x;
        float MouseY = -position.y + player.getPosition().y;

        //�������� ��� ��������
        float rotation = (atan2(MouseX, MouseY)) * 180 / M_PI;


        //������������
        player.m_aimRotation = rotation;

        player.GiveMeMovePLS();

        player.handleGamepadInput(Joystick::Axis::X, Joystick::Axis::Y, deltaTime); // ������������ ���� � ��������
    }





    float getspeed() const {
        return speed;
    }
    void setspeed(float speed_s){
        speed = speed_s;
    }


public:
    RectangleShape m_aim;

    bool CanIMoveLEFT = 1;
    bool CanIMoveRIGHT = 1;
    bool CanIMoveUP = 1;
    bool CanIMoveDAUN = 1;

    float MoveKeybordX = 0;
    float MoveKeybordY = 0;

    float MouseX = 0;
    float MouseY = 0;

private:
    // ������, ������������ ��� ��������� ������
    RectangleShape m_legs;
    RectangleShape m_body;
    Vector2f movementDir;
    Vector2f m_aimOffset;
    Vector2f velocity;

    float m_aimRotation;
    float m_aimDistance;
    float m_speed;
    float speed = 10;
    float size;

    Vector2f m_bodyOffset;
};
