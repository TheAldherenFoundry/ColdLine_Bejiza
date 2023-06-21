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

    window.setFramerateLimit(120);

    bool DEBUG_INFO = 1;
    float timeFPS = 0;
    int fps = 0;

    RectangleShape a(Vector2f(1000, 1000));

    Clock deltaClock;
    float deltaTime = 0.f;

    World* world = new World(DEBUG_INFO);

    TEXTURES_MODULE hi;
    
    if (!DEBUG_INFO) {
        world->addOMD(Vector2f(100, 0), hi.GetWallTexture(1));
        world->add_Enemy(Vector2f(300, 300), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(300, 400), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(300, 500), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(300, 600), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(300, 700), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(400, 300), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(400, 400), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(400, 500), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(400, 600), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(400, 700), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(500, 300), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(500, 400), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(500, 500), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(500, 600), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(500, 700), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(600, 300), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(600, 400), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(600, 500), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(600, 600), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(600, 700), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(700, 300), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(700, 400), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(700, 500), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(700, 600), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_Enemy(Vector2f(700, 700), 50, 50, Color::Blue, 0, hi.GetWeaponTexture(1), 0.5f, 1, 3);
        world->add_player(Vector2f(100.f, 100.f), 50.f, 300, Color::Red, 5);
        
        world->addWall(Vector2f(0, 0), hi.GetWallTexture(1));
        world->addWall(Vector2f(200, 200), hi.GetWallTexture(1));

        world->SetGlobalObjectBounds();

        world->add_Revolver_basic(hi.GetWeaponTexture(1), false, Vector2f(400, 400));
        world->add_MiniGun(hi.GetWeaponTexture(2), true, Vector2f(200, 200));


    }
    while (window.isOpen())
    {
        Time dt = deltaClock.restart();                          // Кол-во времени между кадрами
        deltaTime = dt.asSeconds();                              // Да!

        timeFPS += deltaTime;
        fps++;
        if (timeFPS >= 1) {
            cout << "FPS: " << fps << endl;
            timeFPS = 0;
            fps = 0;
        }

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
        
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        world->update(window, deltaTime);                                                  // Отрисовка объектов
        
        window.display();                                                                 // выводим экран на монито
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    delete world;
    return 0;
}
