#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int main()
{
    RenderWindow window({800, 300}, "dialogue-text-function");
    Font my_font;
    my_font.loadFromFile("fonts/Roboto-Black.ttf");
    Text my_text;
    my_text.setFont(my_font);
    my_text.setFillColor(Color::Blue); //...controls text color
    my_text.setCharacterSize(35);    //...controls text size
    my_text.setPosition(270,90);
    Clock clock;
    Time time;  //...=0
    String arr = "This is our game\ngit-started\nwelcome boo!"; //...add script
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type ==Event::Closed)
                window.close();
        }
        time += clock.restart(); 
        while (time >=seconds(0.08f))
        {
            time -=seconds(0.08f);
            if (arr.getSize() > 0)
            {
                my_text.setString(my_text.getString() + arr[0]); 
                arr = arr.toAnsiString().substr(1);
            }
        }
        window.clear(Color::White);
        window.draw(my_text);
        window.display();

    }
    return 0;
}