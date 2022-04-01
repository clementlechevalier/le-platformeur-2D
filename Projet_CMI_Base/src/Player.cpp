#include <SFML/Graphics.hpp>
#include <typeinfo>
#include <math.h>
#include "../include/Player.h"

Player::Player()
{
    m_textureIdle.loadFromFile("Sprites/FreeKnight/Used/_Idle.png");
    m_animationIdle = Animation(m_textureIdle, sf::Vector2u(10, 1), 0.15f);
    m_textureAttack.loadFromFile("Sprites/FreeKnight/Used/_AttackCombo2hit.png");
    m_animationAttack = Animation(m_textureAttack, sf::Vector2u(10, 1), 0.08f);
    m_textureRun.loadFromFile("Sprites/FreeKnight/Used/_Run.png");
    m_animationRun = Animation(m_textureRun, sf::Vector2u(10, 1), 0.08f);
    m_textureJump.loadFromFile("Sprites/FreeKnight/Used/_Jump.png");
    m_animationJump = Animation(m_textureJump, sf::Vector2u(3, 1), 0.15f);
    m_textureFall.loadFromFile("Sprites/FreeKnight/Used/_Fall.png");
    m_animationFall = Animation(m_textureFall, sf::Vector2u(3, 1), 0.15f);
    m_textureJumpFall.loadFromFile("Sprites/FreeKnight/Used/_JumpFallInbetween.png");
    m_animationJumpFall = Animation(m_textureJumpFall, sf::Vector2u(2, 1), 0.15f);
    m_textureHurt.loadFromFile("Sprites/FreeKnight/Used/_Hit.png");
    m_animationHurt = Animation(m_textureHurt, sf::Vector2u(1, 1), 0.5f);

    m_speed = 500.0f;
    m_attacking = 0;
    m_scale = 2;
    m_rotation = 0;
    m_row = 0;
    m_faceRight = true;
    m_texture.setSize(sf::Vector2f(120.0f * m_scale, 80.0f * m_scale));
    m_texture.setPosition(200.0f, 200.0f);
    m_texture.setTexture(&m_textureIdle);
    m_texture.setRotation(m_rotation);

    m_mainHitbox.setSize(sf::Vector2f(120.0f * m_scale, 80.0f * m_scale));
    m_mainHitbox.setPosition(200.0f, 200.0f);
    m_mainHitbox.setRotation(m_rotation);

    m_jumpFall = 5000.0f;
    m_canUseEvent = true;
    m_attacking = 0;
    m_canMove = true;
    m_inDoor = 0;
    m_trap = 0;
    m_textureOffset = 0;
    m_knockback = 0;
    m_maxKnockback = 0.5;

    getHitboxes("Hitboxes/MainCharacter/idleKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/runKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/jumpKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/fallKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/jumpFallKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/TwoAttacksKnight.txt");
    getHitboxes("Hitboxes/MainCharacter/hurtKnight.txt");
}

Player::~Player()
{

}

void Player::getHitboxes(std::string txtFileName)
{
    std::ifstream txtFile(txtFileName);
    std::vector<std::vector<sf::RectangleShape>> collisionHitboxes;
    std::vector<std::vector<sf::RectangleShape>> damageTakenHitboxes;
    std::vector<std::vector<sf::RectangleShape>> damageDealtHitboxes;
    std::vector<sf::RectangleShape> currentCollisionHitboxes;
    std::vector<sf::RectangleShape> currentDamageTakenHitboxes;
    std::vector<sf::RectangleShape> currentDamageDealtHitboxes;
    char x = 0;
    int level = 0;
    int lign = 0;
    int column = 0;
    int number = 0;
    std::vector<int> hitbox;
    sf::RectangleShape currentHitbox;
    if(txtFile)
    {
        while(txtFile.get(x))
        {
            if(x == '[')
            {
                level ++;
                number = 0;
            }
            else if(x == ']')
            {
                if(level == 1){
                    lign++;
                    column = 0;}
                else if(level == 2){
                    collisionHitboxes.push_back(currentCollisionHitboxes);
                    damageTakenHitboxes.push_back(currentDamageTakenHitboxes);
                    damageDealtHitboxes.push_back(currentDamageDealtHitboxes);
                    currentCollisionHitboxes.clear();
                    currentDamageTakenHitboxes.clear();
                    currentDamageDealtHitboxes.clear();
                    column++;}
                else if(level == 3){
                    hitbox.push_back(number);
                    currentHitbox.setPosition(sf::Vector2f(hitbox[0] * m_scale, hitbox[1] * m_scale));
                    currentHitbox.setSize(sf::Vector2f(hitbox[2] * m_scale, hitbox[3] * m_scale));
                    currentHitbox.setRotation(hitbox[5]);
                    if(hitbox[4] == 1){
                        currentCollisionHitboxes.push_back(currentHitbox);}
                    else if(hitbox[4] == 2){
                        currentDamageTakenHitboxes.push_back(currentHitbox);}
                    else if(hitbox[4] == 3){
                        currentDamageDealtHitboxes.push_back(currentHitbox);}
                    }
                level --;
                number = 0;
                hitbox = {};
            }
            else if(x == ',' && level == 3)
            {
                hitbox.push_back(number);
                number = 0;;
            }
            else
            {
                number *= 10;
                number += (int)x - 48;
            }

        }
        m_collisionHitboxes.push_back(collisionHitboxes);
        m_damageDealtHitboxes.push_back(damageDealtHitboxes);
        m_damageTakenHitboxes.push_back(damageTakenHitboxes);
    }
    else
    {
        std::cout << "can't open txt file : " << txtFileName << std::endl;
    }
    txtFile.close();
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

void Player::Attacking(float deltaTime)
{
    if(m_attackDuration > 0)
    {
        m_attackDuration -= deltaTime;
        if(m_animationAttack.getCurrentImage() == 4){
            m_animationAttack.SetCurrentImage(5);
            m_attackDuration = 0;
            }
        else if(m_animationAttack.getCurrentImage() == 9){
            m_animationAttack.SetCurrentImage(0);
            m_attackDuration = 0;
            }
    }
    else
    {
        m_attacking = 0;
    }
}

void Player::Inputs(float deltaTime)
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

    bool playerMovementEnabled = ( m_inDoor <= 0 && m_knockback <= 0);
    if(playerMovementEnabled)
    {
        //MOVEMENTS//
        //horizontal movements//

        m_velocity.x = 0.0f;
        if (m_canMove && playerMovementEnabled)
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
        if (m_velocity.y < 1000.0f && !m_canJump)
        {
            m_velocity.y += m_jumpFall*deltaTime;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            m_attackDuration = 0.40;
            m_attacking = 1;
        }
    }

    //ANIMATIONS//
    if (m_velocity.x == 0.0f)
    {
        m_row = 0;
    }
    else
    {
        if(m_attackDuration <= 0)
        {
            if(m_velocity.x > 0.0f){
                if(!m_faceRight){
                    m_texture.scale(sf::Vector2f(-1.f, 1.f));}
                    m_textureOffset = 0;
                m_faceRight = true;
            }
            else if (m_velocity.x < 0.0f){
                if(m_faceRight){
                    m_texture.scale(sf::Vector2f(-1.f, 1.f));}
                    m_textureOffset = 240;
                m_faceRight = false;
            }
        }
    }
}

void Player::Update(float deltaTime)
{
    if (m_trap > 0){m_trap -= deltaTime;}
    if (m_attacking > 0){Attacking(deltaTime);}
    if (m_knockback > 0){m_knockback -= deltaTime;}
    else {m_knockback = 0;}

    m_mainHitbox.move(m_velocity * deltaTime);
    if (m_knockback > 0)
    {
        m_row = 6;
        m_frame = m_animationHurt.getCurrentImage();
        m_animationHurt.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureHurt);
        m_texture.setTextureRect(m_animationHurt.getUvRect());
    }
    else if (m_attacking == 1)
    {
        m_row = 5;
        m_frame = m_animationAttack.getCurrentImage();
        m_animationAttack.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureAttack);
        m_texture.setTextureRect(m_animationAttack.getUvRect());
    }
    else if (m_velocity.y < 0)
    {
        m_row = 2;
        m_frame = m_animationJump.getCurrentImage();
        m_animationJump.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureJump);
        m_texture.setTextureRect(m_animationJump.getUvRect());
    }
    else if (m_velocity.y > 0)
    {
        m_row = 3;
        m_frame = m_animationFall.getCurrentImage();
        m_animationFall.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureFall);
        m_texture.setTextureRect(m_animationFall.getUvRect());
    }
    else if(m_velocity.x == 0)
    {
        m_row = 0;
        m_frame = m_animationIdle.getCurrentImage();
        m_animationIdle.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureIdle);
        m_texture.setTextureRect(m_animationIdle.getUvRect());
    }
    else if(m_velocity.x != 0)
    {
        m_row = 1;
        m_frame = m_animationRun.getCurrentImage();
        m_animationRun.Update(0, deltaTime, m_faceRight);
        m_texture.setTexture(&m_textureRun);
        m_texture.setTextureRect(m_animationRun.getUvRect());
    }
    m_texture.setPosition(sf::Vector2f(m_mainHitbox.getPosition().x + m_textureOffset,m_mainHitbox.getPosition().y));
}

bool Player::Door(float deltaTime, int &currentMap)
{
    if (m_inDoor > 0)
    {
        m_inDoor -= deltaTime;
        if (m_nextDirection ==1)//going right
        {
            m_velocity.x = m_speed;
        }
        else if (m_nextDirection ==2)//going left
        {
            m_velocity.x = -m_speed;
        }
        if (m_inDoor >= 0.4 && m_inDoor <= 0.5)
        {
            m_mainHitbox.setPosition(m_nextLocation);
            currentMap = m_nextMap;
        }
        if(m_inDoor > 0.3){
            return true;}
        else{
            return false;}
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
        m_attackDuration = 0;
        m_animationAttack.SetCurrentImage(0);
        m_velocity = sf::Vector2f(0.0f, 0.0f);
        m_inDoor = 0.7;
        m_canJump = false;
        m_nextLocation = nextLocation;
        m_nextDirection = nextDirection;
        m_nextMap = nextMap;
    }
}

void Player::Trapped(sf::Vector2f nextLocation)
{
    if (m_trap <= 0)
    {
        m_nextLocation = nextLocation;
        m_trap = 0.7f;
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
        m_jumpAnimationTransition = true;
        m_canJump = true;
    }
    else if (direction.y > 0.0f)//collision on the top
    {
        m_velocity.y = 0.0f;
        m_jumpDuration = 0.0f;
        m_jumpFall = 3000.0f;
    }
}

std::vector<Collider> Player::GetColliders()
{
    std::vector<Collider> returning;
    for(int i = 0; i < (int)m_collisionHitboxes[m_row][m_frame].size(); i++)
    {
        sf::RectangleShape hitbox;
        sf::Vector2f prevLoc = m_prevLocation+m_collisionHitboxes[m_row][m_frame][i].getPosition();
        hitbox.setSize(m_collisionHitboxes[m_row][m_frame][i].getSize());
        hitbox.setPosition(m_collisionHitboxes[m_row][m_frame][i].getPosition() + m_mainHitbox.getPosition());
        hitbox.setRotation(m_collisionHitboxes[m_row][m_frame][i].getRotation());
        if(!m_faceRight)
        {
            hitbox.setPosition(m_mainHitbox.getPosition().x - (m_collisionHitboxes[m_row][m_frame][i].getPosition().x) + 240 - hitbox.getSize().x, hitbox.getPosition().y);
            prevLoc.x = m_prevLocation.x - m_collisionHitboxes[m_row][m_frame][i].getPosition().x +240 -hitbox.getSize().x;
        }
        returning.push_back(Collider(hitbox, 1, true, prevLoc));
    }
    return returning;
}

void Player::Draw(sf::RenderWindow& window)
{
    /*m_mainHitbox.setFillColor(sf::Color::Cyan);
    window.draw(m_mainHitbox);
    for(int i = 0; i < (int)m_collisionHitboxes[1][m_animationRun.getCurrentImage()].size(); i++)
    {
        sf::RectangleShape drawnHitbox;
        drawnHitbox.setSize(m_collisionHitboxes[m_row][m_frame][i].getSize());
        drawnHitbox.setPosition(m_collisionHitboxes[m_row][m_frame][i].getPosition() + m_mainHitbox.getPosition());
        drawnHitbox.setRotation(m_collisionHitboxes[m_row][m_frame][i].getRotation());
        if(!m_faceRight)
        {
            drawnHitbox.setPosition(m_mainHitbox.getPosition().x - m_collisionHitboxes[m_row][m_frame][i].getPosition().x + 240 -drawnHitbox.getSize().x, drawnHitbox.getPosition().y);
        }
        window.draw(drawnHitbox);
    }*/
    window.draw(m_texture);

}

void Player::GetHit()
{
    if(m_knockback <= 0)
    {
        m_velocity = sf::Vector2f(0,0);
        m_knockback = m_maxKnockback;
    }
}
