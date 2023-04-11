#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const int window_width = 1920;
const int window_height = 1080;


//structs
struct declaration //for dialogue box
{
    Font font;
    Texture texture; 
    Sprite sprite;
    Text dialogueTitle;
}dialogue_box;

struct properties  //for dialogue text
{
    String font_type = "fonts/Roboto-Black.ttf";
    Color text_color = Color::Blue;
    double text_size = 35;
    double text_speed = 0.08f;
    String dialogue_script = "This is our game\ngit-started\nwelcome boo!";
} dialogue_properties;

//functions
void drawDialogue(RenderWindow& window,string title, string imagePath, string font_type, declaration& dialogue_box,RectangleShape& dialogueBox);
void printDialogueText(Time& dialogue_text_time, Text& dialogue_text_text, Clock& clock, Font& dialogue_text_font);


int main()
{
    RenderWindow window(VideoMode(window_width, window_height), "Git Started!");
    string title = "Title";
    string image_path = "man_photo\\man.png";
    string font_type= "font_type\\Roboto-Black.ttf";
    RectangleShape dialogueBox(Vector2f(750,300));
    Event event;
    Clock clock;
    Time dialogue_text_time; //...default value=0
    Font dialogue_text_font;
    Text dialogue_text_text;

    //Game loop
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        drawDialogue(window,title, image_path,font_type, dialogue_box,dialogueBox);
        printDialogueText(dialogue_text_time, dialogue_text_text, clock,dialogue_text_font);
        window.clear(Color::White);
        window.draw(dialogueBox);
        window.draw(dialogue_box.dialogueTitle);
        window.draw(dialogue_box.sprite);
        window.draw(dialogue_text_text);
        window.display();
    }
    return 0;
}

void drawDialogue(RenderWindow& window, string title, string imagePath, string font_type, declaration& dialogue_box,RectangleShape& dialogueBox) 
{
    
    dialogue_box.font.loadFromFile(font_type);
    dialogue_box.texture.loadFromFile(imagePath);

    //dialogue box
    dialogueBox.setFillColor(Color::White);
    dialogueBox.setOutlineThickness(5);
    dialogueBox.setOutlineColor(Color::Black);
    dialogueBox.setPosition((window.getSize().x - dialogueBox.getSize().x) / 2, 800);
    
    //sprite
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(450, 750);

    //title
    dialogue_box.dialogueTitle.setString(title);
    dialogue_box.dialogueTitle.setFont(dialogue_box.font);
    dialogue_box.dialogueTitle.setFillColor(Color::Black); //...controls text color
    dialogue_box.dialogueTitle.setCharacterSize(38);    //...controls text size
    dialogue_box.dialogueTitle.setPosition(700, 820);
}

void printDialogueText(Time& dialogue_text_time, Text& dialogue_text_text, Clock& clock, Font& dialogue_text_font)
{
        dialogue_text_time += clock.restart();
        dialogue_text_font.loadFromFile(dialogue_properties.font_type);
        dialogue_text_text.setFont(dialogue_text_font);
        dialogue_text_text.setFillColor(dialogue_properties.text_color); //...controls text color
        dialogue_text_text.setCharacterSize(dialogue_properties.text_size);    //...controls text size
        dialogue_text_text.setPosition(750, 900);
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
