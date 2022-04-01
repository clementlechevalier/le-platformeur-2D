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
#include "../include/MainMenu.h"


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

void checkAllCollisions(Player &player, sf::Vector2f direction, Map &mapping, int &actualMap, sf::RenderWindow& window)
/*
@player @direction -> informations regarding the player character in order to have him collide with object in a right way but will have to be modified
@mapping -> a Map object from which we get every informations we need regarding the map the player is currently in

we test the player collision with every object in the map then test if the player is falling. will have to be modified when more objects will need
collision.
*/
{
    Collider playerCollider =player.GetCollider();

    bool playerColliding = false;
    for(unsigned int i=0; i < mapping.m_levelGrounds.size(); i++)
    {
        if (mapping.m_levelGrounds[i].GetCollider().CheckCollision(playerCollider, direction, window))
        {
            if (mapping.m_levelGrounds[i].GetType() ==1)
            {
                player.OnCollision(direction);
                playerColliding = true;
            }
            if (mapping.m_levelGrounds[i].GetType() ==2)
            {
                player.GoThroughDoor(mapping.m_levelGrounds[i].GetNextLocation(), mapping.m_levelGrounds[i].GetNextDirection(), mapping.m_levelGrounds[i].GetNextMap());
            }
            if (mapping.m_levelGrounds[i].GetType() ==3)
            {
                player.Trapped(mapping.m_levelGrounds[i].GetNextLocation());
            }
        }
    }
    if (!playerColliding)
        {
            player.Falling();
        }
}


void drawAll(sf::RenderWindow& window, Player &player, Fading &fadeScreen, Map &mapping, sf::View view)
/*
simple drawAll function where we will draw every entities that needs to be drawn on the window
*/
{

    for(unsigned int i=0; i < mapping.m_levelGrounds.size(); i++)
    {
        mapping.m_levelGrounds[i].Draw(window);
    }
    player.Draw(window);
    fadeScreen.Draw(window, view);
}

int main()
{
    RenderWindow window(VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Main Menu", Style::Default);
    MainMenu mainMenu(window.getSize().x, window.getSize().y);

    RectangleShape background;
    background.setSize(Vector2f(VIEW_WIDTH, VIEW_HEIGHT));
    Texture Maintexture;
    Maintexture.loadFromFile("Textures/610766.jpg");
    background.setTexture(&Maintexture);
    

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    mainMenu.MoveUp();
                    break;
                }
                if (event.key.code == Keyboard::Down)
                {
                    mainMenu.MoveDown();
                    break;
                }
                if (event.key.code == Keyboard::Return){
                    RenderWindow OPTIONS(VideoMode(960, 720), "Options");
                    RenderWindow ABOUT(VideoMode(960, 720), "ABOUT");

                    int x = mainMenu.MainMenuPressed();
                    if (x == 0){
                        while (window.isOpen())
                        {
                            Event aevent;
                            while (window.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                {
                                    window.close();
                                }
                                if (aevent.type == Event::KeyPressed)
                                {
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        window.close();
                                    }
                                }
                            }
                            OPTIONS.close();
                            ABOUT.close();
                            window.clear();
                            
                            float deltaTime = 0.0f;//used so that any machine runs the game at the same speed but is the source of some bugs when not handled carefully
                            sf::Clock clock;

                            sf::Vector2f direction;//will be changed, is currently the player direction
                            sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));


                            int const level1MapNumber = 2;//number of map in the first level
                            int currentLevel = 0;//the current level we're in
                            float view_x;//variables used to display the view
                            float view_y;
                            Map level1[level1MapNumber];//a list of all map in the first level
                            getMapData("Data/000.txt", level1[0]);//we collect data for the map from getMapData
                            getMapData("Data/001.txt", level1[1]);//we collect data for the map from getMapData

                            Player player;
                            player.SetPosition(sf::Vector2f(1000, 0));

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

                                player.Movement(deltaTime);//the character updates depending on the player inputs
                                if(player.Door(deltaTime, currentLevel) || player.GetTrap() > 0.3)//handle doors and trap events
                                {
                                    fadeScreen.Fade(deltaTime);
                                }
                                else if (player.GetTrap() >= 0.2 && player.GetTrap() <= 0.3)
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
                                drawAll(window, player, fadeScreen, level1[currentLevel], view);
                                checkAllCollisions(player, direction, level1[currentLevel], currentLevel, window);

                                window.display();
                            }

                            return 0;
                        }
                    }
                    if (x == 1)
                    {
                        while (OPTIONS.isOpen())
                        {
                            Event aevent;
                            while (OPTIONS.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                {
                                    OPTIONS.close();
                                }
                                if (aevent.type == Event::KeyPressed){
                                    if (aevent.key.code == Keyboard::Escape)
                                    {
                                        OPTIONS.close();
                                    }
                                }
                            }
                            window.close();
                            OPTIONS.clear();
                            ABOUT.close();
                            OPTIONS.display();
                        }
                    }
                    if (x == 2){
                        while (ABOUT.isOpen()){
                            Event aevent;
                            while (ABOUT.pollEvent(aevent)){
                                if (aevent.type == Event::Closed)
                                {
                                    ABOUT.close();
                                }
                                if (aevent.type == Event::KeyPressed) {
                                    if (aevent.key.code == Keyboard::Escape){
                                        ABOUT.close();
                                    }
                                }
                            }
                            window.close();
                            OPTIONS.close();
                            ABOUT.clear();
                            ABOUT.display();
                        }
                    }
                    if (x == 3)
                        window.close();
                    break;
                }
            }
        }
        window.clear();
        window.draw(background);
        mainMenu.draw(window);
        window.display();
    }
}