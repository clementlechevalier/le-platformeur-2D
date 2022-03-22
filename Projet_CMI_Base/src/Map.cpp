#include "../include/Map.h"
#include <iostream>

Map::Map()//, Ground const floor[]
{

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

Map::~Map()
{
    //dtor
}
