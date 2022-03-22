#ifndef MAP_H
#define MAP_H

#include "Ground.h"
#include <vector>

class Map
{
    public:
        Map();
        Map(int const& width, int const& height);
        void AddGround(Ground ground);//add a platofrm to m_levelGrounds
        void SetMapSize(float width, float height);
        sf::Vector2f GetMapSize() {return m_mapSize.getSize();}
        virtual ~Map();

    public:
        std::vector<Ground> m_levelGrounds;//I had to make it public because modifying it is very important. It's the list of all platforms on the level

    protected:

        sf::RectangleShape m_mapSize;


    private:
};

#endif // MAP_H
