#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "GIT Started");
    std:: string user_input;
      //user text
    sf :: Font font;
    font.loadFromFile("font/Roboto-Black.ttf");
    sf::Text text("", font);
    sf :: Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
         else if (event.type == sf::Event::TextEntered) {
                if (std::isprint(event.text.unicode))
                    user_input+= event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!user_input.empty())
                        user_input.pop_back();
                }
                if (event.key.code == sf::Keyboard::Return) {
                        user_input += '\n';
                }
            }
        }
        text.setString(user_input);
        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}