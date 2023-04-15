#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
using namespace sf;
using namespace std;
#include <cmath>




RenderWindow window(VideoMode(1200, 800), "Dino Fight");

void play();
void homescreen();

int main()
{
    window.setFramerateLimit(144.0); // to not burn out your graphics card
    Image I;
    I.loadFromFile("assets/dino.png");

    window.setIcon(I.getSize().x, I.getSize().y, I.getPixelsPtr());
    


    homescreen();
    return 0;
}



void homescreen() {

    Text playy;
    Font font;
    Texture background;
    background.loadFromFile("assets/background.png");
    Sprite back;
    back.setTexture(background);
    back.scale(.8, .7);
    double backwidth = background.getSize().x * .8;
    /////////////////////////// to play
    font.loadFromFile("assets/Arial.ttf");
    playy.setFont(font);
    playy.setStyle(Text::Bold);
    playy.setCharacterSize(50);
    playy.setFillColor(Color::Black);
    playy.setString("Press F to Play");
    playy.setPosition(520, 350);
    bool mute = 0;

    //loading backgorund sound
    SoundBuffer backs;
    backs.loadFromFile("assets/background.wav");
    Sound backsound;
    backsound.setBuffer(backs);
    backsound.play();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (Keyboard::isKeyPressed(Keyboard::F)) {
            backsound.stop();
            play();
        }

        
        if (Keyboard::isKeyPressed(Keyboard::M) && !mute) {
            backsound.setVolume(0);
            mute = 1;
        } else if (Keyboard::isKeyPressed(Keyboard::K) && mute) {
            backsound.setVolume(100);
            mute = 0;
        }
        window.draw(back);
        window.draw(playy);
        window.display();

    }

}


void play() {
    Texture texture;
    texture.loadFromFile("assets/dino.png");
    Sprite dino;
    dino.scale(.1, .1);
    dino.setPosition(50, 640);
    dino.setTexture(texture);



    ////////////////////////////////////////////
    Texture bull;
    bull.loadFromFile("assets/bullet.png");
    Sprite bullet;
    bullet.scale(.1, .15);
    bullet.setTexture(bull);




    ////////////////////////////////////////////

    Texture texturedown;
    texturedown.loadFromFile("assets/dinodown.png");

    Texture background;
    background.loadFromFile("assets/background.png");
    Sprite back;
    back.setTexture(background);
    back.scale(.8, .7);
    double backwidth = background.getSize().x * .8;

    int tiles = ceil(1200 / (backwidth)) + 1;
    /////////////////jumping

    Vector2f velocity(0.f, 0.f);
    bool canjump;
    float jumpheight = 200;
    //bool jumpno = 0;

    int m = 0;


    //////////////cactus
    Texture cact;
    cact.loadFromFile("assets/cactus.png");
    Sprite cactus;
    Sprite cactus2;
    Sprite cactus3;
    cactus2.setTexture(cact);
    cactus3.setTexture(cact);
    cactus.setTexture(cact);
    cactus.scale(.3, .3);
    cactus2.scale(.3, .3);
    cactus3.scale(.3, .3);





    //////////////enemy
    Texture enem;
    enem.loadFromFile("assets/bird.png");
    Sprite enemy;
    enemy.setTexture(enem);
    enemy.scale(-0.2, 0.15);



    /////////////////////////////////

    bool first = true;
    bool hh = 1;

    double dinowidth = texture.getSize().x * .1;
    double dinoheight = texture.getSize().y * .1;
    double cactwidth = cact.getSize().x * .2;
    double cactheight = cact.getSize().y * .2;
    double enemywidth = enem.getSize().x * .2;
    double enemheight = enem.getSize().y * .15;


    double marginx = (texture.getSize().x) * 0.1;
    double marginy = (texture.getSize().y) * 0.1;

    int scroll = 0;
    int scroll2 = 0;
    int scroll3 = 0;
    int scroll4 = 0;
    int scroll5 = 0;
    int scrollbullet = 0;

    int score = 0;



    Text scoree;
    Font font;




    /////////////////////////score display
    font.loadFromFile("assets/Arial.ttf");
    scoree.setFont(font);
    scoree.setStyle(Text::Bold);
    scoree.setCharacterSize(50);
    scoree.setFillColor(Color::White);
    scoree.setPosition(19, 4);



    ////////////////////////////////
    bool reset = false;
    bool onway = 0;
    bool canfire = true;
    bool firstbullet = 1;


    double bulletposition;

    //////////////////////////////////////////////////sound

    SoundBuffer up;
    up.loadFromFile("assets/upp.wav");

    Sound ups;
    ups.setBuffer(up);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }










        if (Keyboard::isKeyPressed(Keyboard::Space) && dino.getPosition().y > 635 && !Keyboard::isKeyPressed(Keyboard::Down)) {
            velocity.y = -sqrt(2.0f * 981.0f * jumpheight);
            m = 2;
            ups.play();
        }


        bool downpressed = true;


        window.clear();




        for (int i = 0; i < tiles; i++) {
            back.setPosition((i * 1280) + scroll, 0);
            window.draw(back);

        }






        cactus.setPosition(1200 + scroll2, 610);
        enemy.setPosition(1500 + scroll3, 600);
        window.draw(cactus);
        window.draw(enemy);
        /*
        if (score > 40 && (score - 40) % 20 == 0) {
           cactus2.setPosition(1300 + scroll4, 610);
           cout << cactus.getPosition().x << "  " << cactus2.getPosition().x << endl;
           window.draw(cactus2);
        }
        */

        //if (score > 40 && (score - 40) % 40 == 0) {
            //cactus3.setPosition(1400-(score*20) + scroll5, 610);
            //window.draw(cactus3);
        //}



        scroll4 -= 5;
        scroll3 -= 5;
        scroll2 -= 5;
        scroll -= 5;
        scroll5 -= 5;

        if (abs(scroll) > backwidth) {
            scroll = 0;
        }
        if (abs(scroll2) > 1200 + cactwidth) {
            scroll2 = 0;
            score += 5;
        }
        if (abs(scroll3) > 1800 + cactwidth) {
            scroll3 = 0;
            //   score += 10;
        } if (abs(scroll4) > 1300 + cactwidth) {
            scroll4 = 0;
            //   score += 10;
        }if (abs(scroll5) > 1400 + cactwidth) {
            scroll5 = 0;

        }

        window.draw(dino);
        scoree.setString(to_string(score));
        window.draw(scoree);
        

        if (score > 50) {
            //    window.draw(enemy);
        }

        








        if (Keyboard::isKeyPressed(Keyboard::Space) && dino.getPosition().y > 635 && !Keyboard::isKeyPressed(Keyboard::Down)) {
            velocity.y = -sqrt(2.0f * 981.0f * jumpheight);
            m = 2;
            ups.play();
        }
        if (Keyboard::isKeyPressed(Keyboard::T) && m == 2) {
            velocity.y = -sqrt(2.0f * 981.0f * jumpheight);
            m = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::Down) && downpressed && dino.getPosition().y > 630) {
            dino.setTexture(texturedown);
            dino.setPosition(47, 689);
            downpressed = 1;
            reset = 1;
        }
        if (reset && !Keyboard::isKeyPressed(Keyboard::Down)) {
            downpressed = 0;
            dino.setPosition(50, 640);
            dino.setTexture(texture);
            reset = 0;
        }
        window.draw(bullet);

        ////////////////////////////////////////////////////////////////////////////////// firing mechanism


        if (Keyboard::isKeyPressed(Keyboard::K) && canfire && !firstbullet) {
            bullet.setPosition(dino.getPosition().x + dinowidth, dino.getPosition().y);

        }

        if(bullet.getPosition().x<1200 && canfire){
            //bullet.setPosition(dino.getPosition().x + dinowidth, bullet.getPosition().y);
            canfire = 0;
            onway = 1;
            bulletposition = bullet.getPosition().y;
            
        }

        if (bullet.getPosition().x < 1200 && onway) {
            scrollbullet += 50;
            bullet.setPosition(bullet.getPosition().x + scrollbullet/10.0, bulletposition);   
        }

        if (bullet.getPosition().x > 1200) {
            
            scrollbullet = 0;
            canfire = 1;
            onway = 0;
            firstbullet = 0;
        }


        //////////////////////////////////////////////////////////////////////////////////////////////////////

        window.display();
        //static double GetDeltaTime();


        if (dino.getPosition().y < (640)) {
            velocity.y += 981.0f * (1.0 / 144.0);
        }
        if (dino.getPosition().y > (640) && !Keyboard::isKeyPressed(Keyboard::Down)) {
            dino.setPosition(50, 640);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Down) && !downpressed) {
            dino.setPosition(47, 689);
        }


        dino.move(0, velocity.y * (1.0 / 144.0));


        //(Mx>Px) or (Ox>Nx) or (My>Py) or (Oy>Ny) or (Mz>Pz) or (Oz>Nz).

        if (dino.getPosition().x < cactus.getPosition().x + cactwidth && dino.getPosition().x + dinowidth>cactus.getPosition().x + 45 && dino.getPosition().y < cactus.getPosition().y + cactheight && dino.getPosition().y + dinoheight>cactus.getPosition().y + 25) {
            cout << "cact" << endl;
        }
        if (dino.getPosition().x < enemy.getPosition().x + enemywidth && dino.getPosition().x + dinowidth>enemy.getPosition().x && dino.getPosition().y < enemy.getPosition().y + enemheight && dino.getPosition().y + dinoheight>enemy.getPosition().y) {
            cout << "bird" << endl;
        }
    }

}






//
//#include <iostream>
//#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//using namespace sf;
//using namespace std;
//RenderWindow window(VideoMode(1200, 800), "SFML Works!", Style::Close | Style::Titlebar);
//void BackkgrounndColors()
//{
//    Vector2f rec1pos = Vector2f(0, 0);
//    RectangleShape rec1(Vector2f(1200.f, 200.f));
//    rec1.setFillColor(Color::Cyan);
//    rec1.setPosition(rec1pos);
//    window.draw(rec1);
//}
//
//void BackgroundWords()
//{
//    Font font;
//    if (!font.loadFromFile("assets/Arial.ttf"))
//        throw("COULD NOT LOAD FONT");
//    Text text;
//    text.setFont(font);
//    text.setCharacterSize(50);
//    text.setFillColor(Color::Red);
//    text.setStyle(Text::Regular);
//    text.setString(" Dino Runner ");
//    text.setPosition(Vector2f(450, 300));
//    window.draw(text);
//}
//
//
//void Output()
//{
//    window.setFramerateLimit(60);
//    SoundBuffer soundBuffer;
//    Sound sound;
//    if (!soundBuffer.loadFromFile("assets/background.wav"))
//    {
//        throw("COULD NOT LOAD Audio");
//    }
//    sound.setBuffer(soundBuffer);
//    sound.play();
//    while (window.isOpen())
//    {
//        sf::Event event;
//        while (window.pollEvent(event))
//        {
//
//            if (event.type == sf::Event::Closed)
//                window.close();
//        }
//        window.clear();
//        BackkgrounndColors();
//        BackgroundWords();
//        window.display();
//
//    }
//}
//
///// main function 
//int main()
//{
//
//    Output();
//}

