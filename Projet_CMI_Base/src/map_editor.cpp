#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <math.h>
#include <fstream>
#include "../include/Map.h"
#include "../include/Ground.h"
#include "../include/Animation.h"
#include "../include/Player.h"
#include "../include/Collider.h"
#include "../include/Fading.h"
#include "../include/ecriture_hit_box.h"

std::vector<std::vector<int>> HITBOX;


static const float VIEW_WIDTH = 1920.0f; // defines the size of the view and the window, we might have to separate the two at some point
static const float VIEW_HEIGHT = 1080.0f;

void ResizeView(const sf::RenderWindow & window, sf::View& view)
//not used anymore because it made the view bug, but it was made to set things to the right size after changing window size
{
       float aspectRatio = float(window.getSize().x / float(window.getSize().y));
       view.setSize(VIEW_WIDTH * aspectRatio, VIEW_WIDTH);
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
    std::vector<Collider> playerColliders =player.GetColliders();

    bool playerColliding = false;
    for(unsigned int i=0; i < mapping.m_levelGrounds.size(); i++)
    {
        if (mapping.m_levelGrounds[i].GetCollider().CheckCollision(playerCollider, direction, window))
        {
            for(int j = 0; j < (int)playerColliders.size() ; j++)
            {
                if (mapping.m_levelGrounds[i].GetCollider().CheckCollision(playerColliders[j], direction, window))
                {
                    //std::cout << playerColliders[0].GetPreviousPosition().x << " " << playerColliders[0].GetPosition().x << std::endl;
                    if (mapping.m_levelGrounds[i].GetType() ==1)
                    {
                        sf::Vector2f offset = mapping.m_levelGrounds[i].GetCollider().Repel(playerColliders[j], direction);
                        player.SetPosition(player.GetPosition()-offset);
                        player.OnCollision(direction);
                        playerColliding = true;
                    }
                    if (mapping.m_levelGrounds[i].GetType() ==2)
                    {
                        player.GoThroughDoor(mapping.m_levelGrounds[i].GetNextLocation(), mapping.m_levelGrounds[i].GetNextDirection(), mapping.m_levelGrounds[i].GetNextMap());
                    }
                    if (mapping.m_levelGrounds[i].GetType() ==3)
                    {
                        player.GetHit();
                        player.Trapped(mapping.m_levelGrounds[i].GetNextLocation());
                    }
                }
            }
        }
    }
    if (!playerColliding)
        {
            player.Falling();
        }
}

void updateAll(float deltatime, Player &player)
{
    player.Update(deltatime);
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
    float deltaTime = 0.0f;//used so that any machine runs the game at the same speed but is the source of some bugs when not handled carefully
    sf::Clock clock;

    sf::Vector2f direction;//will be changed, is currently the player direction
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Pastis World"); //creation of the window and the view
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));


    int const level1MapNumber = 2;//number of map in the first level
    int currentLevel = 0;//the current level we're in
    float view_x;//variables used to display the view
    float view_y;
    Map level1[level1MapNumber];//a list of all map in the first level
    getMapData("Data/000.txt", level1[0],&HITBOX);//we collect data for the map from getMapData
    //getMapData("Data/001.txt", level1[1]);//we collect data for the map from getMapData

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
            if(evnt.type == sf::Event::TextEntered){
                std::cout<<evnt.text.unicode<<"\n";
                if(evnt.text.unicode==99){//C
					creeHitBox(&HITBOX);
	        		//std::string nomDuFichierDeLaMap="Data/00"+std::to_string(currentLevel)+".txt";
					ecritDansTxt("Data/000.txt",&HITBOX);
					getMapData("Data/000.txt",level1[0],&HITBOX);
				}
				if(evnt.text.unicode==97){affichRect(&HITBOX,level1[0]);}//A
				if(evnt.text.unicode==121){//Y
					for(int i=0;i<HITBOX.size();i++){
						for(int y=0;y<HITBOX[i].size();y++){
							std::cout<<HITBOX[i][y]<<" ";		
						}
						std::cout<<"\n";
					}
				}
                if(evnt.text.unicode==109){//M
                    modifHitBox(&HITBOX);
                    ecritDansTxt("Data/000.txt",&HITBOX);
                    getMapData("Data/000.txt", level1[0],&HITBOX);
                }
                if(evnt.text.unicode==115){//S
                    supppr(&HITBOX);
                    ecritDansTxt("Data/000.txt",&HITBOX);
                    getMapData("Data/000.txt", level1[0],&HITBOX);
                }
            }
        }

        player.Inputs(deltaTime);//the character updates depending on the player inputs
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
        updateAll(deltaTime,player);
        checkAllCollisions(player, direction, level1[currentLevel], currentLevel, window);

        drawAll(window, player, fadeScreen, level1[currentLevel], view);
        window.display();
    }

    return 0;
}
