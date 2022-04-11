#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../include/Map.h"
#include "../include/Ground.h"
#include "../include/ecriture_hit_box.h"

void positionMouse(int *x,int *y,sf::View view,sf::RenderWindow *window){
    while(!sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
    *x=sf::Mouse::getPosition((*window)).x +(view.getCenter().x-(*window).getSize().x/2);
    *y= sf::Mouse::getPosition().y +(view.getCenter().y-(*window).getSize().y/2);
    std::cout<<sf::Mouse::getPosition((*window)).x +(view.getCenter().x-(*window).getSize().x/2) <<" "<< sf::Mouse::getPosition((*window)).y +(view.getCenter().y-(*window).getSize().y/2)<<"\n";
    while(sf::Mouse::isButtonPressed(sf::Mouse::Left)){}
}


void creeHitBox(std::vector<std::vector<int>> *listeHitBox,sf::View view,sf::RenderWindow *window){
    int sx,sy,ix,iy,type;
    std::vector<int> laHitBox;
    std::cout<<"saisi le type, 1=plateforme, 2=porte, 3=piége:   ";std::cin>>type;
    std::cout<<"clique sur l'angle supérieur gauche\n";positionMouse(&sx,&sy,view,window);
    std::cout<<"clique sur l'angle inférieur droit\n";positionMouse(&ix,&iy,view,window);
    switch (type){
        case 1:
            laHitBox={ix-sx,iy-sy,sx,sy,type};
            break;
        case 2:
            int i,o,rx,ry;
            std::cout<<"saisi l'indice de la carte suivante:   ";std::cin>>i;
            std::cout<<"saisi l'orientation de la carte suivante:   ";std::cin>>o;
            std::cout<<"clique sur le point de réaparition\n";positionMouse(&rx,&ry,view,window);
            laHitBox={ix-sx,iy-sy,sx,sy,type,i,o,rx,ry};
            break;
        case 3:
            int apx,apy;
            std::cout<<"clique sur le point de réaparition\n";positionMouse(&apx,&apy,view,window);
            laHitBox={ix-sx,iy-sy,sx,sy,type,apx,apy};
            break;
    }
    (*listeHitBox).push_back(laHitBox);
}
//fonction suppr qui demande l'indice du truc à supprimé(fonction au dessus sert à trouver l'indice)
void supppr(std::vector<std::vector<int>> *listeHitBox){
    int i;
    std::cout<<"entre l'indice du rectangle a supprimer:   ";std::cin>>i;
    (*listeHitBox).erase((*listeHitBox).begin()+i);
}

//modif carré qui avec indice donne les x y l h du carré et te permet de les modifier.
void modifHitBox(std::vector<std::vector<int>> *listeHitBox){
    int i,m;
    std::cout<<"entre l'indice du rectangle a modifier:   ";std::cin>>i;
    std::cout<<"son abcysse est: "<<(*listeHitBox)[i][2]<<"\nrentre ce que tu veut ajouter à l'abcysse:   ";std::cin>>m;
    (*listeHitBox)[i][2]=(*listeHitBox)[i][2]+m;
    std::cout<<"son ordonnée est: "<<(*listeHitBox)[i][3]<<"\nrentre ce que tu veut ajouter à l'ordonnée:   ";std::cin>>m;
    (*listeHitBox)[i][3]=(*listeHitBox)[i][3]+m;
    std::cout<<"sa largeur est: "<<(*listeHitBox)[i][0]<<"\nrentre ce que tu veut ajouter à la largeur:   ";std::cin>>m;
    (*listeHitBox)[i][0]=(*listeHitBox)[i][0]+m;
    std::cout<<"sa hauteur est: "<<(*listeHitBox)[i][1]<<"\nrentre ce que tu veut ajouter à la hauteur:   ";std::cin>>m;
    (*listeHitBox)[i][1]=(*listeHitBox)[i][1]+m;
}


void ecritDansTxt(std::string nom,std::vector<std::vector<int>> *vect){
    std::fstream fichier;
    fichier.open(nom,std::ios::out);
	fichier<<"2000 1250\n";
    for(int i=0;i<(*vect).size();i++){
		for(int y=0;y<(*vect)[i].size();y++){
			fichier<<(*vect)[i][y]<<" ";		
		}
		fichier<<"\n";
    }
    fichier.close();
}

void getMapData(std::string txtName, Map &mapping,std::vector<std::vector<int>> *vect)
/*
@txtName -> name and address of the text file containing the map data
@mapping -> Map object where we will store the map data

the first two words are the width and height of the map, we take them separately from the rest
then we get every info 5 by 5 to add the platforms the infos are :
width, height, position x, position y, platform type
then we store it in the Map object
*/
{
	(*vect).clear();
    mapping.m_levelGrounds.clear();
    std::ifstream monFlux(txtName);
    std::vector<int> numbers;
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
            if (numbers[4]%100 == 1)//type 1 means we're dealing with a regular platform
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4]);
                mapping.AddGround(platform);
				(*vect).push_back(numbers);
                numbers.clear();
            }
            else if (numbers[4]%100 == 2 && numbers.size() == 9) //type 2 means we're dealing with a door so we have more parameters
                // the new parameters are : 1-the index of the map we're heading 2-the direction 3-4- the location
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4], (int)numbers[5], numbers[6], sf::Vector2f(numbers[7], numbers[8]));
                mapping.AddGround(platform);
				(*vect).push_back(numbers);
                numbers.clear();
            }
            else if (numbers[4]%100 == 3 && numbers.size() == 7) //type 3 means we're dealing with a trap so we have more parameters
                // the new parameters are 1-2- the location
            {
                Ground platform(sf::Vector2f(numbers[0], numbers[1]), sf::Vector2f(numbers[2], numbers[3]), (int)numbers[4], sf::Vector2f(numbers[5], numbers[6]));
                mapping.AddGround(platform);
				(*vect).push_back(numbers);
                numbers.clear();
            }
        }
    }
}




