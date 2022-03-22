#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <math.h>
#include "../include/Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
    m_animation(texture, imageCount, switchTime)
{
    m_speed = speed;
    m_rotation = 0;
    m_row = 0;
    m_faceRight = true;
    m_texture.setSize(sf::Vector2f(100.0f, 100.0f));
    //m_texture.setOrigin(m_texture.getSize() / 2.0f);
    m_texture.setPosition(200.0f, 200.0f);
    m_texture.setTexture(texture);
    m_texture.setRotation(m_rotation);

    m_mainHitbox.setSize(sf::Vector2f(100.0f, 100.0f));
    //m_mainHitbox.setOrigin(m_mainHitbox.getSize() / 2.0f);
    m_mainHitbox.setPosition(200.0f, 200.0f);
    m_mainHitbox.setRotation(m_rotation);

    m_jumpFall = 5000.0f;
    m_canUseEvent = true;
    m_canMove = true;
    m_inDoor = 0;
    m_trap = 0;
}

Player::~Player()
{

}

void Player::EventStorage(sf::Event event) //pour l'instant inutile
{

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            m_nextEvent = "jump";
            m_storageDuration = 1000;
            m_canUseEvent = false;
        }
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        m_canUseEvent = true;
    }
}

void Player::Movement(float deltaTime)
{
    m_prevLocation = m_mainHitbox.getPosition();
    if (m_storageDuration > 1)
    {
        m_storageDuration --;
    }
    else if (m_storageDuration == 1)
    {
        m_nextEvent = "";
        m_storageDuration = 0;
    }

    //MOVEMENTS//
    //horizontal movements//

    m_velocity.x = 0.0f;
    if (m_canMove && m_inDoor == 0)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            m_velocity.x = -m_speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            m_velocity.x = m_speed;
        }
    }

    //vertical movements//

    //simple jump//
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_canJump) //jump height is approximately 250
    {
        m_canJump = false;
        m_velocity.y = -800.0f;
        m_jumpDuration = 1.0f;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_jumpDuration > 0.0f)
    {
        m_velocity.y -= m_jumpFall*deltaTime;
        m_jumpDuration -= 3.1*deltaTime;

    }

    //falling//
    else
    {
        m_jumpDuration = 0.0f;
        if (m_jumpFall < 5000.0f)
        {
            m_jumpFall += 5;
        }
    }

    if (m_velocity.y < 1000.0f)
    {
        m_velocity.y += m_jumpFall*deltaTime;
    }

    //ANIMATIONS//
    if (m_velocity.x == 0.0f)
    {
        m_row = 0;
    }
    else
    {
        m_row = 0;
        if(m_velocity.x > 0.0f){
            m_faceRight = true;
        }
        else {
            m_faceRight = false;
        }
    }
    Update(deltaTime);
}

void Player::Update(float deltaTime)
{
    if (m_trap > 0)
    {
        m_trap -= deltaTime;
    }
    m_animation.Update(m_row, deltaTime, m_faceRight);
    m_texture.setTextureRect(m_animation.getUvRect());
    m_mainHitbox.move(m_velocity * deltaTime);
    m_texture.setPosition(sf::Vector2f(m_mainHitbox.getPosition().x,m_mainHitbox.getPosition().y));
}

bool Player::Door(float deltaTime, int &currentMap)
{
    if (m_inDoor > 0)
    {
        m_inDoor -=deltaTime;
        if (m_nextDirection ==1)
        {
            m_velocity.x = m_speed;
        }
        else if (m_nextDirection ==2)
        {
            m_velocity.x = -m_speed;
        }
        if (m_inDoor >= 0.2 && m_inDoor <= 0.3)
        {
            m_mainHitbox.setPosition(m_nextLocation);
            currentMap = m_nextMap;
        }
        Update(deltaTime);
        return true;
    }
    else
    {
        m_inDoor = 0;
    }
    return false;
}

void Player::GoThroughDoor(sf::Vector2f nextLocation, int nextDirection, int nextMap)
{
    if(m_inDoor <= 0)
    {
        m_inDoor = 0.5;
        m_canJump = false;
        m_nextLocation = nextLocation;
        m_nextDirection = nextDirection;
        m_nextMap = nextMap;
    }
}

void Player::SetPosition(sf::Vector2f position)
{
    m_mainHitbox.setPosition(position);
}


void Player::Trapped(sf::Vector2f nextLocation)
{
    if (m_trap <= 0)
    {
        m_nextLocation = nextLocation;
        m_trap = 0.5f;
        m_canJump = false;
        m_canMove = false;
    }
}

void Player::OnCollision(sf::Vector2f direction)
{
    if (direction.x < 0.0f)//collision on the left
    {
        m_velocity.x = 0.0f;
    }
    else if (direction.x > 0.0f)//collision on the right
    {
        m_velocity.x = 0.0f;
    }

    if (direction.y < 0.0f)//collision on the bottom
    {
        m_velocity.y = 0.0f;
        m_jumpFall = 5000.0f;
        m_canJump = true;
    }
    else if (direction.y > 0.0f)//collision on the top
    {
        m_velocity.y = 0.0f;
        m_jumpDuration = 0.0f;
        m_jumpFall = 3000.0f;
    }
}



void Player::Draw(sf::RenderWindow& window)
{
    m_mainHitbox.setFillColor(sf::Color::Cyan);
    window.draw(m_mainHitbox);
    window.draw(m_texture);
}
