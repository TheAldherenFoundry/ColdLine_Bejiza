#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Weapon.h"
#include "Entity.h"

using namespace sf;
using namespace std;

// ��� ����� ��� - (������) ���� - ������. ��� �� ������ ������� �����, ����� �����, �����, ������, �����, ����
struct OMD_MAIN {
protected:
    Sprite m_detail; // ������� ����� �������
    bool CIMOVEONTHIS; // � ���� ��������� �� ���?                                  i
    bool ITSINTERECTIVE;// ��� ������������� ����?
    string name;
public:
    OMD_MAIN(Vector2f position, Texture& x) {
        m_detail.setPosition(position);
        m_detail.setTexture(x);

    }
    // ��� �� ������� ������ ��������� ��� � bool, ����� ���������� ��������
    OMD_MAIN(string klichko, bool EbidoEbi, Texture KrasniyRog, bool gagababa)
    {

        name = klichko;
        CIMOVEONTHIS = EbidoEbi;
        m_detail.setTexture(KrasniyRog);
        ITSINTERECTIVE = gagababa;

    }

    // ���� ���� ������ �������� ������������� � ���� ������ ���������� ���������, ���� ���, �� ������ ������
    void Update(RenderWindow& babadjon)
    {
        babadjon.draw(m_detail);

        if (ITSINTERECTIVE)
        {
            // ��� � ������� ���������� �������� ��� ��� ������� ������ ���������� �������
            // � ��� ����� ������ ����� ��������� ����� ����
        }
    }

};

struct TextureGrid
{
    TEXTURES_MODULE& textureModule; // ������ �� ������ ������ Texture_Module
    std::vector<sf::Sprite> sprites;

    TextureGrid(TEXTURES_MODULE& tm) : textureModule(tm)
    {
        // �������� �������� ��� ������ �������� � Texture_Module
        for (const auto& texture : textureModule.GetAllOMDTextures())
        {
            sf::Sprite sprite(texture);
            sprites.push_back(sprite);
        }

        // ������������ �������� � �����
        const int gridSizeX = 5; // ���������� ��������
        const int gridSizeY = 3; // ���������� �����
        const float spriteSize = 100.f; // ������ �������

        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int x = 0; x < gridSizeX; ++x)
            {
                int index = x + y * gridSizeX; // ������ ������� � ������� sprites
                if (index < sprites.size())
                {
                    sprites[index].setPosition(x * spriteSize, y * spriteSize);
                }
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
        for (const auto& sprite : sprites)
        {
            window.draw(sprite);
        }
    }
};

// �� ��� �����, �������?
struct TrailSegment {
    sf::Vector2f position;  // ������� �������� �����
    sf::Color color;       // ���� �������� �����
    float transparency;    // ������������ �������� �����
    float size;            // ������ �������� �����
};

class Wall {
protected:
    Vector2f angle_x;
    Vector2f angle_y;

    Vector2f getSize() const
    {
        return m_body.getScale();
    }

    Vector2f getPosition() const
    {
        return m_body.getPosition();
    }

    
    
    int getStepenBrankera()
    {
        return StepenBrankera;
    }
    Vector2f getNormal() const {
    // �������� ������� � ������� �����
    Vector2f position = getPosition();
    Vector2f size = getSize();

    // ��������� ����� �����
    Vector2f center = position + size / 2.f;

    // ��������� ����� �� �����, �� ������� ����� ���� �������
    // � ������ ������� �������� �������� ������ ���� �����
    Vector2f pointOnWall = Vector2f(position.x, center.y);

    // ��������� ������ �� ����� �� ����� � ������ �����
    Vector2f wallToCenter = center - pointOnWall;

    // ����������� ������, ����� �������� ��������� �������
    Vector2f normal = normalize(wallToCenter);

    return normal;
}
public:
    void CheckPaterochka(Player& Vladimir)
    {
        if (Vladimir.m_legs.getGlobalBounds().intersects(getGlobalBounds())) {
            sf::Vector2f playerPosition = Vladimir.m_legs.getPosition();
            sf::FloatRect objectBounds = getGlobalBounds();

            if (playerPosition.x < objectBounds.left) {
                Vladimir.CanIMoveRIGHT = false;
            }

            if (playerPosition.x > objectBounds.left + objectBounds.width) {
                Vladimir.CanIMoveLEFT = false;
                
            }

            if (playerPosition.y < objectBounds.top ) {
                Vladimir.CanIMoveDAUN = false;
            
            }

            if (playerPosition.y > objectBounds.top + objectBounds.height) {
                 Vladimir.CanIMoveUP = false;
                
            }
        }
    }
    /*void CheckPaterochka(Bull& Vladimir) // ��� �������� ������������ � �����
    {
        if (Vladimir.getGlobalBounds().intersects(getGlobalBounds())) {
            
            // ���� ���� ������� �� ���

        }
    }*/

    void DrawGodLines(Player& Vladimir, FloatRect xy, RenderWindow& o)
    {
        sf::Vertex lineUp[] =
        {
            sf::Vertex(sf::Vector2f(xy.left, xy.top)),
            sf::Vertex(sf::Vector2f(xy.left + xy.width, xy.top))
        };
        sf::Vertex lineRight[] =
        {
            sf::Vertex(sf::Vector2f(xy.left + xy.width, xy.top)),
            sf::Vertex(sf::Vector2f(xy.left + xy.width, xy.top + xy.height))
        };
        sf::Vertex lineLeft[] =
        {
            sf::Vertex(sf::Vector2f(xy.left, xy.top)),
            sf::Vertex(sf::Vector2f(xy.left, xy.top + xy.height))
        };
        sf::Vertex lineDown[] =
        {
            sf::Vertex(sf::Vector2f(xy.left, xy.top + xy.height)),
            sf::Vertex(sf::Vector2f(xy.left + xy.width, xy.top + xy.height))
        };

        lineDown->color = Color::Red;
        lineUp->color = Color::Red;
        lineLeft->color = Color::Red;
        lineRight->color = Color::Red;
        

        o.draw(lineUp, 2, Lines);
        o.draw(lineDown, 2, Lines);

        o.draw(lineLeft, 2, Lines);
        o.draw(lineRight, 2, Lines);
    } 
    public:
    
        sf::Vector2f WallCenter(const sf::FloatRect& wallBounds)
        {
            float centerX = wallBounds.left + wallBounds.width / 2;
            float centerY = wallBounds.top + wallBounds.height / 2;
            return sf::Vector2f(centerX, centerY);
        }

    Sprite GetShape()
    {
        return m_body;
    }

    void update(RenderWindow& window)  {
       
        window.draw(m_body);
    }
    void update(RenderWindow& window, Player& Vladimir) {

        window.draw(m_body);
        if (GODVIEW)DrawGodLines(Vladimir, getGlobalBounds(), window);
    }
    FloatRect getGlobalBounds() const {
        return m_body.getGlobalBounds();
    }

    //Wall() {} // ����������� ���� ���� 
    Wall(Vector2f position, Texture& texture){
        m_body.setPosition(position);
        m_body.setTexture(texture);
        StepenBrankera = 4;
        hp = 100;
        GODVIEW = 0;
    }

protected:
    int hp;
    Sprite m_body;
    bool GODVIEW = true; 
    int StepenBrankera; // 0 - ���������� 1 - ������ 2 - ����� 3 - ��������� ���� 4 - ��������  (1 � 2 �� ������ ����) 2 - ����� ������������� �����
};

class Door : public Wall { // �� �� ������� � ��������� ����� ����� �������, ������� �������� ����� �� ������� ������� ���� ������. � ������� ������� ������ World ����� ������� "������ ��������" ��� ����������� ��������� �������.
public:
    
    Door(Vector2f position, Texture& texture) : Wall(position, texture){ 

        StepenBrankera = 2;
        hp = 100;
    }
};

class World {
public:

    bool CREATIVE_MODE = 0;

    // ��� �� ��������� ������
    vector<Revolver_basic> m_Revolver_basic;
    // ��� �� ��������� ������� ����
    vector<Wall> m_walls;
    vector<Door> m_doora;
    vector<Enemy> m_enemys;
    vector<OMD_MAIN> m_other;

    vector<FloatRect> m_objects;

    TEXTURES_MODULE HAMLET;

    CircleShape Cursor;

    CameraRoll Kashtan;

private:

    vector<TrailSegment> trail;
    sf::VertexArray trailVertices;  // ������ ������ ��� ��������� �����
    Color RandCOlOR;

    const int worldWidth = 1000;   // ������ ����
    const int worldHeight = 1000;   // ������ ����
    const int squareSize = 32;     // ������ �������� 32 - ��� 1 ����

    // ��������� ���������� ��������� �� ����������� � ���������
    const int numSquaresX = worldWidth / squareSize;
    const int numSquaresY = worldHeight / squareSize;

    // ������� ��������� ������ ��� �������� ���������
    std::vector<sf::RectangleShape> squares;

    bool isMoving = false;  // ���� �����������
    bool isKeyPressed[10] = { false };
    bool isZoomHandled;

    float MoveKeybordX;
    float MoveKeybordY;

    float speed;

    int ColorRape = 1;
    int TextureIndex[2];
    /// /////////////////////////////////////

    void WeaponCONTROL();

    void UpdateParticles(float dt);

    void UpdateEnemys(float& deltaTime, RenderWindow& window, Player& player);

    void UpdateEnemys(float& deltaTime, RenderWindow& window);

    /// /////////////////////////////////////

    void CreateOBJ(RectangleShape& sprite);

    void ControlWCR(RenderWindow& window, float dt);

    void Movement(float deltaTime);

    void updateTrail(sf::Vector2f position);

public:

    void addWall(Vector2f position, Texture& texture)
    {
        m_walls.emplace_back(position,texture);
    }

    void add_Revolver_basic(Texture texture, bool isTaked, Vector2f position) // ������� ������ 
    {
        Sprite sprite;
        sprite.setTexture(texture);
        m_Revolver_basic.emplace_back(sprite, isTaked, position);
    }

    void add_Enemy(Vector2f position, float size, float speed, Color color, float rotate)
    {
        m_enemys.emplace_back(position, size, speed, color, rotate);
    }

    void addOMD(Vector2f position, Texture& texture)
    {
        m_other.emplace_back(position, texture);
    }

    void update(RenderWindow& window, Player& player_2, float dt) { // ������, ��������� ��������
        for (auto& wall : m_walls) {
            wall.update(window, player_2);
            wall.CheckPaterochka(player_2);
        }
        for (auto& door : m_doora) {
            door.update(window, player_2);
        }
        for (auto& makarov : m_Revolver_basic) {
            makarov.update(dt, player_2, window, m_objects, m_enemys);
        }
        if (!CREATIVE_MODE) {
            WeaponCONTROL();
            UpdateParticles(dt);
            UpdateEnemys(dt, window, player_2);
        }
        else {
            // ��������� ����
            for (const auto& square : squares)
            {
                window.draw(square);
            }

            for (auto& square : squares)
            {
                if (Cursor.getGlobalBounds().intersects(square.getGlobalBounds()))
                {
                    square.setFillColor(Color::Black);
                    CreateOBJ(square);
                }
                else square.setFillColor(Color::White);

            }
            Movement(dt);

            Kashtan.followPlayer(Cursor.getPosition(), 0.01);
            Kashtan.update(window);
            updateTrail(Cursor.getPosition());
            ControlWCR(window, dt);

            // ������������ ���� � �������������� ������� ������
            window.draw(trailVertices);
            window.draw(Cursor);
        }
    }

    void update(RenderWindow& window, float dt) { // ������, ��������� ��������
        for (auto& wall : m_walls) {
            wall.update(window);
        }
        for (auto& door : m_doora) {
            door.update(window);
        }
        for (auto& makarov : m_Revolver_basic) {
            makarov.update(dt, window);
        }
        if (!CREATIVE_MODE) {
            WeaponCONTROL();
            UpdateParticles(dt);
            UpdateEnemys(dt, window);
        }
        else {
            // ��������� ����

            for (const auto& square : squares)
            {
                window.draw(square);
            }

            for (auto& square : squares)
            {
                if (Cursor.getGlobalBounds().intersects(square.getGlobalBounds()))
                {
                    square.setFillColor(Color::Black);
                    CreateOBJ(square);
                }
                else square.setFillColor(Color::White);

            }
            for (auto& OMD : m_other) {
                OMD.Update(window);
            }
            Movement(dt);

            Kashtan.followPlayer(Cursor.getPosition(), 0.01);
            Kashtan.update(window);
            updateTrail(Cursor.getPosition());
            ControlWCR(window, dt);

            for (auto& walls : m_walls)
            {
                walls.update(window);
            }
            // ������������ ���� � �������������� ������� ������
            window.draw(trailVertices);
            window.draw(Cursor);

        }
    }


    void SetGlobalObjectBounds()
    {
        for (auto& door : m_doora) {
            m_objects.emplace_back(door.getGlobalBounds());
        }
        for (auto& wall : m_walls) {
            m_objects.emplace_back(wall.getGlobalBounds());
        }
        cout << "COMPLETE OBJECTS:" << m_objects.size() << endl;
    }

    bool CheckCollisions(const FloatRect& bulletBounds) const {
        bool collidedWithWall = false;
        for (const auto& wall : m_walls) {
            if (bulletBounds.intersects(wall.getGlobalBounds())) {
                collidedWithWall = true;
                break;
            }
        }

        bool collidedWithDoor = false;
        for (const auto& door : m_doora) {
            if (bulletBounds.intersects(door.getGlobalBounds())) {
                collidedWithDoor = true;
                break;
            }
        }

        return collidedWithWall || collidedWithDoor;
    }

    World(bool a) {

        CREATIVE_MODE = a;

        TextureGrid* Hey = new TextureGrid(HAMLET);

        if (CREATIVE_MODE) {

            // ������������� ����
            Cursor.setRadius(5);
            speed = 300;
            Cursor.setOrigin(5 / 2, 5 / 2);

            // ��������� ���������� ��������� �� ����������� � ���������
            const int numSquaresX = worldWidth / squareSize;
            const int numSquaresY = worldHeight / squareSize;

            // ��������� ����� ���������� ���������
            const int totalSquares = numSquaresX * numSquaresY;

            // ������� ������� ��������
            const float squareWidth = static_cast<float>(worldWidth) / numSquaresX;
            const float squareHeight = static_cast<float>(worldHeight) / numSquaresY;




            // ��������� ������ ����������
            for (int i = 0; i < totalSquares; ++i)
            {
                sf::RectangleShape square(sf::Vector2f(squareWidth, squareHeight));
                square.setOutlineThickness(1.0f);  // ������� �������
                square.setOutlineColor(sf::Color::Red);  // ���� �������
                square.setPosition(sf::Vector2f((i % numSquaresX) * squareWidth, (i / numSquaresX) * squareHeight));
                squares.push_back(square);
            }

            for (auto& square : squares)
            {
                if (Cursor.getGlobalBounds().intersects(square.getGlobalBounds()))
                {
                    square.setFillColor(Color::Black);
                    CreateOBJ(square);
                }
                else square.setFillColor(Color::White);

            }

        }
    }
};








//////////////////////////////////���������� �������/////////////////////////////////

void World::WeaponCONTROL()
{
    for (auto& revolver : m_Revolver_basic) {
        for (auto& door : m_doora) {
            //revolver.SetBulletDamage(door.getGlobalBounds(), door.WallCenter(door.getGlobalBounds()));
        }
        for (auto& wall : m_walls){
            //revolver.SetBulletDamage(wall.getGlobalBounds(), wall.WallCenter(wall.getGlobalBounds()));
        }
    }

}

void World::UpdateParticles(float deltaTime)
{
    for (auto& revolver : m_Revolver_basic) {
        for (auto& door : m_doora) {
            //revolver.m_particle.UpdateParticles(deltaTime, door.GetShape());
        }
        for (auto& wall : m_walls) {
           // revolver.m_particle.UpdateParticles(deltaTime, wall.GetShape());
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////

void World::UpdateEnemys(float& deltaTime, RenderWindow& window, Player& player)
{   
    for (auto& enemy : m_enemys) {
            enemy.Update(deltaTime, window, m_objects, player);
    }
}

void World::UpdateEnemys(float& deltaTime, RenderWindow& window)
{
    for (auto& enemy : m_enemys) {
        enemy.Update(deltaTime, window, m_objects);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
// ��� ��������� ���������
// .......................



void World::CreateOBJ(RectangleShape& sprite)
{
    // ��������� ��������� �������
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        if (!isKeyPressed[1])
        {
            addWall(sprite.getPosition(),HAMLET.GetWallTexture(1));
            cout << "Ok" << endl;
            isKeyPressed[1] = true;
        }
    }
    else
    {
        isKeyPressed[1] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        if (!isKeyPressed[2])
        {
            cout << "Ok" << endl;
            addOMD(sprite.getPosition(), HAMLET.GetOMDTexture(11));
            isKeyPressed[2] = true;
        }
    }
    else
    {
        isKeyPressed[2] = false;
    }

}

void World::ControlWCR(RenderWindow & window, float dt)
{
    // ��������� ��������� �������
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (!isKeyPressed[0])
        {
            std::cout << 1 / dt << std::endl;
            isKeyPressed[0] = true;
        }
    }
    else
    {
        isKeyPressed[0] = false;
    }


    // ��������� ��������� ������ "+" � "-"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
    {
        // ����������� ���
        Kashtan.m_view.zoom(1.001f);  // �������� 1.1 �� �������� ����������� ����
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
    {
        // ��������� ���
        Kashtan.m_view.zoom(0.999f);  // �������� 0.9 �� �������� ����������� ����
    }
}

void World::Movement(float deltaTime) {

    isMoving = false;
    // ������������ �����������
    if (Keyboard::isKeyPressed(Keyboard::D)) { MoveKeybordX = 1 * deltaTime * speed; isMoving = true;}
    if (Keyboard::isKeyPressed(Keyboard::A)) { MoveKeybordX = -1 * deltaTime * speed; isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::W)) { MoveKeybordY = 1 * deltaTime * speed; isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::S)) { MoveKeybordY = -1 * deltaTime * speed; isMoving = true; }
    Cursor.move(Vector2f(MoveKeybordX, -MoveKeybordY));
    if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) || (Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::A))) { MoveKeybordX = 0 * deltaTime * speed; }
    if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::S))) { MoveKeybordY = 0 * deltaTime * speed; }
}

void World::updateTrail(sf::Vector2f position)
{

    // ������� ��������� ������� �����, ���� ��� ���������� ��������� �������� �����
    const int maxTrailLength = 500;  // ������� �������� ����� �����
    if (trail.size() > maxTrailLength)
    {
        trail.pop_back();
    }

    // ��������� ����� ������� ����� � ������ ����������
    TrailSegment segment;
    segment.position = position;
    segment.transparency = 255;      // ������� ��������� ������������ �����
    trail.insert(trail.begin(), segment);

    // ��������� ������������ � ���� ������� �������� �����
    for (auto& segment : trail)
    {
        segment.transparency -= 1;  // ��������� ������������ �������� �����

        // ������������� ����� ������������ �������� �����
        segment.color.a = static_cast<sf::Uint8>(segment.transparency);

    }

    // ��������� ������ ������ ��� ��������� �����

    trailVertices.clear();

    // ��������� ������� � ������ ��� ������ ������� �����
    for (const auto& segment : trail)
    {
        if (ColorRape == 2) {
            sf::Vertex vertex(Vector2f(segment.position.x + 5, segment.position.y + 5), Color::Yellow);
            trailVertices.append(vertex);
            sf::Vertex vertex_1(Vector2f(segment.position.x + 2.5, segment.position.y + 2.5), Color::Yellow);
            trailVertices.append(vertex_1);
            sf::Vertex vertex_2(Vector2f(segment.position.x, segment.position.y), Color::Blue);
            trailVertices.append(vertex_2);
            sf::Vertex vertex_3(Vector2f(segment.position.x - 2.5, segment.position.y - 2.5), Color::Blue);
            trailVertices.append(vertex_3);
        }

        if (ColorRape == 1) {
            sf::Vertex vertex(Vector2f(segment.position.x - 5, segment.position.y - 5), Color::White);
            trailVertices.append(vertex);
            sf::Vertex vertex_1(Vector2f(segment.position.x - 2.5, segment.position.y - 2.5), Color::White);
            trailVertices.append(vertex_1);
            sf::Vertex vertex_2(Vector2f(segment.position.x + 1, segment.position.y + 1), Color::Blue);
            trailVertices.append(vertex_2);
            sf::Vertex vertex_3(Vector2f(segment.position.x - 1, segment.position.y - 1), Color::Blue);
            trailVertices.append(vertex_3);
            sf::Vertex vertex_4(Vector2f(segment.position.x + 2.5, segment.position.y + 2.5), Color::Red);
            trailVertices.append(vertex_4);
            sf::Vertex vertex_5(Vector2f(segment.position.x + 5, segment.position.y + 5), Color::Red);
            trailVertices.append(vertex_5);

        }
        if (ColorRape == 3) {
            sf::Vertex vertex(Vector2f(segment.position.x + 5, segment.position.y + 5), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex);
            sf::Vertex vertex_1(Vector2f(segment.position.x + 2.5, segment.position.y + 2.5), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex_1);
            sf::Vertex vertex_2(Vector2f(segment.position.x + 1, segment.position.y + 1), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex_2);
            sf::Vertex vertex_3(Vector2f(segment.position.x - 1, segment.position.y - 1), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex_3);
            sf::Vertex vertex_4(Vector2f(segment.position.x - 2.5, segment.position.y - 2.5), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex_4);
            sf::Vertex vertex_5(Vector2f(segment.position.x - 5, segment.position.y - 5), Color(rand() % 256, rand() % 256, rand() % 256));
            trailVertices.append(vertex_5);

        }

    }

}
///////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� 1.2 
// ����� ���������
// � ������� ������� ������ World ����� �������  ����������� ��������� �������.
// ��� ������ ��������������
////////////////////////////////////////////////////////////////////////////////////////////////////
// ����� ������� ������� ���� � ������������ ������ ����� � ����������� �� ������� ���� (��� ������ � ������� Bullet ����� �������)