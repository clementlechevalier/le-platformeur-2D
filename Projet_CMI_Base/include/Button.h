#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
    public:
        Button(sf::Vector2f position = sf::Vector2f(0,0), sf::RectangleShape dimentions = sf::RectangleShape(sf::Vector2f(100, 40)));
        virtual ~Button();
        void Draw(sf::RenderWindow& window);
        void Clicking(sf::Vector2f mousePos);
        void SetPosition(sf::Vector2f position) {m_body.setPosition(position);}
        void setSize(sf::Vector2f dimentions) {m_body.setSize(dimentions);}
        void Clicked() {m_checked = true; m_body.setFillColor(sf::Color(0,150,0));}
        void Unclicked() {m_checked = false; m_body.setFillColor(sf::Color(30,120,30));}
        void Activated() {m_activated = true;}
        void Deactivate() {m_activated = false;}
        bool IsChecked() {return m_checked;}

    protected:
    sf::RectangleShape m_body;
    bool m_activated;
    bool m_checked;

    private:
};

#endif // BUTTON_H
