#ifndef ENNEMYBOSS1_H
#define ENNEMYBOSS1_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "../Animation.h"
#include "../Collider.h"
#include "../Living_Entity.h"
#include "../Player.h"
#include "../Ground.h"
#include <fstream>
#include <vector>

class EnnemyBoss1 : public Living_Entity
{
    public:
        //primary//
        EnnemyBoss1(float x = 0, float y = 0);
        virtual ~EnnemyBoss1();

        //actions//
        void Behavior(float deltaTime);
        void GetHit(sf::Vector2f direction = sf::Vector2f(0,0), int damage = 0);
        void Attacking(float deltaTime);
        void ChangePhase();

        //Updates//
        void UpdateMovement(float deltaTime);
        void UpdateAnimation(float deltaTime);
        void OnCollision(sf::Vector2f direction);
        void CollisionCheck(Ground platform);
        void DamageCheck(Player &player, Collider &playerCollider, std::vector<Collider> &playerHitbox, std::vector<Collider> &playerAttacks);

        //setData//
        void SetDistance(sf::Vector2f distance) {m_distanceToPlayer = distance;}

    protected:
        Animation m_animationAttack2;
        Animation m_animationBackward;
        sf::Texture m_textureAttack2;
        sf::Texture m_textureBackward;
        sf::Vector2f m_distanceToPlayer;
        bool m_playerDetected;
        float counter;
        int m_attack1Counter;
        int m_attack2Counter;
        int m_attack3Counter;
        int m_phase;


    private:
};

#endif // ENNEMYBOSS1_H
