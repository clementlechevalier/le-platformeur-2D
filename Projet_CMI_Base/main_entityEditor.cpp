#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include "include/TextBox.h"
#include "include/Button.h"

static const float VIEW_WIDTH = 1920.0f; // defines the size of the view and the window, we might have to separate the two at some point
static const float VIEW_HEIGHT = 1000.0f;



void windowDraw(sf::RenderWindow& window, TextBox txtbxs[], const int &txtbxNbr, Button buttons[], const int &buttonsNbr, bool working)
/*
simple drawAll function where we will draw every entities that needs to be drawn on the window
*/
{
    window.clear(sf::Color(150,150,150));
    sf::RectangleShape bg(sf::Vector2f(1580, 864));
    bg.setPosition(0, VIEW_HEIGHT-864);
    bg.setFillColor(sf::Color(180,180,180));
    window.draw(bg);

    for(int i = 0; i < txtbxNbr; i++)
    {
        txtbxs[i].Draw(window);
    }
    for(int i = 0; i < buttonsNbr; i++)
    {
        buttons[i].Draw(window);
    }

    if (!working)
    {
        window.display();
    }
}


void windowDrawWorking(sf::RenderWindow& window, sf::RectangleShape imageShape, sf::Texture &image, const int &MaxLign, const int &MaxColumn, const int &currentLign, const int &currentColumn)
{
    sf::Vector2f SpriteSize;
    sf::Vector2f SpritePos;
    sf::Vector2f Scale(1.0f, 1.0f);
    if (currentColumn == 0){
        SpriteSize.x = image.getSize().x;
        SpritePos.x = 0;
    }
    else {
        SpriteSize.x = image.getSize().x/MaxColumn;
        SpritePos.x = (currentColumn-1) * image.getSize().x/MaxColumn;
    }
    if (currentLign == 0){
        SpriteSize.y = image.getSize().y;
        SpritePos.y = 0;
    }
    else {
        SpriteSize.y = image.getSize().y/MaxLign;
        SpritePos.y = (currentLign-1) * image.getSize().y/MaxLign;
    }
    while (SpriteSize.x*Scale.x > 1500 || SpriteSize.y*Scale.y > 850)
    {
        Scale *= 0.95f;
    }
    imageShape.setPosition(sf::Vector2f(790 - (SpriteSize.x * Scale.x)/2, 575- (SpriteSize.y* Scale.y)/2));
    imageShape.setScale(Scale);
    imageShape.setSize(sf::Vector2f(SpriteSize.x, SpriteSize.y));
    imageShape.setTexture(&image);
    imageShape.setTextureRect(sf::IntRect(SpritePos.x, SpritePos.y, SpriteSize.x, SpriteSize.y));
    window.draw(imageShape);
    window.display();
}
void onClick(const sf::RenderWindow& window, const sf::Vector2i& mousePos, TextBox txtbxs[], const int &txtbxNbr, Button buttons[], const int &buttonsNbr)
{
    for(int i = 0; i < txtbxNbr; i++)
    {
        txtbxs[i].Selection(sf::Vector2f(mousePos.x *(VIEW_WIDTH/window.getSize().x), mousePos.y * (VIEW_HEIGHT/window.getSize().y)));
    }
    for(int i = 0; i < buttonsNbr; i++)
    {
        buttons[i].Clicking(sf::Vector2f(mousePos.x *(VIEW_WIDTH/window.getSize().x), mousePos.y * (VIEW_HEIGHT/window.getSize().y)));
    }
}


bool buttonOneEvent(TextBox txtbxs[], int const &txtbxNumber, sf::Texture &picture, std::ofstream &txtFile, int &column, int &lign)
{
    bool canWork = true;
    sf::Texture picTexture;
    if (picTexture.loadFromFile(txtbxs[0].GetText()))
    {
        picture.loadFromFile(txtbxs[0].GetText());
    }
    else{
        txtbxs[0].BecomeRed();
        canWork = false;
    }
    txtFile.open(txtbxs[1].GetText(), std::ios::out);
    if (txtFile.bad() || txtbxs[1].GetText().length() < 1)
    {
        txtbxs[1].BecomeRed();
        canWork = false;
    }
    try{
        if (std::stoi(txtbxs[2].GetText()) > 0){
            lign = std::stoi(txtbxs[2].GetText());
        }
        else
        {
            txtbxs[2].BecomeRed();
            canWork = false;
        }
    }
    catch (const std::invalid_argument &e){
        txtbxs[2].BecomeRed();
        canWork = false;
    }
    catch (const std::out_of_range &e){
        txtbxs[2].BecomeRed();
        canWork = false;
    }
    try{
        if (std::stoi(txtbxs[3].GetText()) > 0){
            column = std::stoi(txtbxs[3].GetText());
        }
        else
        {
            txtbxs[3].BecomeRed();
            canWork = false;
        }
    }
    catch (const std::invalid_argument &e){
        txtbxs[3].BecomeRed();
        canWork = false;
    }
    catch (const std::out_of_range &e){
        txtbxs[3].BecomeRed();
        canWork = false;
    }
    return canWork;
}

void GetFrame(TextBox txtbxs[], int &currentLign, int &currentColumn)
{
    try{
        currentLign = std::stoi(txtbxs[10].GetText());
    }
    catch (const std::invalid_argument &e){
        if(!txtbxs[10].IsSelected())
        {
            txtbxs[10].BecomeRed();
        }
        currentLign = 0;
    }
    catch (const std::out_of_range &e){
        if(!txtbxs[10].IsSelected())
        {
            txtbxs[10].BecomeRed();
        }
        currentLign = 0;
    }
    try{
        currentColumn = std::stoi(txtbxs[11].GetText());
    }
    catch (const std::invalid_argument &e){
        if(!txtbxs[11].IsSelected())
        {
            txtbxs[11].BecomeRed();
        }
        currentColumn = 0;
    }
    catch (const std::out_of_range &e){
        if(!txtbxs[11].IsSelected())
        {
            txtbxs[11].BecomeRed();
        }
        currentColumn = 0;
    }

}

int main()
{
    bool working=false;
    sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Entity Editor"); //creation of the window and the view

    sf::RectangleShape mainPictureShape;
    sf::Texture mainPicture;
    std::ofstream txtFile;
    int MaxColumn = 0;
    int MaxLign = 0;
    int currentColumn = 0;
    int currentLign = 0;

    int const txtbxNumber = 12;
    TextBox txtbxs[txtbxNumber];
    txtbxs[0].SetPosition(sf::Vector2f(250, 490));
    txtbxs[0].SetString("Sprite Adress");
    txtbxs[0].Activated();
    txtbxs[1].SetPosition(sf::Vector2f(770, 490));
    txtbxs[1].SetString("txt destination");
    txtbxs[1].Activated();
    txtbxs[2].SetPosition(sf::Vector2f(250, 550));
    txtbxs[2].SetString("lign number");
    txtbxs[2].Activated();
    txtbxs[3].SetPosition(sf::Vector2f(770, 550));
    txtbxs[3].SetString("column number");
    txtbxs[3].Activated();

    txtbxs[4].SetPosition(sf::Vector2f(20, 20));
    txtbxs[4].SetString("Position X");
    txtbxs[5].SetPosition(sf::Vector2f(540, 20));
    txtbxs[5].SetString("Position Y");
    txtbxs[6].SetPosition(sf::Vector2f(20, 80));
    txtbxs[6].SetString("Width");
    txtbxs[7].SetPosition(sf::Vector2f(540, 80));
    txtbxs[7].SetString("Height");
    txtbxs[8].SetPosition(sf::Vector2f(1060, 20));
    txtbxs[8].SetString("Type");
    txtbxs[9].SetPosition(sf::Vector2f(1060, 80));
    txtbxs[9].SetString("Angle");

    txtbxs[10].SetPosition(sf::Vector2f(1600, 20));
    txtbxs[10].setSize(sf::Vector2f(300, 40));
    txtbxs[10].SetString("frame lign");
    txtbxs[11].SetPosition(sf::Vector2f(1600, 80));
    txtbxs[11].setSize(sf::Vector2f(300, 40));
    txtbxs[11].SetString("frame column");

    int const buttonNbr = 1;
    Button buttons[buttonNbr];
    buttons[0].SetPosition(sf::Vector2f(1300, 520));
    buttons[0].Activated();

    while (window.isOpen())
    {

        sf::Event evnt;
        while (window.pollEvent(evnt))//check what events are called
        {
            if (evnt.type == sf::Event::Closed){
                window.close();
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                onClick(window, sf::Mouse::getPosition(window), txtbxs, txtbxNumber, buttons, buttonNbr);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                for(int i = 0; i < txtbxNumber ; i ++)
                {
                    txtbxs[i].Unselect();
                }
            }
            else if (evnt.type == sf::Event::TextEntered)
            {
                for(int i = 0; i < txtbxNumber ; i ++)
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    {
                        txtbxs[i].Erase();
                    }
                    else
                    {
                        txtbxs[i].Write(evnt);
                    }
                }
            }
            if (buttons[0].IsChecked())
            {
                if (buttonOneEvent(txtbxs, txtbxNumber, mainPicture, txtFile, MaxColumn, MaxLign))
                {
                    for(int i = 0; i < 4; i ++){
                        txtbxs[i].Deactivate();}
                    for(int i = 4; i < 12; i ++){
                        txtbxs[i].Activated();}
                    buttons[0].Deactivate();
                    working = true;
                }
                buttons[0].Unclicked();
            }
        }
        windowDraw(window, txtbxs, txtbxNumber, buttons, buttonNbr, working);
        if (working)
        {
            GetFrame(txtbxs, currentLign, currentColumn);
            windowDrawWorking(window,mainPictureShape, mainPicture, MaxLign, MaxColumn, currentLign, currentColumn);
        }

    }


    return 0;
}

