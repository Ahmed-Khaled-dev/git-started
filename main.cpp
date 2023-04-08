#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 500), "GIT Started");
    std:: string user_input;
    sf :: Font font;
    font.loadFromFile("font/Roboto-Black.ttf");
    sf::Text text("", font);
    sf :: Clock clock; //for cursor
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
         else if (event.type == sf::Event::TextEntered) {  //take input from user
                if (std::isprint(event.text.unicode))      //filter out symbols (only characters in ascii code enters)
                    user_input+= event.text.unicode;
            }
            else if (event.type == sf::Event::KeyPressed) {    //if user wants to erase what he wrote
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!user_input.empty())
                        user_input.pop_back();             //pop it from the string
                }
                if (event.key.code == sf::Keyboard::Return) {  //user clicks enter (will be modified into appearing separately)
                        user_input += '\n';
                }
            }
        }static sf::Time text_effect_time; 
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= sf::seconds(0.5f)) //cursor time to appear
        {
            show_cursor = !show_cursor;
            text_effect_time = sf::Time::Zero;
        }

        text.setString(user_input + (show_cursor ? '|' : ' '));
        text.setPosition(0,450);
        window.clear();
        window.draw(text);
        window.display();
    }

    return 0;
}