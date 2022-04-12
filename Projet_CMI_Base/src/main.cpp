#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <math.h>
#include "../include/Map.h"
#include "../include/Ground.h"
#include "../include/Animation.h"
#include "../include/Player.h"
#include "../include/Collider.h"
#include "../include/Fading.h"
#include "../include/Living_Entity.h"
#include "../include/Ennemies/EnnemyFlying_eye.h"
#include "../include/Ennemies/EnnemySkeleton.h"
#include "../include/Ennemies/EnnemyBoss1.h"


static const float VIEW_WIDTH = 1920.0f; // defines the size of the view and the window, we might have to separate the two at some point
static const float VIEW_HEIGHT = 1080.0f;


void ResizeView(const sf::RenderWindow & window, sf::View& view)
//not used anymore because it made the view bug, but it was made to set things to the right size after changing window size
{
       float aspectRatio = float(window.getSize().x / float(window.getSize().y));
       view.setSize(VIEW_WIDTH * aspectRatio, VIEW_WIDTH);
}

void getMapData(std::string txtName, Map &mapping)
/*
@txtName -> name and address of the text file containing the map data
@mapping -> Map object where we will store the map data

the first two words are the width and height of the map, we take them separately from the rest
then we get every info 5 by 5 to add the platforms the infos are :
width, height, position x, position y, platform type
then we store it in the Map object
*/
{
    std::ifstream monFlux(txtName);
    std::vector<float> numbers;
    float number;

    for(int i=0; i < 2; i++)
    {
    monFlux >> number;
    numbers.push_back(number);
    }
    mapping.SetMapSize(numbers[0], numbers[1]);
    numbers.resize(0);

    while(monFlux >> number)
    {
        numbers.push_back(number);
        if (numbers.size()>= 5)
        {
            if (numbers[4] == 1)//type 1 means we're dealing with a regular platform
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4]);
                mapping.AddGround(platform);
                numbers.resize(0);
            }
            else if (numbers[4] ==2 && numbers.size() == 9) //type 2 means we're dealing with a door so we have more parameters
                // the new parameters are : 1-the index of the map we're heading 2-the direction 3-4- the location
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4], (int)numbers[5], numbers[6], sf::Vector2f(numbers[7], numbers[8]));
                mapping.AddGround(platform);
                numbers.resize(0);
            }
            else if (numbers[4] ==3 && numbers.size() == 7) //type 3 means we're dealing with a trap so we have more parameters
                // the new parameters are 1-2- the location
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4], sf::Vector2f(numbers[5], numbers[6]));
                mapping.AddGround(platform);
                numbers.resize(0);
            }
        }
    }
}

void checkAllCollisions(Player &player, sf::Vector2f direction, Map &mapping, sf::RenderWindow& window)
/*
@player @direction -> informations regarding the player character in order to have him collide with object in a right way but will have to be modified
@mapping -> a Map object from which we get every informations we need regarding the map the player is currently in

we test the player collision with every object in the map then test if the player is falling. will have to be modified when more objects will need
collision.
*/
{
    Collider playerCollider =player.GetCollider();
    std::vector<Collider> playerHitbox =player.GetDamageRecievedHitboxes();
    std::vector<Collider> playerAttacks =player.GetDamageDealtHitboxes();
    player.UnCollide();

    for(unsigned int i=0; i < mapping.m_levelGrounds.size(); i++)
    {
        player.CheckCollisions(mapping.m_levelGrounds[i]);
        for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
        {
            Collider EnnemyCollider = mapping.m_levelEnnemyFlying_eye[enmy].GetCollider();
            mapping.m_levelEnnemyFlying_eye[enmy].CollisionCheck(mapping.m_levelGrounds[i]);
            mapping.m_levelEnnemyFlying_eye[enmy].SetDistance(EnnemyCollider.Distance(playerCollider));
        }
        for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
        {
            Collider EnnemyCollider = mapping.m_levelEnnemySkeleton[enmy].GetCollider();
            mapping.m_levelEnnemySkeleton[enmy].CollisionCheck(mapping.m_levelGrounds[i]);
            mapping.m_levelEnnemySkeleton[enmy].SetDistance(EnnemyCollider.Distance(playerCollider));
        }
        for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
        {
            Collider EnnemyCollider = mapping.m_levelEnnemyBoss1[enmy].GetCollider();
            mapping.m_levelEnnemyBoss1[enmy].CollisionCheck(mapping.m_levelGrounds[i]);
            mapping.m_levelEnnemyBoss1[enmy].SetDistance(EnnemyCollider.Distance(playerCollider));
        }
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
    {
        mapping.m_levelEnnemyFlying_eye[enmy].DamageCheck(player, playerCollider, playerHitbox, playerAttacks);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
    {
        mapping.m_levelEnnemySkeleton[enmy].DamageCheck(player, playerCollider, playerHitbox, playerAttacks);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
    {
        mapping.m_levelEnnemyBoss1[enmy].DamageCheck(player, playerCollider, playerHitbox, playerAttacks);
    }
}

void updateAllMovement(float deltatime, Player &player, Map &mapping)
{
    player.UpdateMovement(deltatime);
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
    {
        mapping.m_levelEnnemyFlying_eye[enmy].UpdateMovement(deltatime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
    {
        mapping.m_levelEnnemySkeleton[enmy].UpdateMovement(deltatime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
    {
        mapping.m_levelEnnemyBoss1[enmy].UpdateMovement(deltatime);
    }
}

void updateAllAnimation(float deltatime, Player &player, Map &mapping)
{
    player.UpdateAnimation(deltatime);
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
    {
        mapping.m_levelEnnemyFlying_eye[enmy].UpdateAnimation(deltatime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
    {
        mapping.m_levelEnnemySkeleton[enmy].UpdateAnimation(deltatime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
    {
        mapping.m_levelEnnemyBoss1[enmy].UpdateAnimation(deltatime);
    }
}

void movementAll(Player &player, Map &mapping, float deltaTime)
{
    player.Inputs(deltaTime);
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
    {
        mapping.m_levelEnnemyFlying_eye[enmy].Behavior(deltaTime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
    {
        mapping.m_levelEnnemySkeleton[enmy].Behavior(deltaTime);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
    {
        mapping.m_levelEnnemyBoss1[enmy].Behavior(deltaTime);
    }
}

void drawAll(sf::RenderWindow& window, Player &player, Fading &fadeScreen, Map &mapping, sf::View view)
/*
simple drawAll function where we will draw every entities that needs to be drawn on the window
*/
{
    sf::Texture heartTexture;
    heartTexture.loadFromFile("Sprites/HUD/heartFull.png");
    sf::RectangleShape heart;
    heart.setSize(sf::Vector2f(50, 50));
    heart.setTexture(&heartTexture);
    for(int i = 0; i < player.GetHealth(); i++){
        heart.setPosition(view.getCenter().x - VIEW_WIDTH/2 + 60*i, view.getCenter().y - VIEW_HEIGHT/2);
        window.draw(heart);
    }
    heartTexture.loadFromFile("Sprites/HUD/heartEmpty.png");
    heart.setTexture(&heartTexture);
    for(int i = player.GetHealth(); i < player.GetMaxHealth(); i++){
        heart.setPosition(view.getCenter().x - VIEW_WIDTH/2 + 60*i, view.getCenter().y - VIEW_HEIGHT/2);
        window.draw(heart);
    }
    for(unsigned int i=0; i < mapping.m_levelGrounds.size(); i++)
    {
        mapping.m_levelGrounds[i].Draw(window);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyFlying_eye.size() ; enmy ++)
    {
        mapping.m_levelEnnemyFlying_eye[enmy].Draw(window);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemySkeleton.size() ; enmy ++)
    {
        mapping.m_levelEnnemySkeleton[enmy].Draw(window);
    }
    for(int enmy = 0; enmy < (int)mapping.m_levelEnnemyBoss1.size() ; enmy ++)
    {
        mapping.m_levelEnnemyBoss1[enmy].Draw(window);
    }
    player.Draw(window);
    fadeScreen.Draw(window, view);
}

int main()
{
    float deltaTime = 0.0f;//used so that any machine runs the game at the same speed but is the source of some bugs when not handled carefully
    sf::Clock clock;
    sf::Vector2f direction;//will be changed, is currently the player direction
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Pastis World"); //creation of the window and the view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));


    int const level1MapNumber = 3;//number of map in the first level
    int currentLevel = 0;//the current level we're in
    float view_x;//variables used to display the view
    float view_y;
    Map level1[level1MapNumber];//a list of all map in the first level
    getMapData("Data/000.txt", level1[0]);//we collect data for the map from getMapData
    getMapData("Data/001.txt", level1[1]);//we collect data for the map from getMapData
    getMapData("Data/002.txt", level1[2]);//we collect data for the map from getMapData

    Player player;
    player.SetPosition(sf::Vector2f(800, 0));

    EnnemyFlying_eye patrick(0, 300);
    EnnemyFlying_eye pascal(1200, 300);
    EnnemyFlying_eye michelieu(1500, 500);
    EnnemySkeleton jeanPatrick(1400, 900);
    EnnemySkeleton michel(1200, 300);
    EnnemySkeleton fabrice(300, 700);
    EnnemyBoss1 jeanPaul(900, 600);
    level1[0].AddEnnemyFlying_eye(patrick);
    level1[1].AddEnnemyFlying_eye(pascal);
    level1[1].AddEnnemyFlying_eye(michelieu);
    level1[0].AddEnnemySkeleton(michel);
    level1[0].AddEnnemySkeleton(jeanPatrick);
    level1[1].AddEnnemySkeleton(fabrice);
    level1[2].AddEnnemyBoss1(jeanPaul);
    Fading fadeScreen(0.2, sf::RectangleShape(sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT)));
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();//we get the time that took the machine to get through the whole cycle each time so we can calculate movement based on that
        if (deltaTime > 1.0f/20.0f)// we set a framerate limit from which the game will slow down
        {
            deltaTime = 1.0f/20.0f;
        }

        sf::Event evnt;
        while (window.pollEvent(evnt))//check what events are called
        {
            if (evnt.type == sf::Event::Closed){
                window.close();
            }
            //else if (evnt.type == sf::Event::Resized){
            //    ResizeView(window, view);
            //}
            //player.EventStorage(evnt);//not used anymore
        }

        movementAll(player, level1[currentLevel], deltaTime);//the character updates depending on the player inputs
        if(player.Door(deltaTime, currentLevel) || player.GetTrap() > 0.5)//handle doors and trap events
        {
            fadeScreen.Fade(deltaTime);
        }
        else if (player.GetTrap() >= 0.4 && player.GetTrap() <= 0.5)
        {
            player.SetPosition(player.GetNextLocation());
        }
        else
        {
            fadeScreen.UnFade(deltaTime);
            if (player.GetTrap() > 0 && player.GetTrap() <= 0.1)
            {
                player.Freed();
            }
        }


        view_x = std::min(level1[currentLevel].GetMapSize().x-VIEW_WIDTH/2  , std::max(player.GetPosition().x, VIEW_WIDTH/2));//the view must only show the inside of a map so we set boundaries here
        view_y = std::min(level1[currentLevel].GetMapSize().y-VIEW_HEIGHT/2, std::max(player.GetPosition().y, VIEW_HEIGHT/2));
        view.setCenter(view_x, view_y);//and set the view center
        window.setView(view);


        window.clear(sf::Color(150,150,150));//we then refresh the window and redraw everything
        updateAllMovement(deltaTime,player, level1[currentLevel]);
        checkAllCollisions(player, direction, level1[currentLevel], window);
        updateAllAnimation(deltaTime,player, level1[currentLevel]);

        drawAll(window, player, fadeScreen, level1[currentLevel], view);
        window.display();
    }

    return 0;
}
