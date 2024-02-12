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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

class RenderShape {
  std::vector<std::shared_ptr<sf::Shape>> _shapes;
  std::vector<sf::Text> _text;

public:
  RenderShape() { }

  RenderShape(std::vector<std::shared_ptr<sf::Shape>> shapes, std::vector<sf::Text> text)
    : _shapes(shapes)
    , _text(text)
  {
  }

  void addCircleShape(float radius) {
    _shapes.push_back(std::make_shared<sf::CircleShape>(radius));
  }

  void addRectangleShape(float width, float height) {
    _shapes.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(width, height)));
  }

  void readFromFile(std::string& fileName) {
    std::ifstream fin(fileName);

  }

  // set shape
  // get shape
  // set text
  // get text

};

int main(int argc, char * argv[]) {
  const int height = 1280;
  const int width = 720;
  sf::RenderWindow window(sf::VideoMode(height, width), "My Window");
  window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(60);


  while(window.isOpen()) {

    sf::Event event;
    // Poll event returns true if event is pending.
    while(window.pollEvent(event)) {

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

    // Clear screen after each frame.
    window.clear(sf::Color::Black);

    // End current frame.
    window.display();
  }

  return 0;
}
