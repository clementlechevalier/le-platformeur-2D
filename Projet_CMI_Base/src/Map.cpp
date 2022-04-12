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

Map::~Map()
{
    //dtor
}
