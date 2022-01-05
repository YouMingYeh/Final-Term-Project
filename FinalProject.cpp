#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <unistd.h>

using namespace std;

class Animation
{
private:
    sf::Clock clock;
    
    int left;
    int imagesCnt;
    int currentCnt;

public:
sf::IntRect rectSourceSprite;
    sf::Sprite sprite;
    Animation(sf::Sprite INPUTsprite, sf::IntRect inputRectSourceSprite, int Cnt);
    ~Animation();
    void Moving(float deltatime);
};

Animation::Animation(sf::Sprite inputSprite, sf::IntRect inputRectSourceSprite, int Cnt)
{
    currentCnt = 1;
    this->sprite = inputSprite;
    this->rectSourceSprite = inputRectSourceSprite;
    this->imagesCnt = Cnt;
    this->left = inputRectSourceSprite.left;
    ;
}

Animation::~Animation()
{
    ;
}

void Animation::Moving(float deltatime)
{
    if (this->clock.getElapsedTime().asSeconds() >= deltatime)
    {
        if (currentCnt != imagesCnt)
        {
            this->rectSourceSprite.left += this->rectSourceSprite.width;
            this->currentCnt++;
        }
        else
        {
            this->rectSourceSprite.left = left;
            this->currentCnt = 1;
        }

        this->sprite.setTextureRect(rectSourceSprite);
        this->clock.restart();
    }
}

struct info
{
    bool jumping;
    bool moving;
    bool facingRight;
    float xVelocity;
    float yVelocity;

    sf::Sprite weapen;
    bool weapenExist;
    bool weapenFacingRight;

    bool attacked;

    int hp;

    sf::RectangleShape hpBar;

    sf::Sprite heart;
};

bool isTouched(sf::Sprite A, sf::Sprite B);

const int hieght = 2048;
const int width = 2048;

int main()
{
    chdir("finalTermProject");
    sf::Texture bg;
    bg.loadFromFile("images/background3.png");


    sf::Sprite background;
    background.setTexture(bg);
    background.setScale(0.85, 0.85);
    background.setPosition(0, -28);

    sf::Texture bg2;
    bg2.loadFromFile("images/background4.png");


    sf::Sprite background2;
    background2.setTexture(bg2);
    background2.setScale(1.5, 1.5);
    background2.setOrigin(700,350);
    background2.setPosition(width/2, 500);

    

    //---------------build window-------------------//

    sf::RenderWindow window(sf::VideoMode(width, hieght), "SpiderMan - No A+ Project");
    window.setFramerateLimit(60);

    //---------------text------------------//
    sf::Font font1;
    font1.loadFromFile("Fonts/Fonttt.ttf");

    sf::Font font2;
    font2.loadFromFile("Fonts/NotoSansJP-Bold.otf");

    sf::Text Guide;
    Guide.setString("O - turn down music \nP - turn up music \nL - turn off music \nK - turn on music \n \nPlayer1: \nW - jump\nA - move to left \nD - move to right \nE - fire!!!\n \nPlayer2: \nUp - jump\nLeft - move to left \nRight - move to right \nRshift - fire!!!");
    Guide.setFont(font1);
    Guide.setCharacterSize(50);
    Guide.setFillColor(sf::Color::White);
    Guide.setOutlineColor(sf::Color::Black);
    Guide.setOutlineThickness(8);
    Guide.setPosition(25, 25);

    sf::Text gameStartUI;
    gameStartUI.setString("This is a 2 players battle game\n shoot your stuffs to damage your enimies\n\nPRESS SPACE TO GET START!!!");
    gameStartUI.setFont(font1);
    gameStartUI.setCharacterSize(80);
    gameStartUI.setFillColor(sf::Color::White);
    gameStartUI.setPosition(500, 1100);
    gameStartUI.setOutlineColor(sf::Color::Black);
    gameStartUI.setOutlineThickness(8);

    sf::Text start;
    start.setString("3");
    start.setFont(font1);
    start.setOrigin(50, 50);
    start.setCharacterSize(200);
    start.setFillColor(sf::Color::White);
    start.setPosition(width / 2, hieght / 2);

    sf::Text choosing;
    choosing.setString("Press 1       2       3\n       4       5       6\nto select your weapon");
    choosing.setFont(font1);
    choosing.setOrigin(50, 50);
    choosing.setCharacterSize(50);
    choosing.setFillColor(sf::Color::White);
    choosing.setPosition(100, 100);

    sf::Text P1;
    P1.setString("Player1");
    P1.setFont(font1);
    P1.setOrigin(50, 50);
    P1.setCharacterSize(100);
    P1.setFillColor(sf::Color::White);
    P1.setPosition(1000, 100);

    sf::Text P2;
    P2.setString("Player2");
    P2.setFont(font1);
    P2.setOrigin(50, 50);
    P2.setCharacterSize(100);
    P2.setFillColor(sf::Color::White);
    P2.setPosition(1000, 100);

    sf::Text restart;
    restart.setString("Press Space to restart ! ");
    restart.setFont(font1);
    restart.setOrigin(650, 50);
    restart.setCharacterSize(200);
    restart.setFillColor(sf::Color::White);
    restart.setOutlineColor(sf::Color::Black);
    restart.setOutlineThickness(20);
    restart.setPosition(width/2, hieght/2-500);

    //---------------Build player------------------//

    sf::Texture character1;
    character1.loadFromFile("Images/p1Right.png");

    sf::Sprite Player1;
    Player1.setTexture(character1);
    Player1.setPosition(500, 1150);
    Player1.setOrigin(100,100);

    sf::Texture character2;
    character2.loadFromFile("Images/p1Left.png");

    sf::Sprite Player2;
    Player2.setTexture(character2);
    Player2.setPosition(1500, 1150);
    Player2.setOrigin(100,100);

    sf::Texture deadP1;
    deadP1.loadFromFile("Images/Dead.png");

    sf::Texture deadP2;
    deadP2.loadFromFile("Images/Dead.png");

    Player1.setScale(1.5,1.5);
    Player2.setScale(1.5,1.5);

    

    sf::Texture p1JumpingRight1;
    p1JumpingRight1.loadFromFile("Images/p1JumpingRight1.png");

    sf::Texture p1JumpingRight2;
    p1JumpingRight2.loadFromFile("Images/p1JumpingRight2.png");

    sf::Texture p1JumpingLeft1;
    p1JumpingLeft1.loadFromFile("Images/p1JumpingLeft1.png");

    sf::Texture p1JumpingLeft2;
    p1JumpingLeft2.loadFromFile("Images/p1JumpingLeft2.png");



    sf::Texture p2JumpingRight1;
    p2JumpingRight1.loadFromFile("Images/p2JumpingRight1.png");

    sf::Texture p2JumpingRight2;
    p2JumpingRight2.loadFromFile("Images/p2JumpingRight2.png");

    sf::Texture p2JumpingLeft1;
    p2JumpingLeft1.loadFromFile("Images/p2JumpingLeft1.png");

    sf::Texture p2JumpingLeft2;
    p2JumpingLeft2.loadFromFile("Images/p2JumpingLeft2.png");

    //------------------- data---------------//

    float moveSpeed = 20;
    int jumpSpeed = 50;
    float attackedSpeed = 10;
    bool ifKeepGoing = true;

    int Cnt = 10;

    sf::Texture eggplant;
    eggplant.loadFromFile("Images/tw.png");

    sf::Texture p1faceRight;
    p1faceRight.loadFromFile("Images/p1Right.png");

    sf::Texture p1faceLeft;
    p1faceLeft.loadFromFile("Images/p1Left.png");

    sf::Texture p2faceRight;
    p2faceRight.loadFromFile("Images/p2Right.png");

    sf::Texture p2faceLeft;
    p2faceLeft.loadFromFile("Images/p2Left.png");

    sf::Music music;
    music.openFromFile("Sounds/soundtrack.wav");
    music.setVolume(50);
    music.play();
    music.setLoop(true);
    //-------------------sound effect--------------//
    sf::SoundBuffer punchBuffer;
    punchBuffer.loadFromFile("Sounds/punch.wav");

    sf::Sound punch;
    punch.setBuffer(punchBuffer);
    punch.setVolume(20);

    sf::SoundBuffer deathBuffer;
    deathBuffer.loadFromFile("Sounds/deathsound.wav");

    sf::Sound deathSound;
    deathSound.setBuffer(deathBuffer);
    deathSound.setVolume(40);


    sf::SoundBuffer buttonBuffer;
    buttonBuffer.loadFromFile("Sounds/button.wav");

    sf::Sound button;
    button.setBuffer(buttonBuffer);
    button.setVolume(40);

    //-------------------heartTexture---------------//
    sf::Texture heartTexture;
    heartTexture.loadFromFile("Images/heart.png");

    //-------------------player1 info---------------//
    info p1;
    p1.jumping = false;
    p1.moving = false;
    p1.facingRight = false;
    p1.xVelocity = 0;
    p1.yVelocity = 0;

    p1.weapen.setTexture(eggplant);
    p1.weapen.setScale(1, 1);
    p1.weapen.setOrigin(100,100);


    p1.weapenExist = false;
    p1.weapenFacingRight = false;

    p1.attacked = false;

    p1.hp = 500;

    p1.hpBar.setSize(sf::Vector2f(p1.hp, 50));
    p1.hpBar.setPosition(50, 1400);
    p1.hpBar.setFillColor(sf::Color::Red);
    p1.hpBar.setOutlineColor(sf::Color::Black);
    p1.hpBar.setOutlineThickness(8);

    p1.heart.setTexture(heartTexture);
    p1.heart.setPosition(0, 1370);
    p1.heart.setScale(0.2, 0.2);

    //-------------------player2 info---------------//
    info p2;
    p2.jumping = false;
    p2.moving = false;
    p2.facingRight = false;
    p2.xVelocity = 0;
    p2.yVelocity = 0;

    p2.weapen.setTexture(eggplant);
    p2.weapen.setScale(1, 1);
    p2.weapen.setOrigin(100,100);

    p2.weapenExist = false;
    p2.weapenFacingRight = false;

    p2.attacked = false;

    p2.hp = 500;

    p2.hpBar.setSize(sf::Vector2f(500, 50));
    p2.hpBar.setPosition(2000 - p2.hp, 1400);
    p2.hpBar.setFillColor(sf::Color::Red);
    p2.hpBar.setOutlineColor(sf::Color::Black);
    p2.hpBar.setOutlineThickness(8);

    p2.heart.setTexture(heartTexture);
    p2.heart.setPosition(1450, 1370);
    p2.heart.setScale(0.2, 0.2);

    //-------------------fire ball------------------//

    float weapenDmg = 30;

    //-------------------game-----------------------//

    bool gameOn = false;

    sf::Clock t;
    sf::Clock t2;
    sf::Clock p1CD;
    sf::Clock p2CD;

    bool ready = false;

    //------------------animation-------------------//

    sf::Texture p1MovingRightTexture;
    p1MovingRightTexture.loadFromFile("Images/p1MovingRight.png");

    sf::IntRect p1MovingRect(0,0,220,188);

    sf::Sprite p1MovingRight;
    p1MovingRight.setTextureRect(p1MovingRect);

    sf::Texture p1MovingLeftTexture;
    p1MovingLeftTexture.loadFromFile("Images/p1MovingLeft.png");

    sf::Sprite p1MovingLeft;
    p1MovingLeft.setTextureRect(p1MovingRect);

    Animation p1MovingRightAni(p1MovingRight,p1MovingRect,4);
    Animation p1MovingLeftAni(p1MovingLeft,p1MovingRect,4);

    sf::Texture p2MovingRightTexture;
    p2MovingRightTexture.loadFromFile("Images/p2MovingRight.png");

    sf::IntRect p2MovingRect(0,0,220,188);

    sf::Sprite p2MovingRight;
    p2MovingRight.setTextureRect(p2MovingRect);

    sf::Texture p2MovingLeftTexture;
    p2MovingLeftTexture.loadFromFile("Images/p2MovingLeft.png");

    sf::Sprite p2MovingLeft;
    p2MovingLeft.setTextureRect(p2MovingRect);

    Animation p2MovingRightAni(p2MovingRight,p2MovingRect,4);
    Animation p2MovingLeftAni(p2MovingLeft,p2MovingRect,4);
    
    sf::IntRect defaultRect(0,0,220,188);

    //------------------------------------------------//

    sf::Clock t4;
    bool p1Choosed = false;
    bool p2Choosed = false;

    sf::Texture *weaponTexture = new sf::Texture [6];
    sf::Sprite *Weapon = new sf::Sprite [6];

    weaponTexture[0].loadFromFile("Images/dogge.png");
    Weapon[0].setTexture(weaponTexture[0]);
    Weapon[0].setPosition(500,500);

    weaponTexture[1].loadFromFile("Images/pengiun.png");
    Weapon[1].setTexture(weaponTexture[1]);
    Weapon[1].setPosition(1000,500);

    weaponTexture[2].loadFromFile("Images/pokeball.png");
    Weapon[2].setTexture(weaponTexture[2]);
    Weapon[2].setPosition(1500,500);

    weaponTexture[3].loadFromFile("Images/grenade1.png");
    Weapon[3].setTexture(weaponTexture[3]);
    Weapon[3].setPosition(500,1000);


    weaponTexture[4].loadFromFile("Images/grenade2.png");
    Weapon[4].setTexture(weaponTexture[4]);
    Weapon[4].setPosition(1000,1000);

    weaponTexture[5].loadFromFile("Images/angry.png");
    Weapon[5].setTexture(weaponTexture[5]);
    Weapon[5].setPosition(1500,1000);
    

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        while (gameOn == false)
        {
            window.clear();
            window.draw(background2);
            window.draw(gameStartUI);
            
            window.display();

            if (t.getElapsedTime().asSeconds() >= 3.0f)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
                {
                    gameOn = true;
                }
            }
        }

        

        
        while(p1Choosed == false){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            p1.weapen.setTexture(weaponTexture[0]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[0].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            p1.weapen.setTexture(weaponTexture[1]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[1].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            p1.weapen.setTexture(weaponTexture[2]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[2].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
            p1.weapen.setTexture(weaponTexture[3]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[3].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            p1.weapen.setTexture(weaponTexture[4]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[4].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
            p1.weapen.setTexture(weaponTexture[5]);
            p1Choosed = true;
            t4.restart();
            button.play();
            Weapon[5].setScale(2,2);
        }
    
        window.clear();
        for(int i = 0; i <6 ;i++){
           window.draw(Weapon[i]); 
        }
        window.draw(P1);
        window.draw(choosing);
        window.display();
    }
    
    while(t4.getElapsedTime().asSeconds() <= 2.0f){
        
    }
    

    while(p2Choosed == false){
        for(int i = 0; i<6; i++){
            Weapon[i].setScale(1,1);
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
            p2.weapen.setTexture(weaponTexture[0]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[0].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
            p2.weapen.setTexture(weaponTexture[1]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[1].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
            p2.weapen.setTexture(weaponTexture[2]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[2].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
            p2.weapen.setTexture(weaponTexture[3]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[3].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)){
            p2.weapen.setTexture(weaponTexture[4]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[4].setScale(2,2);
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)){
            p2.weapen.setTexture(weaponTexture[5]);
            p2Choosed = true;
            t4.restart();
            button.play();
            Weapon[5].setScale(2,2);
        }
    
        window.clear();
        for(int i = 0; i <6 ;i++){
           window.draw(Weapon[i]); 
        }
        window.draw(P2);
        window.draw(choosing);
        window.display();
    }

    while(t4.getElapsedTime().asSeconds() <= 2.0f){
        
    }



        
        
        
        
        t2.restart();
            


        

        while (ready == false)
        {

            if (t2.getElapsedTime().asSeconds() <= 1)
            {
                start.setString("3");
                window.clear();
                window.draw(start);
                window.display();
            }

            if (t2.getElapsedTime().asSeconds() >= 1 && t2.getElapsedTime().asSeconds() <= 2)
            {
                start.setString("2");
                window.clear();
                window.draw(start);
                window.display();
            }
            if (t2.getElapsedTime().asSeconds() >= 2 && t2.getElapsedTime().asSeconds() <= 3)
            {
                start.setString("1");
                window.clear();
                window.draw(start);
                window.display();
            }
            if (t2.getElapsedTime().asSeconds() >= 3 && t2.getElapsedTime().asSeconds() <= 4)
            {
                start.setString("start!!!!");
                window.clear();
                window.draw(start);
                window.display();
            }
            if (t2.getElapsedTime().asSeconds() >= 4)
            {
                ready = true;
            }
        }

        
        
        

        //----------------------music setting------------------------//
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) == true)
        {
            music.setVolume(music.getVolume() - 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) == true)
        {
            music.setVolume(music.getVolume() + 10);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) == true)
        {
            music.pause();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) == true)
        {
            music.play();
        }

        //------------------animation---------------------------//
        p1MovingRightAni.Moving(0.3f);
        p1MovingLeftAni.Moving(0.3f);
        p2MovingRightAni.Moving(0.3f);
        p2MovingLeftAni.Moving(0.3f);
        p1.weapen.rotate(5);
        p2.weapen.rotate(5);

        

        //-----------------------player1 movement--------------------//

        if (p1.attacked == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
            {
                p1.moving = true;
                p1.facingRight = false;
                p1.xVelocity = moveSpeed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
            {
                p1.moving = true;
                p1.facingRight = true;
                p1.xVelocity = moveSpeed;
            }
        }

        if (p1.jumping == false && p1.attacked == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
            {
                p1.jumping = true;
                p1.yVelocity = jumpSpeed;
            }
        }

        if (Player1.getPosition().x <= 0)
        {
            Player1.move(width, 0);
        }
        else if (Player1.getPosition().x >= width)
        {
            Player1.move(-width, 0);
        }

        if (p1.moving == true)
        {
            if (p1.facingRight == true)
            {
                Player1.move(p1.xVelocity, 0);
            }
            else
            {
                Player1.move(-p1.xVelocity, 0);
            }

            p1.xVelocity -= moveSpeed / 10;
            if (p1.xVelocity <= 0)
            {
                p1.moving = false;
            }
        }
        if (p1.attacked == true)
        {
            if (p2.weapenFacingRight == true)
            {
                Player1.move(p1.xVelocity, 0);
            }
            else
            {
                Player1.move(-p1.xVelocity, 0);
            }
            p1.xVelocity -= attackedSpeed / 20;
            if (p1.xVelocity <= 0)
            {
                p1.attacked = false;
            }
        }
        if (p1.jumping == true)
        {

            Player1.move(0, -p1.yVelocity);
            p1.yVelocity -= jumpSpeed / 20;

            if (p1.yVelocity == -jumpSpeed)
            {
                Player1.move(0, -p1.yVelocity);
                p1.jumping = false;
            }
        }

        //-----------------Player2 movement-----------------//

        if (p2.attacked == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true)
            {
                p2.moving = true;
                p2.facingRight = false;
                p2.xVelocity = moveSpeed;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true)
            {
                p2.moving = true;
                p2.facingRight = true;
                p2.xVelocity = moveSpeed;
            }
        }

        if (p2.jumping == false && p2.attacked == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true)
            {
                p2.jumping = true;
                p2.yVelocity = jumpSpeed;
            }
        }

        if (Player2.getPosition().x <= 0)
        {
            Player2.move(width, 0);
        }
        else if (Player2.getPosition().x >= width)
        {
            Player2.move(-width, 0);
        }

        if (p2.moving == true)
        {
            if (p2.facingRight == true)
            {
                Player2.move(p2.xVelocity, 0);
            }
            else
            {
                Player2.move(-p2.xVelocity, 0);
            }

            p2.xVelocity -= moveSpeed / 10;
            if (p2.xVelocity <= 0)
            {
                p2.moving = false;
            }
        }
        if (p2.attacked == true)
        {
            if (p1.weapenFacingRight == true)
            {
                Player2.move(p2.xVelocity, 0);
            }
            else
            {
                Player2.move(-p2.xVelocity, 0);
            }
            p2.xVelocity -= attackedSpeed / 20;
            if (p2.xVelocity <= 0)
            {
                p2.attacked = false;
            }
        }
        if (p2.jumping == true)
        {

            Player2.move(0, -p2.yVelocity);
            p2.yVelocity -= jumpSpeed / 20;

            if (p2.yVelocity == -jumpSpeed)
            {
                Player2.move(0, -p2.yVelocity);
                p2.jumping = false;
            }
        }

        //-----------------hp issue---------------------//
        if (p1.hp >= 300)
            p1.hpBar.setFillColor(sf::Color::Green);
        if (p1.hp <= 300)
            p1.hpBar.setFillColor(sf::Color::Yellow);
        if (p1.hp <= 100)
            p1.hpBar.setFillColor(sf::Color::Red);

        if (p2.hp >= 300)
            p2.hpBar.setFillColor(sf::Color::Green);
        if (p2.hp <= 300)
            p2.hpBar.setFillColor(sf::Color::Yellow);
        if (p2.hp <= 100)
            p2.hpBar.setFillColor(sf::Color::Red);

        //-----------------fire!!!---------------------------//
        if (p1.weapenExist == false && p1CD.getElapsedTime().asSeconds() >= 0.5f)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) == true)
            {
                p1.weapenExist = true;
                p1.weapen.setPosition(Player1.getPosition());
                p1CD.restart();
                if (p1.facingRight == true)
                {
                    p1.weapenFacingRight = true;
                }
                else
                    p1.weapenFacingRight = false;
            }
        }
        if (p1.weapenExist == true)
        {
            if (p1.weapenFacingRight == true)
            {

                p1.weapen.move(20, 0);
            }
            else
            {
                p1.weapen.move(-20, 0);
            }
            if (p1.weapen.getPosition().x >= width || p1.weapen.getPosition().x <= 100)
            {
                p1.weapenExist = false;
                p1.weapen.setPosition(0, 0);
            }
        }

        if (p2.weapenExist == false && p2CD.getElapsedTime().asSeconds() >= 1.0f)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift) == true)
            {
                p2.weapenExist = true;
                p2.weapen.setPosition(Player2.getPosition());
                p2CD.restart();
                if (p2.facingRight == true)
                {
                    p2.weapenFacingRight = true;
                }
                else
                    p2.weapenFacingRight = false;
            }
        }
        if (p2.weapenExist == true)
        {
            if (p2.weapenFacingRight == true)
            {

                p2.weapen.move(20, 0);
            }
            else
            {
                p2.weapen.move(-20, 0);
            }
            if (p2.weapen.getPosition().x >= width || p2.weapen.getPosition().x <= 100)
            {
                p2.weapenExist = false;
                p2.weapen.setPosition(0, 0);
            }
        }

        if (isTouched(p1.weapen, Player2))
        {
            punch.play();
            if (p1.weapenFacingRight == true)
            {
                p2.attacked = true;
                p2.moving = false;

                p2.xVelocity = attackedSpeed;

                p2.hp -= weapenDmg;

                p2.hpBar.setSize(sf::Vector2f(p2.hp, 50));

                p1.weapenExist = false;
                p1.weapen.setPosition(0, 0);
            }
            else
            {
                p2.attacked = true;
                p2.moving = false;

                p2.xVelocity = attackedSpeed;

                p2.hp -= weapenDmg;

                p2.hpBar.setSize(sf::Vector2f(p2.hp, 50));

                p1.weapenExist = false;
                p1.weapen.setPosition(0, 0);
            }
        }
        if (isTouched(p2.weapen, Player1))
        {
            punch.play();
            if (p2.weapenFacingRight == true)
            {

                p1.attacked = true;
                p1.moving = false;

                p1.xVelocity = attackedSpeed;

                p1.hp -= weapenDmg;

                p1.hpBar.setSize(sf::Vector2f(p1.hp, 50));

                p2.weapenExist = false;
                p2.weapen.setPosition(0, 0);
            }
            else
            {
                p1.attacked = true;
                p1.moving = false;

                p1.xVelocity = attackedSpeed;
                p1.hp -= weapenDmg;

                p1.hpBar.setSize(sf::Vector2f(p1.hp, 50));

                p2.weapenExist = false;
                p2.weapen.setPosition(0, 0);
            }
        }

        if (ifKeepGoing == true)
        {
            window.clear(sf::Color(150, 150, 150));
            window.draw(background);
            if (p1.hp <= 0)
            {
                deathSound.play();
                Player1.setTextureRect(defaultRect);
                Player2.setTextureRect(defaultRect);
                Player1.setTexture(deadP1);

                if (p2.facingRight == true)
                {
                    Player2.setTexture(p1faceRight);
                }
                else
                {
                    Player2.setTexture(p1faceRight);
                }
                window.draw(Player2);

                window.draw(Player1);
                if (p1.weapenExist == true)
                {
                    window.draw(p1.weapen);
                }
                if (p2.weapenExist == true)
                {
                    window.draw(p2.weapen);
                }
                window.draw(p1.hpBar);
                window.draw(p2.hpBar);
                window.draw(p1.heart);
                window.draw(p2.heart);
                
                ifKeepGoing = false;
                window.draw(restart);
            }
            else if (p2.hp <= 0)
            {
                deathSound.play();
                Player1.setTextureRect(defaultRect);
                Player2.setTextureRect(defaultRect);
                Player2.setTexture(deadP2);

                if (p1.facingRight == true)
                {
                    Player1.setTexture(p1faceRight);
                }
                else
                {
                    Player1.setTexture(p1faceLeft);
                }
                window.draw(Player1);

                window.draw(Player2);
                if (p1.weapenExist == true)
                {
                    window.draw(p1.weapen);
                }
                if (p2.weapenExist == true)
                {
                    window.draw(p2.weapen);
                }
                window.draw(p1.hpBar);
                window.draw(p2.hpBar);
                window.draw(p1.heart);
                window.draw(p2.heart);

                ifKeepGoing = false;
                window.draw(restart);
            }
            else if (p1.hp > 0 && p2.hp > 0)
            {
                if(p1.moving == true){
                    
                    if(p1.facingRight == true){
                        Player1.setTexture(p1MovingRightTexture);
                        Player1.setTextureRect(p1MovingRightAni.rectSourceSprite);
                        window.draw(Player1);
                        
                    }
                    else{
                        Player1.setTexture(p1MovingLeftTexture);
                        Player1.setTextureRect(p1MovingLeftAni.rectSourceSprite);
                        
                    }
                }
                else{
                    Player1.setTextureRect(defaultRect);

                    if(p1.facingRight == true){
                        
                        Player1.setTexture(p1faceRight);
                        
                    }
                    else{
                        Player1.setTexture(p1faceLeft);
                        
                    }
                }

                if(p1.jumping == true){
                    Player1.setTextureRect(defaultRect);
                    if(p1.yVelocity >= 0){
                        if(p1.facingRight == true)
                        Player1.setTexture(p1JumpingRight1);
                        else
                        Player1.setTexture(p1JumpingLeft1);
                    }
                    else{
                        if(p1.facingRight == true)
                        Player1.setTexture(p1JumpingRight2);
                        else
                        Player1.setTexture(p1JumpingLeft2);
                    }
                }

                if(p2.moving == true){
                    
                    if(p2.facingRight == true){
                        Player2.setTexture(p2MovingRightTexture);
                        Player2.setTextureRect(p2MovingRightAni.rectSourceSprite);
                        
                        
                    }
                    else{
                        Player2.setTexture(p2MovingLeftTexture);
                        Player2.setTextureRect(p2MovingLeftAni.rectSourceSprite);
                        
                    }
                }
                else{
                    Player2.setTextureRect(defaultRect);
                    if(p2.facingRight == true){
                        Player2.setTexture(p2faceRight);
                        
                    }
                    else{
                        Player2.setTexture(p2faceLeft);
                        
                    }
                }
                if(p2.jumping == true){
                    Player2.setTextureRect(defaultRect);
                    if(p2.yVelocity >= 0){
                        if(p2.facingRight == true)
                        Player2.setTexture(p2JumpingRight1);
                        else
                        Player2.setTexture(p2JumpingLeft1);
                    }
                    else{
                        if(p2.facingRight == true)
                        Player2.setTexture(p2JumpingRight2);
                        else
                        Player2.setTexture(p2JumpingLeft2);
                    }
                }

                window.draw(Player1);
                window.draw(Player2);




                if (p1.weapenExist == true)
                {
                    window.draw(p1.weapen);
                }
                if (p2.weapenExist == true)
                {
                    window.draw(p2.weapen);
                }
                
                window.draw(Guide);
                window.draw(p1.hpBar);
                window.draw(p2.hpBar);
                window.draw(p1.heart);
                window.draw(p2.heart);
                
                
            }
            window.display();   
            
        }

        while (ifKeepGoing == false)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == true)
            {
                p1.hp = 500;
                p2.hp = 500;
                Player1.setPosition(500, 1150);
                Player2.setPosition(1500, 1150);
                p1.hpBar.setSize(sf::Vector2f(p1.hp, 50));
                p2.hpBar.setSize(sf::Vector2f(p2.hp, 50));
                ifKeepGoing = true;
                ready = false;
            }
            
            
        }
    }
    return 0;
}

bool isTouched(sf::Sprite A, sf::Sprite B)
{
    sf::Vector2f Apos(0, 0);
    sf::Vector2f Bpos(0, 0);
    Apos = A.getPosition();
    Bpos = B.getPosition();
    if (abs(Apos.x - Bpos.x) <= 100 && abs(Apos.y - Bpos.y) <= 100)
    {
        return true;
    }
    return false;
}