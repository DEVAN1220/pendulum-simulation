#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

constexpr int windowWidth = 400;
constexpr int windowHeight = 400;
constexpr int halfWidth = windowWidth / 2;

class pendulum {
  float stringLength;
  sf::CircleShape bob;
  sf::RectangleShape string;

  float angle;
  float angularVelocity{};
  float angularAcceleration{};

public:
  pendulum(const float radius, float s)
      : stringLength((s)), bob(sf::CircleShape(radius)),
        string(sf::RectangleShape{sf::Vector2f(s, 1)}) {
    angle = M_PI / 4;
    bob.setFillColor(sf::Color(0xb8, 0xbb, 0x28));
    string.setFillColor(sf::Color(0xfb, 0x49, 0x34));
    string.move(sf::Vector2f(halfWidth, 0));
    string.rotate(sf::degrees(90.f));

    bob.move(sf::Vector2f(halfWidth - radius, stringLength - radius));
  }

    void update(float deltaTime){

        angularAcceleration = -1 * (15.f/stringLength) * std::sin(angle  );
        angularVelocity += angularAcceleration * deltaTime;
        angle += angularVelocity;

        // std::cout << angularAcceleration << "," << angularVelocity << "," << angle << std::endl;
        string.setRotation(sf::radians((angle) + M_PI/2));

        const sf::Vector2f bp(-1 * std::sin(angle) * stringLength + halfWidth - bob.getRadius(),
                        std::cos(angle) * stringLength - bob.getRadius());

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
    float deltatime = 1.0 / 60;


    auto window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "pendulum simulation");
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
        window.clear(sf::Color(28, 28, 28));
        p1.update(deltatime);
        p1.draw(&window);
        p2.update(deltatime);
        p2.draw(&window);
        window.display();
    }
}
