#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
using namespace std;
using namespace sf;

struct properties  //...with default values
{
    String font_type = "fonts/Roboto-Black.ttf";
    Color text_color = Color::Blue;
    double text_size = 35;
    double text_speed = 0.08f;
    String dialogue_script = "This is our game\ngit-started\nwelcome boo!";
} dialogue_properties;

void printDialogueText(Time& dialogue_text_time, Text& dialogue_text_text, Clock& clock, Font& dialogue_text_font);

int main()
{
    RenderWindow window({ 1920, 1080 }, "dialogue-text-function"); 
    Event e;
    Clock clock;
    Time dialogue_text_time; //...default value=0
    Font dialogue_text_font;
    Text dialogue_text_text;
    while (window.isOpen())
    {
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }
        printDialogueText(dialogue_text_time, dialogue_text_text, clock,dialogue_text_font);
        window.clear(Color::White);
        window.draw(dialogue_text_text);
        window.display();
    }
    return 0;
}

void printDialogueText(Time& dialogue_text_time, Text& dialogue_text_text, Clock& clock, Font& dialogue_text_font)
{
        dialogue_text_time += clock.restart();
        dialogue_text_font.loadFromFile(dialogue_properties.font_type);
        dialogue_text_text.setFont(dialogue_text_font);
        dialogue_text_text.setFillColor(dialogue_properties.text_color); //...controls text color
        dialogue_text_text.setCharacterSize(dialogue_properties.text_size);    //...controls text size
        dialogue_text_text.setPosition(820, 450);
        while (dialogue_text_time >= seconds(dialogue_properties.text_speed))  //...change speed
        {
            dialogue_text_time -= seconds(dialogue_properties.text_speed);  //...change speed
            dialogue_properties.dialogue_script;
            if (dialogue_properties.dialogue_script.getSize() > 0)
            {
                dialogue_text_text.setString(dialogue_text_text.getString() + dialogue_properties.dialogue_script[0]); //start from index zero
                dialogue_properties.dialogue_script = dialogue_properties.dialogue_script.toAnsiString().substr(1);  //deletes index zero and re-indexes
            }
        }   
}