#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

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
