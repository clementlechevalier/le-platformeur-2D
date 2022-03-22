#include "../include/Hitbox.h"
#include <SFML/Graphics.hpp>

Hitbox::Hitbox(sf::RectangleShape hitbox, int type, float timeBeforeNext) : m_hitbox(hitbox), m_type(type), m_timeBeforeNext(timeBeforeNext)
{
    //ctor
}

Hitbox::~Hitbox()
{
    //dtor
}
