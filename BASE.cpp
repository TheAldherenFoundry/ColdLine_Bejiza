//#include "LEVELS.h"
//
//using namespace sf;
//using namespace std;
//
//int main()
//{
//    TAF_CREATOR* Hello = new TAF_CREATOR();
//    Level* One = new Level();
//
//    bool DEBUG_MODE = 0;
//
//    if(DEBUG_MODE){
//    while (Hello->window.isOpen())
//    {
//        Time dt = Hello->deltaClock.restart();                          // Кол-во времени между кадрами
//        Hello->deltaTime = dt.asSeconds();                              // Да!
//
//        Event event;
//        while (Hello->window.pollEvent(event))
//        {
//            if (event.type == Event::Closed)
//            {
//                Hello->window.close();
//            }
//        }
//        Hello->window.clear(Color::Black);                                                 // Очищаем экран
//        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        Hello->Update();                                                                    // выводим экран на монито
//        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//        Hello->window.display();
//    }
//
//    Hello->Extominate_world();
//    return 0;
//    }
//    if (!DEBUG_MODE)
//    {
//        while (One->window.isOpen())
//        {
//            Time dt = One->deltaClock.restart();                          // Кол-во времени между кадрами
//            One->deltaTime = dt.asSeconds();                              // Да!
//
//            Event event;
//            while (One->window.pollEvent(event))
//            {
//                if (event.type == Event::Closed)
//                {
//                    One->window.close();
//                }
//            }
//            One->window.clear(Color::Black);                                                 // Очищаем экран
//            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//            One->Update();                                                                    // выводим экран на монито
//            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//            One->window.display();
//        }
//
//        One->Extominate_world();
//        return 0;
//    }
//
//}


#include "LEVELS.h"


using namespace sf;
using namespace std;

int main()
{
    // Создаем окно размером 800x600
    RenderWindow window(VideoMode(1920, 1080), "Hotline Miami");

    window.setMouseCursorVisible(false);
    window.setMouseCursorGrabbed(true);

    bool DEBUG_INFO = 0;

    RectangleShape a(Vector2f(1000, 1000));
    a.setFillColor(Color::Cyan);

    Clock deltaClock;
    float deltaTime = 0.f;

    // Создаем игрока
    Player player(Vector2f(100.f, 100.f), 50.f, 300, Color::Red); // создаем персонажа

    World* world = new World(0);

    TEXTURES_MODULE hi;

    for(int a = 0;a <= 320;a = a + 32)world->addWall(Vector2f(0, a), hi.GetWallTexture(1));
    for (int a = 32; a <= 320; a = a + 32)world->addWall(Vector2f(a, 0), hi.GetWallTexture(1));
    world->addOMD(Vector2f(100, 0), hi.GetWallTexture(1));
    //world->add_Enemy(Vector2f(400, 500), 50, 50, Color::Red, 0);
    
    
    world->SetGlobalObjectBounds();

    world->add_Revolver_basic(hi.GetWeaponTexture(1), true, Vector2f(0,0));
    while (window.isOpen())
    {
        Time dt = deltaClock.restart();                          // Кол-во времени между кадрами
        deltaTime = dt.asSeconds();                              // Да!

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear(Color::Black);                                                       // Очищаем экран
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        if (!DEBUG_INFO) {
            player.update(deltaTime, window,player);                                                         // да
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            world->update(window, player, deltaTime);                                         // Отрисовка объектов
            player.draw(window);                                                              // отображаем персонажа на экране
        }
        else {
            window.draw(a);
        }
        window.display();                                                                 // выводим экран на монито
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    delete world;
    return 0;
}
