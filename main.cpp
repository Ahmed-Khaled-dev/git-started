#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
void txt (RenderWindow& window, string s)
{
    Clock clock;
    Time time; //...=0
    Font my_font;
    my_font.loadFromFile("fonts/Roboto-Black.ttf");
    Text my_text;
    my_text.setFont(my_font);
    my_text.setFillColor(Color::Blue); //...controls text color
    my_text.setCharacterSize(35);    //...controls text size
    my_text.setPosition(270,90);
    String script = "This is our game\ngit-started\nwelcome boo!"; //...add script
    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type ==Event::Closed)
                window.close();
        }
        time += clock.restart();
        while (time >=seconds(0.08f))  //...change speed
        {
            time -=seconds(0.08f);  //...change speed
            if (script.getSize() > 0)
            {
                my_text.setString(my_text.getString() + script[0]); //start from index zero
                script = script.toAnsiString().substr(1);  //deletes index zero and re-indexes
            }
        }
        window.clear(Color::White);
        window.draw(my_text);
        window.display();
    } 
}
int main()
{
    RenderWindow window({800, 300}, "dialogue-text-function");
    string script;
    txt(window,script);
    return 0;
}