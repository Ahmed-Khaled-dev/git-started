#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

// Structs
struct dialogueBox
{
    Font font;
    Texture texture; 
    Sprite sprite;
    Text title;
    string title_content = "Title";
    double title_size = 38;
    string image_path = "resources/sprites/man.png";
    string font_type= "resources/fonts/Roboto-Black.ttf";
    RectangleShape shape;
}dialogue_box;

struct dialogueText
{
    Font font;
    Time time;
    Clock clock;
    Text text;
    String font_type = "resources/fonts/Roboto-Black.ttf";
    Color color = Color::Blue;
    double size = 35;
    double speed = 0.09f;
    String script = "This is our game\ngit-started\nwelcome boo!";
}dialogue_text;

// Functions definition 
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box);
void printDialogueText(dialogueText& dialogue_text);

int main()
{
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Git Started!");
    dialogue_box.font.loadFromFile(dialogue_box.font_type);
    dialogue_box.texture.loadFromFile(dialogue_box.image_path);
    dialogue_text.font.loadFromFile(dialogue_text.font_type);
    Event event;
    
    //Game loop
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        drawDialogue(window, dialogue_box);
        printDialogueText(dialogue_text);
        window.clear(Color::White);
        window.draw(dialogue_box.shape);
        window.draw(dialogue_box.title);
        window.draw(dialogue_box.sprite);
        window.draw(dialogue_text.text);
        window.display();
    }
}

void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box) 
{
    //Dialogue box
    dialogue_box.shape.setSize(Vector2f(750,300));
    dialogue_box.shape.setFillColor(Color::White);
    dialogue_box.shape.setOutlineThickness(5);
    dialogue_box.shape.setOutlineColor(Color::Black);
    dialogue_box.shape.setPosition((window.getSize().x - dialogue_box.shape.getSize().x) / 2, window.getSize().y - dialogue_box.shape.getSize().y);
    
    //Sprite
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(450, 750);

    //Title
    dialogue_box.title.setString(dialogue_box.title_content);
    dialogue_box.title.setFont(dialogue_box.font);
    dialogue_box.title.setFillColor(Color::Black);
    dialogue_box.title.setCharacterSize(dialogue_box.title_size);
    dialogue_box.title.setPosition(700, 800);
}

void printDialogueText(dialogueText& dialogue_text)
{
        dialogue_text.time += dialogue_text.clock.restart();
        dialogue_text.text.setFont(dialogue_text.font);
        dialogue_text.text.setFillColor(dialogue_text.color);
        dialogue_text.text.setCharacterSize(dialogue_text.size);
        dialogue_text.text.setPosition(850, 850);
        while (dialogue_text.time >= seconds(dialogue_text.speed))
        {
            dialogue_text.time -= seconds(dialogue_text.speed);
            dialogue_text.script;
            if (dialogue_text.script.getSize() > 0)
            {
                // Start from index zero
                dialogue_text.text.setString(dialogue_text.text.getString() + dialogue_text.script[0]); 
                // Deletes index zero and re-indexes
                dialogue_text.script = dialogue_text.script.toAnsiString().substr(1);
            }
        }   
}
