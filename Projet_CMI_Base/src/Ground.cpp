#include "../include/Ground.h"
#include <iostream>
#include <math.h>



Ground::Ground(sf::Vector2f size, sf::Vector2f position, int type)
{
    m_body.setSize(size);
    m_rotation = 0;
    //m_body.setOrigin(size / 2.0f);
    m_body.setRotation(m_rotation);
    m_body.setTexture(nullptr);
    m_body.setPosition(position);
    m_type = type;
    m_body.setRotation(m_rotation);
}

Ground::Ground(sf::Vector2f size, sf::Vector2f position, int type, sf::Vector2f destination)
{
    m_body.setSize(size);
    //m_body.setOrigin(size / 2.0f);
    m_body.setTexture(nullptr);
    m_body.setPosition(position);
    m_type = type;
    m_destinationLocation = destination;
    m_rotation = 0;
}

Ground::Ground(sf::Vector2f size, sf::Vector2f position, int type, int destinationMap, int destinationOrientation, sf::Vector2f destination)
{
    m_body.setSize(size);
    //m_body.setOrigin(size / 2.0f);
    m_body.setTexture(nullptr);
    m_body.setPosition(position);
    m_type = type;
    m_destinationMap = destinationMap;
    m_destinationLocation = destination;
    m_destinationOrientation = destinationOrientation;
    m_rotation = 0;
}

void Ground::GetInfo()
{
}

void Ground::Draw(sf::RenderWindow& window)
{
    if(m_type == 1)
        m_body.setFillColor(sf::Color(175,175,175));
    if(m_type == 2)
        m_body.setFillColor(sf::Color::Yellow);
    if(m_type == 3)
        m_body.setFillColor(sf::Color::Red);

    window.draw(m_body);
}

Collider Ground::GetCollider()
{
    if (m_type == 1)
    {
    return Collider(m_body);
    }
    else
    {
        return Collider(m_body, 1 ,false);
    }
}

Ground::~Ground()
{
    //dtor
}

