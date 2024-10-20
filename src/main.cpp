#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Window.hpp>
#define _USE_MATH_DEFINES
#include <cmath>

constexpr float RAD2DEG = (180 / M_PI);


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");


    sf::View camera(sf::FloatRect(0.0f, 0.0f, 800.0f, 600.0f));
    window.setView(camera);

    sf::Font liberationsans;
    if (!liberationsans.loadFromFile("./assets/fonts/LiberationSans.ttf")) {
        // font not loaded
    }

    sf::Text text;
    text.setFont(liberationsans);
    text.setString("Hello, world!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setOrigin(sf::Vector2f(0.0f, 0.0f));
    text.setPosition(sf::Vector2f({window.getSize().x * 0.5f, window.getSize().y * 0.5f }));


    sf::Texture texture;
    if(!texture.loadFromFile("assets/images/ship.png")) {
        // image not loaded
    }
    texture.setSmooth(true);



    // shader stuff
    sf::RectangleShape background_shape(sf::Vector2f(100000.0f, 10000.0f));
    sf::Shader background;
    

    if(!background.loadFromFile("assets/shaders/background.frag", sf::Shader::Fragment)) {
        // shader not loaded
    }








    sf::Sprite ship;
    ship.setTexture(texture);
    ship.setOrigin(sf::Vector2f(32.0f, 32.0f));
    ship.setPosition(1000.0f, 1000.0f);
    sf::Vector2f velocity;
    sf::Clock clock;
    sf::Clock uTime;
    const float speed = 25.0f;
    window.setMouseCursorGrabbed(true);
    window.setMouseCursorVisible(true);

    window.setFramerateLimit(60);
    while(window.isOpen()) {

        float dt = clock.restart().asSeconds();
        
        sf::Vector2f mouse_coords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    sf::Vector2f diff = ship.getPosition() - mouse_coords;

                    float angle = std::atan2(diff.y, diff.x) * RAD2DEG;
                    ship.setRotation(angle);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            velocity -= sf::Vector2f(0, 1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            velocity += sf::Vector2f(0.0f, 1.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity += sf::Vector2f(1.0f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity -= sf::Vector2f(1.0f, 0.0f);
        }

        ship.move( speed * velocity * dt);
        
        camera.setCenter(ship.getPosition());
        window.setView(camera);
 
        sf::Event event;
        while(window.pollEvent(event)) {

            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                    
            }
        }

        window.clear(sf::Color::Black);
        background.setUniform("u_resolution", background_shape.getSize());
        background.setUniform("u_time", uTime.getElapsedTime().asSeconds());
        window.draw(background_shape, &background);
        window.draw(ship);
        window.draw(text);


        window.display();
        
    }
    return 0;
}