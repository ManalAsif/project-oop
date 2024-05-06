#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Simple GUI Example");

    // Create a button
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Blue);
    button.setPosition(300, 250);

    // Create button text
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return 1;
    }

    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("Click Me!");
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition(340, 260);

    // Main loop
    while (window.isOpen()) {
        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if the button is clicked
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    sf::Vector2f buttonPos = button.getPosition();
                    sf::Vector2f buttonSize = button.getSize();
                    if (mousePos.x >= buttonPos.x && mousePos.x <= buttonPos.x + buttonSize.x &&
                        mousePos.y >= buttonPos.y && mousePos.y <= buttonPos.y + buttonSize.y) {
                        std::cout << "Button clicked!" << std::endl;
                    }
                }
            }
        }

        // Clear the window
        window.clear(sf::Color::White);

        // Draw button and text
        window.draw(button);
        window.draw(buttonText);

        // Display the window
        window.display();
    }

    return 0;
}
