#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>

class Hitbox
{
    public:
        Hitbox(sf::RectangleShape hitbox, int type, float timeBeforeNext);
        virtual ~Hitbox();

    protected:
    sf::RectangleShape m_hitbox;
    int m_type;
    float m_timeBeforeNext;


    private:
};

#endif // HITBOX_H
