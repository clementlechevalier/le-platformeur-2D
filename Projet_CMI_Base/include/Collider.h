#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include <math.h>

class Collider
{
    public:
    Collider(sf::RectangleShape &body, int type = 1, bool active = true, sf::Vector2f prevLocation = sf::Vector2f(-10000, -10000));//nothing can be at coordinate -10000,-10000 or it's collision will bug
    virtual ~Collider();

    void SetPosition(float dx, float dy) {m_body.setPosition(dx, dy);}//moves the colliding objects
    void ChangeActive();

    bool CheckCollision(Collider& other);//check if other and the current object are colliding. return true if they are. we can add sf::RenderWindow& window
    sf::Vector2f Repel(Collider other, sf::Vector2f& direction);
    sf::Vector2f Distance(Collider other);

    sf::Vector2f GetPosition() {return m_body.getPosition();}
    sf::Vector2f GetPreviousPosition() {return m_prevLocation;}
    sf::Vector2f GetSize() {return m_body.getSize();}
    float GetRotation() {return m_body.getRotation()*(M_PI/180);}
    float GetRadius() {return m_radius;}
    bool GetActive() {return m_active;}

    protected:

    sf::RectangleShape m_body;
    float m_radius;
    int m_type;//1 fot rectangle and 2 for circles
    bool m_active;
    sf::Vector2f m_prevLocation;

    private:
};

#endif // COLLISION_H
