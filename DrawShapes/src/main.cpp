// TODO: Figure out a way to utalise our shape specifications.

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>

class RenderShape {
  std::vector<sf::Shape *> _shapes;
  std::vector<sf::Text *> _text;

public:
  RenderShape() {}

  RenderShape(std::vector<sf::Shape *> shapes, std::vector<sf::Text *> text)
      : _shapes(shapes), _text(text) {}

  void addCircleShape(float radius) {
    sf::CircleShape *shape = new sf::CircleShape(radius);
    _shapes.push_back(shape);
  }

  void addRectangleShape(float width, float height) {
    sf::RectangleShape *shape =
        new sf::RectangleShape(sf::Vector2f(width, height));
    _shapes.push_back(shape);
  }

  std::vector<sf::Shape *> getShapes() { return _shapes; }

  /*
   * Read from a file our window, font and shape specifications.
   *
   * Rect N X Y SX SY R G B W H
   * Circ N X Y SX SY R G B Radius
   *
   */
  void readFromFile(std::string &fileName) {
    std::ifstream fin(fileName);
    std::string temp;
    // Window variables.
    int windowX;
    int windowY;
    // Font variables.
    std::string font;
    int fontSize;
    int fontR;
    int fontG;
    int fontB;
    // Shape variables.
    std::string shapeText;
    int posX;
    int posY;
    float speedX;
    float speedY;
    int shapeR;
    int shapeG;
    int shapeB;
    int width; // Radius for cirlces.
    int height;

    fin >> temp >> windowY >> windowX;
    fin >> temp >> fontSize >> fontR >> fontG >> fontB;

    while (fin >> temp) {
      fin >> shapeText >> posX >> posY >> speedX >> speedY >> shapeR >>
          shapeG >> shapeB >> width;
      if (temp == "Rectangle") {
        fin >> height;
        addRectangleShape(width, height);
      } else {
        addCircleShape(width);
      }
    }
  }
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
