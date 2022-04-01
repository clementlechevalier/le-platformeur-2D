#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <typeinfo>
#include <math.h>
#include <vector>
#include "Animation.h"
#include "Collider.h"
#include <fstream>
#include <vector>

class Player
{
    public:
        Player();
        virtual ~Player();
        void Inputs(float deltaTime);//defines all player movements depending on the inputs received
        void Update(float deltaTime);//Updates the player depending on what he did
        void EventStorage(sf::Event event);//not used anymore, but might be used one day. Used to store player inputs
        void Draw (sf::RenderWindow& window);
        void OnCollision(sf::Vector2f direction);
        void SetPosition(sf::Vector2f position){ m_mainHitbox.setPosition(position);}
        void Attacking(float deltaTime);
        void GetHit();

        void Trapped(sf::Vector2f nextLocation);
        void Freed() {m_canJump = true; m_canMove = true;}

        bool Door(float deltaTime, int &currentMap);
        void GoThroughDoor(sf::Vector2f nextLocation, int nextDirection, int nextMap);

        void Falling() {m_canJump = false;}

        sf::Vector2f GetPosition() { return m_mainHitbox.getPosition();}
        sf::Vector2f GetNextLocation() { return m_nextLocation;}
        Collider GetCollider() { return Collider(m_mainHitbox, 1, true, m_prevLocation);}
        std::vector<Collider> GetColliders();
        float GetTrap() {return m_trap;}

    protected:
        void getHitboxes(std::string txtFileName);

    protected:
    sf::RectangleShape m_texture;
    sf::RectangleShape m_mainHitbox;
    sf::Vector2f m_velocity;
    sf::Vector2f m_nextLocation; //when going through doors
    sf::Vector2f m_prevLocation; //for collisions
    Animation m_animationIdle;
    Animation m_animationAttack;
    Animation m_animationRun;
    Animation m_animationJump;
    Animation m_animationFall;
    Animation m_animationJumpFall;
    Animation m_animationHurt;
    sf::Texture m_textureIdle;
    sf::Texture m_textureAttack;
    sf::Texture m_textureRun;
    sf::Texture m_textureJump;
    sf::Texture m_textureFall;
    sf::Texture m_textureJumpFall;
    sf::Texture m_textureHurt;
    unsigned int m_row;//for animation
    unsigned int m_frame;
    unsigned int m_storageDuration;//for action storage
    int m_nextMap;//when going through doors
    int m_attacking;
    int m_nextDirection;//when going through doors
    float m_textureOffset;//used when the character turns
    float m_rotation;
    float m_speed;
    float m_scale;
    float m_trap;//active when the player touched a trap
    float m_inDoor;//when going through doors
    float m_attackDuration;
    float m_knockback;
    float m_maxKnockback;
    bool m_faceRight;
    bool m_canUseEvent;//for event storage
    bool m_canJump;
    bool m_canMove;
    bool m_jumpAnimationTransition;
    float m_jumpDuration;
    float m_jumpFall;
    std::string m_nextEvent;
    std::vector<std::vector<std::vector<sf::RectangleShape>>> m_collisionHitboxes;//first layer is the type of animation, 2nd the frame, 3rd every hitboxes (usually only one)
    std::vector<std::vector<std::vector<sf::RectangleShape>>> m_damageTakenHitboxes;
    std::vector<std::vector<std::vector<sf::RectangleShape>>> m_damageDealtHitboxes;

    private:
};

#endif // PLAYER_H
