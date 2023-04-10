#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

const int window_width = 1920;
const int window_height = 1080;
//structs
struct declaration
{
    Font font;
    Texture texture; 
    Sprite sprite;
    Text dialogueTitle;
}dialogue_box;

//functions
void drawDialogue(RenderWindow& window, string title, string imagePath, string font_type, declaration& dialogue_box,RectangleShape& dialogueBox);


int main()
{
    RenderWindow window(VideoMode(window_width, window_height), "SFML Dialogue Box");

    string title = "Title";
    string image_path = "man_photo\\man.png";
    string font_type= "font_type\\Roboto-Black.ttf";
    RectangleShape dialogueBox(Vector2f(750,300));

    drawDialogue(window, title, image_path,font_type, dialogue_box,dialogueBox);
    while (window.isOpen()) 
    {
        Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            
        }

        window.clear(Color::White);
        window.draw(dialogueBox);
        window.draw(dialogue_box.dialogueTitle);
        window.draw(dialogue_box.sprite);
        window.display();
    }
    return 0;
}

void drawDialogue(RenderWindow& window, string title, string imagePath, string font_type, declaration& dialogue_box,RectangleShape& dialogueBox) 
{
    
    dialogue_box.font.loadFromFile(font_type);
    dialogue_box.texture.loadFromFile(imagePath);

    dialogueBox.setFillColor(Color::White);
    dialogueBox.setOutlineThickness(5);
    dialogueBox.setOutlineColor(Color::Black);
    dialogueBox.setPosition((window.getSize().x - dialogueBox.getSize().x) / 2, window.getSize().y - dialogueBox.getSize().y);
    

    
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(450, 750);

    
    dialogue_box.dialogueTitle.setString(title);
    dialogue_box.dialogueTitle.setFont(dialogue_box.font);
    dialogue_box.dialogueTitle.setFillColor(Color::Black); //...controls text color
    dialogue_box.dialogueTitle.setCharacterSize(38);    //...controls text size
    dialogue_box.dialogueTitle.setPosition(700, 800);
}
