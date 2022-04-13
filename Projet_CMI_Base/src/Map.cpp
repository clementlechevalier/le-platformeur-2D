#include "../include/Map.h"
#include <iostream>

Map::Map()//, Ground const floor[]
{
    sf::Texture texture;
    texture.setRepeated(true);
    texture.loadFromFile("Sprites/background/tempBackground.png");
    m_backgroundsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleUpperLeft.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleUpper.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleUpperRight.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleRight.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleBottomRight.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleBottom.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleBottomLeft.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/jungleLeft.png");
    m_platformsTexture.push_back(texture);
    texture.loadFromFile("Sprites/jungleAssets/junglePlatform.png");
    m_platformsTexture.push_back(texture);
}

void Map::SetMapSize(float width, float height)
{
    sf::Vector2f mapsize(width, height);
    m_mapSize.setSize(mapsize);
}

void Map::AddGround(Ground ground)
{
    m_levelGrounds.push_back(ground);
}

void Map::AddEnnemySkeleton(EnnemySkeleton ennemy)
{
    m_levelEnnemySkeleton.push_back(ennemy);
}

void Map::AddEnnemyFlying_eye(EnnemyFlying_eye ennemy)
{
    m_levelEnnemyFlying_eye.push_back(ennemy);
}

void Map::AddEnnemyBoss1(EnnemyBoss1 ennemy)
{
    m_levelEnnemyBoss1.push_back(ennemy);
}

void Map::DrawBackground(sf::RenderWindow& window)
{
    sf::RectangleShape texture;
    texture.setPosition(0,0);
    texture.setSize(sf::Vector2f(m_mapSize.getSize().x, m_mapSize.getSize().y));
    texture.setTexture(&m_backgroundsTexture[0]);
    window.draw(texture);
}

void Map::DrawPlatforms(sf::RenderWindow& window)
{
    sf::RectangleShape drawing;
    for(unsigned int i=0; i < m_levelGrounds.size(); i++)
    {
        //m_levelGrounds[i].Draw(window);
        drawing.setSize(m_levelGrounds[i].GetSize());//draw the inside
        drawing.setTextureRect(sf::IntRect(0,0, m_levelGrounds[i].GetSize().x/2, m_levelGrounds[i].GetSize().y/2));
        drawing.setTexture(&m_platformsTexture[8]);
        drawing.setPosition(m_levelGrounds[i].GetPosition());
        window.draw(drawing);

        drawing.setSize(sf::Vector2f(32,32));//draw the four corners
        drawing.setTextureRect(sf::IntRect(0,0, 16, 16));
        drawing.setTexture(&m_platformsTexture[0]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(-4, -4));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[2]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(m_levelGrounds[i].GetSize().x-28, -4));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[2]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(m_levelGrounds[i].GetSize().x-28, -4));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[4]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + m_levelGrounds[i].GetSize() + sf::Vector2f(-28, -28));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[6]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(-4, m_levelGrounds[i].GetSize().y -28));
        window.draw(drawing);

        drawing.setTexture(&m_platformsTexture[1]);//draw the up and down sides
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(28, -4));
        drawing.setTextureRect(sf::IntRect(0,0, m_levelGrounds[i].GetSize().x/2 -28, 16));
        drawing.setSize(sf::Vector2f(m_levelGrounds[i].GetSize().x - 56, 32));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[5]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(28, m_levelGrounds[i].GetSize().y-28));
        window.draw(drawing);

        drawing.setTexture(&m_platformsTexture[3]);//draw the left and right sides
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(-4, 28));
        drawing.setTextureRect(sf::IntRect(0,0, 16, m_levelGrounds[i].GetSize().y/2 -28));
        drawing.setSize(sf::Vector2f(32, m_levelGrounds[i].GetSize().y - 56));
        window.draw(drawing);
        drawing.setTexture(&m_platformsTexture[7]);
        drawing.setPosition(m_levelGrounds[i].GetPosition() + sf::Vector2f(m_levelGrounds[i].GetSize().x-28, 28));
        window.draw(drawing);

    }
}

Map::~Map()
{
    //dtor
}
