#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
int main()
{
    const int X=1000,Y=500;
    const string title ="GIT Started" ;
    RenderWindow window(VideoMode(X, Y) , title);
    string user_input,final_input;
    Font font;
    font.loadFromFile("font/Roboto-Black.ttf");
    Text text("", font);
    Text text_final("", font);
    Clock clock; //for cursor
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
         else if (event.type == Event::TextEntered) {  //take input from user
                if (isprint(event.text.unicode))      //filter out symbols (only characters in ascii code enters)
                    user_input+= event.text.unicode;
            }
            else if (event.type == Event::KeyPressed) {    //if user wants to erase what he wrote
                if (event.key.code == Keyboard::BackSpace) {
                    if (!user_input.empty())
                        user_input.pop_back();             //pop it from the string
                }
                if (event.key.code == Keyboard::Return) {  //user clicks enter and the text will be transfered at the top of the screen
                        final_input += ( user_input + "\n") ;
                        user_input.clear();
                }
            }
        }static Time text_effect_time; 
        static bool show_cursor;

        text_effect_time += clock.restart();

        if (text_effect_time >= seconds(0.5f)) //cursor time to appear
        {
            show_cursor = !show_cursor;
            text_effect_time = Time::Zero;
        }

        text.setString(user_input + (show_cursor ? '|' : ' ')); //shape of cursor
        text.setPosition(0,450);
        text_final.setString(final_input);
        window.clear();
        window.draw(text);
        window.draw(text_final);
        window.display();
    }

    return 0;
}