#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Weapon.h"
#include "Entity.h"

using namespace sf;
using namespace std;

// Это класс ОМД - (Другие) Мини - Детали. Тут мы делаем объекты карты, каран коран, флаги, стулья, столы, пиво
struct OMD_MAIN {
protected:
    Sprite m_detail; // Создаем банку спрайта
    bool CIMOVEONTHIS; // Я могу наступать на это?                                  i
    bool ITSINTERECTIVE;// Это интерактивная вещь?
    string name;
public:
    OMD_MAIN(Vector2f position, Texture& x) {
        m_detail.setPosition(position);
        m_detail.setTexture(x);

    }
    // Тут мы создаем объект используя имя и bool, также присваивая текстуру
    OMD_MAIN(string klichko, bool EbidoEbi, Texture KrasniyRog, bool gagababa)
    {

        name = klichko;
        CIMOVEONTHIS = EbidoEbi;
        m_detail.setTexture(KrasniyRog);
        ITSINTERECTIVE = gagababa;

    }

    // Если наша деталь является интерактивной в этом методе вызываются подметоды, если нет, то просто рисуем
    void Update(RenderWindow& babadjon)
    {
        babadjon.draw(m_detail);

        if (ITSINTERECTIVE)
        {
            // Тут к примеру покадравая анимация или при подходе игрока происходит обводка
            // Я это начну делать после появления такой вещи
        }
    }

};

struct Square
{
private:
    RectangleShape squre;
    bool Object;
public:
    Square(sf::Vector2f x)
    {
        squre.setSize(x);
        Object = 1;
    }
    bool GetObjectDopustim()
    {
        return Object;
    }
    void setGetObjectDopustim()
    {
        Object = 0;
    }
    void setOutlineColor(sf::Color x)
    {
        squre.setOutlineColor(x);
    }
    void setOutlineThickness(float x)
    {
        squre.setOutlineThickness(x);
    }
    void setPosition(sf::Vector2f x)
    {
        squre.setPosition(x);
    }
    void draw(RenderWindow& x)
    {
        x.draw(squre);
    }
    void setFillColor(sf::Color x)
    {
        squre.setFillColor(x);
    }
    FloatRect getGlobalBounds()
    {
        return squre.getGlobalBounds();
    }
    Vector2f getPosition()
    {
        return squre.getPosition();
    }
};

struct TextureGrid
{
    TEXTURES_MODULE& textureModule; // Ссылка на объект класса Texture_Module
    std::vector<sf::Sprite> sprites;

    TextureGrid(TEXTURES_MODULE& tm) : textureModule(tm)
    {
        // Создание спрайтов для каждой текстуры в Texture_Module
        for (const auto& texture : textureModule.GetAllOMDTextures())
        {
            sf::Sprite sprite(texture);
            sprites.push_back(sprite);
        }

        // Расположение спрайтов в сетке
        const int gridSizeX = 5; // Количество столбцов
        const int gridSizeY = 3; // Количество строк
        const float spriteSize = 100.f; // Размер спрайта

        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int x = 0; x < gridSizeX; ++x)
            {
                int index = x + y * gridSizeX; // Индекс спрайта в векторе sprites
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

// Да это круто, вопросы?
struct TrailSegment {
    sf::Vector2f position;  // Позиция сегмента следа
    sf::Color color;       // Цвет сегмента следа
    float transparency;    // Прозрачность сегмента следа
    float size;            // Размер сегмента следа
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
        // Получаем позицию и размеры стены
        Vector2f position = getPosition();
        Vector2f size = getSize();

        // Вычисляем центр стены
        Vector2f center = position + size / 2.f;

        // Вычисляем точку на стене, от которой будет идти нормаль
        // В данном примере выбираем середину левого края стены
        Vector2f pointOnWall = Vector2f(position.x, center.y);

        // Вычисляем вектор от точки на стене к центру стены
        Vector2f wallToCenter = center - pointOnWall;

        // Нормализуем вектор, чтобы получить единичную нормаль
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

            if (playerPosition.y < objectBounds.top) {
                Vladimir.CanIMoveDAUN = false;

            }

            if (playerPosition.y > objectBounds.top + objectBounds.height) {
                Vladimir.CanIMoveUP = false;

            }
        }
    }
    /*void CheckPaterochka(Bull& Vladimir) // Для проверки столкновения с Пулей
    {
        if (Vladimir.getGlobalBounds().intersects(getGlobalBounds())) {

            // если пуля попадет то это

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

    void update(RenderWindow& window) {

        window.draw(m_body);
    }
    void update(RenderWindow& window, Player& Vladimir) {

        window.draw(m_body);
        if (GODVIEW)DrawGodLines(Vladimir, getGlobalBounds(), window);
    }
    FloatRect getGlobalBounds() const {
        return m_body.getGlobalBounds();
    }

    //Wall() {} // Конструктор лего фури 
    Wall(Vector2f position, Texture& texture) {
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
    int StepenBrankera; // 0 - Изничтожен 1 - Стекло 2 - Древо 3 - рикошетит пулю 4 - Обсидиан  (1 и 2 не держит пули) 2 - имеет сопротивление пулям
};

class Door : public Wall { // Из за запарой с коллизией двери будут закрыты, главный персонаж может их сломать оружием либо выбить. У каждого объекта класса World будет система "Степен Бранкера" для определения прочности объекта.
public:

    Door(Vector2f position, Texture& texture) : Wall(position, texture) {

        StepenBrankera = 2;
        hp = 100;
    }
};

class World {
public:

    bool CREATIVE_MODE = 1;

    // Тут мы кучерявим оружие
    vector<Revolver_basic> m_Revolver_basic;
    vector<MiniCunn> m_MiniGun;
    // Тут мы кучерявим объекты мира
    vector<Wall> m_walls;
    vector<Door> m_doora;
    vector<Enemy> m_enemys;
    vector<OMD_MAIN> m_other;

    vector<FloatRect> m_objects;

    TEXTURES_MODULE HAMLET;

    CircleShape Cursor;

    CameraRoll Kashtan;

    Player Gavrusha;

private:

    vector<TrailSegment> trail;
    sf::VertexArray trailVertices;  // Массив вершин для отрисовки следа
    Color RandCOlOR;

    const int worldWidth = 1000;   // Ширина мира
    const int worldHeight = 1000;   // Высота мира
    const int squareSize = 32;     // Размер квадрата 32 - это 1 метр

    // Вычисляем количество квадратов по горизонтали и вертикали
    const int numSquaresX = worldWidth / squareSize;
    const int numSquaresY = worldHeight / squareSize;

    // Создаем двумерный вектор для хранения квадратов
    std::vector<Square> squares;

    bool isMoving = false;  // Флаг перемещения
    bool isKeyPressed[10] = { false };
    bool isZoomHandled;
    bool Can_Player_Spawn = 1;

    float MoveKeybordX;
    float MoveKeybordY;

    float speed;

    int ColorRape = 2;
    int TextureIndex[2];
    /// /////////////////////////////////////

    void WeaponCONTROL();

    void UpdateParticles(float dt);

    void UpdateEnemys(float& deltaTime, RenderWindow& window, Player& player);

    void UpdateEnemys(float& deltaTime, RenderWindow& window);

    void UpdateEnemys(float& deltaTime, RenderWindow& window, Player& player, bool x);

    /// /////////////////////////////////////

    void CreateOBJ(Square& sprite);

    void ControlWCR(RenderWindow& window, float dt);

    void Movement(float deltaTime);

    void updateTrail(sf::Vector2f position);

public:

    void addWall(Vector2f position, Texture& texture)
    {
        m_walls.emplace_back(position, texture);
    }

    void add_Revolver_basic(Texture& texture, bool isTaked, Vector2f position) // Создаем оружие 
    {
        m_Revolver_basic.emplace_back(texture, isTaked, position);
    }

    void add_MiniGun(Texture& texture, bool isTaked, Vector2f position) // Создаем оружие 
    {
        m_MiniGun.emplace_back(texture, isTaked, position);
    }

    void add_Enemy(Vector2f position, float size, float speed, Color color, float rotate, Texture& texture, float weapCD,int passiveMod, int hp_)
    {
        m_enemys.emplace_back(position, size, speed, color, rotate, texture, weapCD, passiveMod, hp_);
    }

    void add_player(Vector2f position, float size, float speed, Color color, int hp)
    {
        if (Can_Player_Spawn) {
            Gavrusha = Player(position, size, speed, color, hp);
            Can_Player_Spawn = 0;
        }
    }

    void addOMD(Vector2f position, Texture& texture)
    {
        m_other.emplace_back(position, texture);
    }

    void update(RenderWindow& window, float dt) { // Рисуем, обновляем коллизию
        if (!CREATIVE_MODE) {
            for (auto& wall : m_walls) {
                wall.update(window, Gavrusha);
                wall.CheckPaterochka(Gavrusha);
            }

            Gavrusha.update(dt, window, Gavrusha);

            for (auto& door : m_doora) {
                door.update(window, Gavrusha);
            }
            for (auto& makarov : m_Revolver_basic) {
                makarov.update(dt, Gavrusha, window, m_objects, m_enemys);
            }
            for (auto& makarov : m_MiniGun) {
                makarov.update(dt, Gavrusha, window, m_objects, m_enemys);
            }

            WeaponCONTROL();
            UpdateParticles(dt);
            UpdateEnemys(dt, window, Gavrusha);
        }
        else {
            // Отрисовка мира
            for (auto& squar : squares)
            {
                squar.draw(window);
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
            for (auto& wall : m_walls) {
                wall.update(window, Gavrusha);
                wall.CheckPaterochka(Gavrusha);
            }
            for (auto& door : m_doora) {
                door.update(window, Gavrusha);
            }
            Movement(dt);

            Gavrusha.update(dt, window, Gavrusha, 0);

            Kashtan.followPlayer(Cursor.getPosition(), 0.01);
            Kashtan.update(window);
            updateTrail(Cursor.getPosition());
            ControlWCR(window, dt);
            UpdateEnemys(dt, window, Gavrusha, 1);

            // Отрисовываем след с использованием массива вершин
            window.draw(trailVertices);
            window.draw(Cursor);
        }
    }


    void SetGlobalObjectBounds()
    {
        m_objects.clear();
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

            // Инициализация мира
            Cursor.setRadius(5);
            speed = 300;
            Cursor.setOrigin(5 / 2, 5 / 2);

            // Вычисляем количество квадратов по горизонтали и вертикали
            const int numSquaresX = worldWidth / squareSize;
            const int numSquaresY = worldHeight / squareSize;

            // Вычисляем общее количество квадратов
            const int totalSquares = numSquaresX * numSquaresY;

            // Размеры каждого квадрата
            const float squareWidth = static_cast<float>(worldWidth) / numSquaresX;
            const float squareHeight = static_cast<float>(worldHeight) / numSquaresY;




            // Заполняем вектор квадратами
            for (int i = 0; i < totalSquares; ++i)
            {
                Square square(sf::Vector2f(squareWidth, squareHeight));
                square.setOutlineThickness(1.0f);  // Толщина границы
                square.setOutlineColor(sf::Color::Red);  // Цвет границы
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








//////////////////////////////////УПРАВЛЕНИЕ ОРУЖИЕМ/////////////////////////////////

void World::WeaponCONTROL()
{
    for (auto& revolver : m_Revolver_basic) {
        for (auto& door : m_doora) {
            //revolver.SetBulletDamage(door.getGlobalBounds(), door.WallCenter(door.getGlobalBounds()));
        }
        for (auto& wall : m_walls) {
            //revolver.SetBulletDamage(wall.getGlobalBounds(), wall.WallCenter(wall.getGlobalBounds()));
        }
    }

    for (auto& revolver : m_MiniGun) {
        for (auto& door : m_doora) {
            //revolver.SetBulletDamage(door.getGlobalBounds(), door.WallCenter(door.getGlobalBounds()));
        }
        for (auto& wall : m_walls) {
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

    for (auto& revolver : m_MiniGun) {
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

void World::UpdateEnemys(float& deltaTime, RenderWindow& window, Player& player, bool x)
{
    for (auto& enemy : m_enemys) {
        enemy.Update(deltaTime, window, m_objects);
    }
}

void World::UpdateEnemys(float& deltaTime, RenderWindow& window)
{
    for (auto& enemy : m_enemys) {
        enemy.Update(deltaTime, window, m_objects);
    }
}
/////////////////////////////////////////////////////////////////////////////////////
// Тут Обработка редактора
// .......................



void World::CreateOBJ(Square& sprite)
{
    // Проверяем состояние клавиши
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
       
        if (sprite.GetObjectDopustim() == 1)
        {
            addWall(sprite.getPosition(), HAMLET.GetWallTexture(1));
            sprite.setGetObjectDopustim();
            cout << "Ok" << endl;
        }
        else {
            cout << "idnaui" << endl;
        }
            isKeyPressed[1] = true;
        
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
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        if (!isKeyPressed[3])
        {
            cout << "Ok" << endl;
            add_player(sprite.getPosition(), 50.f, 300, Color::Red, 5);
            isKeyPressed[3] = true;
        }
    }
    else
    {
        isKeyPressed[3] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        if (!isKeyPressed[4])
        {
            cout << "Ok" << endl;
            add_Enemy(sprite.getPosition(), 50.f, 230, Color::Yellow, 0, HAMLET.GetWeaponTexture(1), 0.3f,0,100);
            isKeyPressed[4] = true;
        }
    }
    else
    {
        isKeyPressed[4] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        if (!isKeyPressed[5])
        {
            cout << "OBJECT FIRED" << endl;
            SetGlobalObjectBounds();
            isKeyPressed[5] = true;
        }
    }
    else
    {
        isKeyPressed[5] = false;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
    {
        if (!isKeyPressed[6])
        {
            if (CREATIVE_MODE)
            {
                CREATIVE_MODE = 0;
            }
            else {
                CREATIVE_MODE = 1;
            }
            cout << "DEBUG:" <<CREATIVE_MODE<< endl;
            isKeyPressed[6] = true;
        }
    }
    else
    {
        isKeyPressed[6] = false;
    }
}

void World::ControlWCR(RenderWindow& window, float dt)
{
    // Проверяем состояние клавиши
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


    // Проверяем состояние клавиш "+" и "-"
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
    {
        // Увеличиваем зум
        Kashtan.m_view.zoom(1.001f);  // Измените 1.1 на желаемый коэффициент зума
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
    {
        // Уменьшаем зум
        Kashtan.m_view.zoom(0.999f);  // Измените 0.9 на желаемый коэффициент зума
    }
}

void World::Movement(float deltaTime) {

    isMoving = false;
    // Передвижение клавиатурой
    if (Keyboard::isKeyPressed(Keyboard::D)) { MoveKeybordX = 1 * deltaTime * speed; isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::A)) { MoveKeybordX = -1 * deltaTime * speed; isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::W)) { MoveKeybordY = 1 * deltaTime * speed; isMoving = true; }
    if (Keyboard::isKeyPressed(Keyboard::S)) { MoveKeybordY = -1 * deltaTime * speed; isMoving = true; }
    Cursor.move(Vector2f(MoveKeybordX, -MoveKeybordY));
    if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) || (Keyboard::isKeyPressed(Keyboard::D)) || (Keyboard::isKeyPressed(Keyboard::A))) { MoveKeybordX = 0 * deltaTime * speed; }
    if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S) || (Keyboard::isKeyPressed(Keyboard::W)) || (Keyboard::isKeyPressed(Keyboard::S))) { MoveKeybordY = 0 * deltaTime * speed; }
}

void World::updateTrail(sf::Vector2f position)
{

    // Удаляем последний сегмент следа, если его количество превышает желаемую длину
    const int maxTrailLength = 500;  // Задайте желаемую длину следа
    if (trail.size() > maxTrailLength)
    {
        trail.pop_back();
    }

    // Добавляем новый сегмент следа в начало контейнера
    TrailSegment segment;
    segment.position = position;
    segment.transparency = 255;      // Задайте начальную прозрачность следа
    trail.insert(trail.begin(), segment);

    // Обновляем прозрачность и цвет каждого сегмента следа
    for (auto& segment : trail)
    {
        segment.transparency -= 1;  // Уменьшаем прозрачность сегмента следа

        // Устанавливаем новую прозрачность сегмента следа
        segment.color.a = static_cast<sf::Uint8>(segment.transparency);

    }

    // Обновляем массив вершин для отрисовки следа

    trailVertices.clear();

    // Добавляем вершины в массив для каждый сегмент следа
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