#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;
void cli_cursor(Clock &clock, bool & show_cursor,Time &text_effect_time){
     text_effect_time += clock.restart();

        if (text_effect_time >= seconds(0.5f)) //cursor time to appear
        {
            show_cursor = !show_cursor;
            text_effect_time = Time::Zero;
        }
   
}
void cli_text(Text &text, Text &text_cli_final,string &user_input ,string final_input ,bool &show_cursor){
        text.setString(user_input + (show_cursor ? '|' : ' ')); //shape of cursor
        text.setPosition(0,200);
        text_cli_final.setString(final_input);
}
int main()
{
    const int X=1000,Y=500;
    const string title ="GIT Started" ;
    RenderWindow window(VideoMode(X, Y) , title);
    string user_input,final_input;
    Font font_user;
    font_user.loadFromFile("font/Roboto-Black.ttf");
    Text text("", font_user);
    Text text_cli_final("", font_user);
    Event event;
    Time text_effect_time; 
    bool show_cursor;
    Clock clock; //for cursor
 
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::TextEntered) {  //take input from user
                if (isprint(event.text.unicode))      //filter out symbols (only characters in ascii code enters)
                    user_input+= event.text.unicode;
            }
            if (event.type == Event::KeyPressed) {    //if user wants to erase what he wrote
                if (event.key.code == Keyboard::BackSpace) {
                    if (!user_input.empty())
                        user_input.pop_back();             //pop it from the string
                }
                if (event.key.code == Keyboard::Return) {  //user clicks enter and the text will be transfered at the top of the screen
                        final_input += ( user_input + "\n") ;
                        user_input.clear();
                }
            }
        } 
       
        cli_cursor(clock, show_cursor, text_effect_time);
        cli_text(text,text_cli_final,user_input,final_input,show_cursor);
        window.clear();
        window.draw(text);
        window.draw(text_cli_final);
        window.display();
    }

    return 0;
}