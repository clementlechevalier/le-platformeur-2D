#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation//not too sure about this class I almost didn't modify it from the tutorial, but I eventually will
{
    public:
    Animation();
    Animation(sf::Texture texture, sf::Vector2u imageCount, float switchTime);
    virtual ~Animation();

    sf::IntRect getUvRect();
    void Update(int row, float deltaTime, bool faceRight);

    protected:

    sf::IntRect m_uvRect;
    sf::Vector2u m_imageCount;
    sf::Vector2u m_currentImage;
    float m_totalTime;
    float m_switchTime;

    private:
};

#endif // ANIMATION_H
