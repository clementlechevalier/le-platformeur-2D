#include <iostream>
#include <fstream>
#include <string>
#include "ecriture_hit_box.h"

//cree hit box avec clique souris pour position + mettre dans une liste de liste!! tous qui sera écrite dans un fichier constament
void creeHitBox(){
    int l,h,x,y,type;
    std::string laString;
    std::cout<<"saisi le type, 1=plateforme, 2=porte, 3=piége:   ";std::cin>>type;
    std::cout<<"saisi la largeur:   ";std::cin>>l;
    std::cout<<"saisi la hauteur:   ";std::cin>>h;
    std::cout<<"saisi l'abcsysse':   ";std::cin>>x;
    std::cout<<"saisi l'ordonée':   ";std::cin>>y;
    switch (type){
        case 1:
            laString=std::to_string(l)+" "+std::to_string(h)+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(type)+"\n";
            break;
        case 2:
            int i,o,xx,yy;
            std::cout<<"saisi l'indice de la carte suivante':   ";std::cin>>i;
            std::cout<<"saisi l'orientation de la carte suivante':   ";std::cin>>o;
            std::cout<<"saisi l'abscysse d'aparition':   ";std::cin>>xx;
            std::cout<<"saisi l'ordonée d'aparition':   ";std::cin>>yy;
            laString=std::to_string(l)+" "+std::to_string(h)+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(type)+" "+std::to_string(i)+" "+std::to_string(o)+" "+std::to_string(xx)+" "+std::to_string(yy)+"\n";
            break;
        case 3:
            int xxx,yyy;
            std::cout<<"saisi l'abscysse d'aparition':   ";std::cin>>xxx;
            std::cout<<"saisi l'ordonée d'aparition':   ";std::cin>>yyy;
            laString=std::to_string(l)+" "+std::to_string(h)+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(type)+" "+std::to_string(xxx)+" "+std::to_string(yyy)+"\n";
            break;
    }
    std::ofstream fichierText;
    fichierText.open("hitBox.txt",std::ofstream::app);
    fichierText<<laString;
}
//afficher prend un rectangle dans la liste dont on prend l'indice dans le terminal et remplace le 5éme élément du vecteur de la liste par son type + 100
//mettre une boucle while pour laisser le truc type 100 tant que une touche n'a pas été cliqué puis remettre le bon type

//fonction suppr qui demande l'indice du truc à supprimé(fonction au dessus sert à trouver l'indice)

//modif carré qui avec indice donne les x y l h du carré et te permet de les modifier.

void creeRectangle(){
    float a,b;
    int x,y,boll,r,g,bl,indiceCarte;
    std::ofstream fichierText;
    std::string laString;
    std::cout<<"pour que le perso passe au dessus du carré alors entre 1 sinon 0:   ";std::cin>>boll;
    std::cout<<"largeur:   ";std::cin>>a;
    std::cout<<"hauteur:   ";std::cin>>b;
    std::cout<<"abscysse:   ";std::cin>>x;
    std::cout<<"ordonnée:   ";std::cin>>y;
    std::cout<<"rouge pour la couleur en rgb(entre 0 et 255):   ";std::cin>>r;
    std::cout<<"vert pour la couleur en rgb(entre 0 et 255):   ";std::cin>>g;
    std::cout<<"bleu pour la couleur en rgb(entre 0 et 255):   ";std::cin>>bl;
    std::cout<<"donne l'indice de la carte ou on met le carré:   ";std::cin>>indiceCarte;
    laString=std::to_string(boll)+" "+std::to_string(a)+" "+std::to_string(b)+" "+std::to_string(x)+" "+std::to_string(y)+" "+std::to_string(r)+" "+std::to_string(g)+" "+std::to_string(bl)+" "+std::to_string(indiceCarte)+"\n";
    fichierText.open("decor.txt",std::ofstream::app);
    fichierText<<laString;
}


