#include <SFML/Graphics.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>

const int windowWidth = 400;
const int windowHeight = 400;

float deltatime = 1.0 / 60;
class pendulum {
  int stringLength;
  sf::CircleShape bob;
  sf::RectangleShape string{sf::Vector2f(stringLength, 1)};

  float angle;
  float angularVelocity;
  float angularAcceleration;

public:
  pendulum(int radius, int s) : bob(sf::CircleShape(radius)), stringLength(s) {
    angle = M_PI / 4;
    bob.setFillColor(sf::Color(0xb8, 0xbb, 0x28));
    string.setFillColor(sf::Color(0xfb, 0x49, 0x34));
    string.move(sf::Vector2f(windowWidth / 2, 0));
    string.rotate(sf::degrees(90.f));

    bob.move(sf::Vector2f(windowWidth / 2 - radius, stringLength - radius));
    }

    void update(float t,float deltatime){

        // angle = std::sin(t * (M_PI / 180)) ;
        angularAcceleration = -1 * (15.f/stringLength) * std::sin(angle  );
        angularVelocity += angularAcceleration * deltatime;
        angle += angularVelocity;

        std::cout << angularAcceleration << std::endl;
        string.setRotation(sf::radians(angle+ M_PI/2));

        sf::Vector2f bp(-1 * std::sin(angle) * stringLength + windowWidth/2 - bob.getRadius(), std::cos( angle ) * stringLength - bob.getRadius());

        bob.setPosition(bp);

    }

    void draw(sf::RenderWindow *window){
        window->draw(string);
        window->draw(bob);
    };

};

int main()
{
    sf::Clock time;
    
    float t = 0;
    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "testing");
    window.setFramerateLimit(60);

    window.setPosition(sf::Vector2i(400, 400));

    pendulum p1(10, 100);
    pendulum p2(15, 200);
    while (window.isOpen())
    {
        deltatime = time.restart().asSeconds();
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            } else if (const auto *keyPressed =
                           event->getIf<sf::Event::KeyPressed>()) {
              if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
            }
        }
        t+=1;
        window.clear(sf::Color(28, 28, 28));
        p1.update(t, deltatime);
        p1.draw(&window);
        p2.update(t, deltatime);
        p2.draw(&window);
        window.display();
    }
}