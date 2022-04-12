#ifndef ENNEMYFLYINGEYE_H
#define ENNEMYFLYINGEYE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "../Animation.h"
#include "../Ground.h"
#include "../Collider.h"
#include "../Living_Entity.h"
#include "../Player.h"
#include <fstream>
#include <vector>

class EnnemyFlying_eye : public Living_Entity
{
    public:
        //primary//
        EnnemyFlying_eye(float x = 0, float y = 0);
        virtual ~EnnemyFlying_eye();

        //actions//
        void Behavior(float deltaTime);
        void GetHit(sf::Vector2f direction = sf::Vector2f(0,0), int damage = 0);
        void Attacking(float deltaTime);

        //Updates//
        void UpdateMovement(float deltaTime);
        void UpdateAnimation(float deltaTime);
        void OnCollision(sf::Vector2f direction);
        void CollisionCheck(Ground platform);
        void DamageCheck(Player &player, Collider &playerCollider, std::vector<Collider> &playerHitbox, std::vector<Collider> &playerAttacks);

        //setData//
        void SetDistance(sf::Vector2f distance) {m_distanceToPlayer = distance;}

    protected:
        sf::Vector2f m_distanceToPlayer;
        bool m_playerDetected;


    private:
};

#endif // ENNEMYFLYINGEYE_H
