/**
 * Calculate pounds of a circle. sf::CircleShape
 * x,y          x+2r,y
 * x,y+2r       x+2r,y+2r
 *
 * A rectangle would be essentially the same. sf::RectangleShape?
 *
 * circle.setFillColor(sf::Color(r, g, b))
 *
 * Rect N X Y SX SY R G B W H
 * Circ N X Y SX SY R G B Radius
 */
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
// #include <fstream>
#include <iostream>
#include <memory>

class RenderShape {
  std::vector<std::shared_ptr<sf::Shape>> _shapes;
  std::vector<sf::Text> _text;

public:
  RenderShape() {}

  RenderShape(std::vector<std::shared_ptr<sf::Shape>> shapes,
              std::vector<sf::Text> text)
      : _shapes(shapes), _text(text) {}

  void addCircleShape(float radius) {
    _shapes.push_back(std::make_shared<sf::CircleShape>(radius));
  }

  void addRectangleShape(float width, float height) {
    _shapes.push_back(
        std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height)));
  }

  // void readFromFile(std::string &fileName) { std::ifstream fin(fileName); }

  // set shape
  // get shape
  // set text
  // get text
};

float moveSpeedX = 3.0f;
float moveSpeedY = 3.0f;

void reboundObj(sf::CircleShape entity, sf::Vector2u windowSize) {
  if ((entity.getPosition().x + entity.getLocalBounds().width) > windowSize.x ||
      entity.getPosition().x < 0.0f) {
    moveSpeedX *= -1.0f;
  }
  if ((entity.getPosition().y + entity.getLocalBounds().width) > windowSize.y ||
      entity.getPosition().y < 0.0f) {
    moveSpeedY *= -1.0f;
  }
}

int main(int argc, char *argv[]) {
  const int height = 500;
  const int width = 500;
  sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
  window.setFramerateLimit(60);

  sf::CircleShape entity = sf::CircleShape(50);
  entity.setFillColor(sf::Color(0, 255, 255));

  while (window.isOpen()) {
    // entity.move(1.0f, 1.0f);

    sf::Event event;
    // Poll event returns true if event is pending.
    while (window.pollEvent(event)) {

      // Handle our event.
      switch (event.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        std::cout << "Key Pressed" << std::endl;
        break;
      default:
        break;
      }
    }

    entity.setPosition(entity.getPosition().x + moveSpeedX,
                       entity.getPosition().y + moveSpeedY);

    reboundObj(entity, window.getSize());

    // Clear screen after each frame.
    window.clear();
    // Draw shapes.
    window.draw(entity);
    // End current frame.
    window.display();
  }

  return 0;
}
