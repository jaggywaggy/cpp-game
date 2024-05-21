// TODO: Pass text by reference.

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

// Class to wrap an sf shape with additional information.
class ShapeObjectWrapper {
 private:
  sf::Shape *_shape;
  std::string _text;
  float _speedX, _speedY;
  int _type;

 public:
  ShapeObjectWrapper() {}

  ShapeObjectWrapper(sf::Shape *shape, std::string text, float speedX,
                     float speedY, int type)
      : _shape(shape),
        _text(text),
        _speedX(speedX),
        _speedY(speedY),
        _type(type) {}

  ~ShapeObjectWrapper() { delete _shape; }

  sf::Shape *getShape() { return _shape; }

  float getSpeedX() { return _speedX; }
  void setSpeedX(float speedX) { _speedX = speedX; }

  float getSpeedY() { return _speedY; }
  void setSpeedY(float speedY) { _speedY = speedY; }

  std::string getText() { return _text; }

  int getType() { return _type; }
};

// Class to construct our shapes.
class ShapeController {
 private:
  std::vector<ShapeObjectWrapper *> _shapes;
  int _windowX, _windowY, _fontSize, _fontR, _fontG, _fontB;
  std::string _font;

 public:
  ShapeController() {}

  ShapeController(std::vector<ShapeObjectWrapper *> shapes) : _shapes(shapes) {}

  ~ShapeController() {
    for (auto ptr : _shapes) {
      delete ptr;
    }
  }

  void addCircleShape(float radius, std::string text, int posX, int posY,
                      float speedX, float speedY, int shapeR, int shapeG,
                      int shapeB) {
    // Set our shape specifications.
    sf::CircleShape *shape = new sf::CircleShape(radius);
    shape->setPosition(sf::Vector2f(posX, posY));
    shape->setFillColor(sf::Color(shapeR, shapeG, shapeB));
    // Wrap our shape.
    ShapeObjectWrapper *shapeObj =
        new ShapeObjectWrapper(shape, text, speedX, speedY, 0);
    _shapes.push_back(shapeObj);
  }

  void addRectangleShape(float width, float height, std::string text, int posX,
                         int posY, float speedX, float speedY, int shapeR,
                         int shapeG, int shapeB) {
    // Set our shape specifications.
    sf::RectangleShape *shape =
        new sf::RectangleShape(sf::Vector2f(width, height));
    shape->setPosition(sf::Vector2f(posX, posY));
    shape->setFillColor(sf::Color(shapeR, shapeG, shapeB));

    // Wrap our shape.
    ShapeObjectWrapper *shapeObj =
        new ShapeObjectWrapper(shape, text, speedX, speedY, 1);
    _shapes.push_back(shapeObj);
  }

  std::vector<ShapeObjectWrapper *> getShapes() { return _shapes; }

  /*
   * Read from a file our window, font and shape specifications.
   *
   * Rect N X Y SX SY R G B W H
   * Circ N X Y SX SY R G B Radius
   *
   */
  void readFromFile(const std::string &fileName) {
    std::ifstream fin(fileName);
    std::string temp, shapeText, shapeType;
    int posX, posY;
    float speedX, speedY;
    int shapeR, shapeG, shapeB;
    int width;  // Circle radius. Rect height.
    int height;

    // Read items from file.
    fin >> temp >> _windowY >> _windowX;
    fin >> temp >> _font >> _fontSize >> _fontR >> _fontG >> _fontB;
    while (fin >> shapeType) {
      fin >> shapeText >> posX >> posY >> speedX >> speedY >> shapeR >>
          shapeG >> shapeB >> width >> height;

      std::cout << "Loading Shape: " << shapeType << ", Text: " << shapeText
                << ", Position: (" << posX << ", " << posY << "), Speed: ("
                << speedX << ", " << speedY << "), Color: (" << shapeR << ", "
                << shapeG << ", " << shapeB << "), Size: " << width << "x"
                << height << std::endl;

      // Create shape objects.
      if (shapeType == "Rectangle") {
        addRectangleShape(width, height, shapeText, posX, posY, speedX, speedY,
                          shapeR, shapeG, shapeB);
      } else {
        addCircleShape(width, shapeText, posX, posY, speedX, speedY, shapeR,
                       shapeG, shapeB);
      }
      fin.clear();
    }
  }

  int getWindowX() { return _windowX; }
  int getWindowY() { return _windowY; }
  int getFontSize() { return _fontSize; }
  int getFontR() { return _fontR; }
  int getFontG() { return _fontG; }
  int getFontB() { return _fontB; }
  std::string &getFont() { return _font; }
};

const std::string fileName = "shape-config.txt";

int main(int argc, char *argv[]) {
  ShapeController shapeController = ShapeController();
  shapeController.readFromFile(fileName);

  // Create our shape objects.
  std::vector<ShapeObjectWrapper *> shapes = shapeController.getShapes();

  const int height = shapeController.getWindowY();
  const int width = shapeController.getWindowX();

  std::cout << "Launching session with a height of: " << height
            << " and a width of: " << width << std::endl;

  sf::RenderWindow window(sf::VideoMode(width, height), "My Window");
  // window.setFramerateLimit(60);

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
    // Clear screen after each frame.
    window.clear();

    // Retrieve our shapes.
    for (auto &shape : shapes) {
      sf::RectangleShape rectShape;
      sf::CircleShape circleShape;
      auto &realShape = *shape->getShape();
      if (shape->getType() == 0) {
        circleShape.setRadius(
            static_cast<sf::CircleShape *>(shape->getShape())->getRadius());
        circleShape.setPosition(
            static_cast<sf::CircleShape *>(shape->getShape())->getPosition());
        circleShape.setFillColor(
            static_cast<sf::CircleShape *>(shape->getShape())->getFillColor());
      } else {
        rectShape.setSize(
            static_cast<sf::RectangleShape *>(shape->getShape())->getSize());
        rectShape.setPosition(
            static_cast<sf::RectangleShape *>(shape->getShape())
                ->getPosition());
        rectShape.setFillColor(
            static_cast<sf::RectangleShape *>(shape->getShape())
                ->getFillColor());
      }

      // Update shape position.
      realShape.setPosition(realShape.getPosition().x + shape->getSpeedX(),
                            realShape.getPosition().y + shape->getSpeedY());

      // Set our font and text.
      sf::Text text;
      sf::Font font;
      font.loadFromFile(shapeController.getFont());
      text.setFont(font);
      text.setString(shape->getText());
      text.setCharacterSize(shapeController.getFontSize());
      text.setFillColor(sf::Color(shapeController.getFontR(),
                                  shapeController.getFontG(),
                                  shapeController.getFontB()));
      // Update text position.
      if (shape->getType() == 0) {
        text.setPosition(circleShape.getPosition().x + circleShape.getRadius() -
                             (text.getLocalBounds().width * 0.5f),
                         circleShape.getPosition().y + circleShape.getRadius() -
                             (text.getLocalBounds().height * 0.5f));
      } else {
        text.setPosition(
            rectShape.getPosition().x + (rectShape.getSize().x * 0.5f) -
                (text.getLocalBounds().width * 0.5f),
            rectShape.getPosition().y + (rectShape.getSize().y * 0.5f) -
                (text.getLocalBounds().height * 0.5f));
      }

      // Check boundries.
      if ((realShape.getPosition().x + realShape.getLocalBounds().width) >
              window.getSize().x ||
          realShape.getPosition().x < 0.0f) {
        shape->setSpeedX(shape->getSpeedX() * -1.0f);
      }
      if ((realShape.getPosition().y + realShape.getLocalBounds().width) >
              window.getSize().y ||
          realShape.getPosition().y < 0.0f) {
        shape->setSpeedY(shape->getSpeedY() * -1.0f);
      }

      // Draw.
      window.draw(realShape);
      window.draw(text);
    }

    // End current frame.
    window.display();
  }

  return 0;
}
