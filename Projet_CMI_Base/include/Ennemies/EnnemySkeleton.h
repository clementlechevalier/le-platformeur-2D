#ifndef ENNEMYSKELETON_H
#define ENNEMYSKELETON_H

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

class EnnemySkeleton : public Living_Entity
{
    public:
        //primary//
        EnnemySkeleton(float x = 0, float y = 0);
        virtual ~EnnemySkeleton();

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

#endif // ENNEMYSKELETON_H
