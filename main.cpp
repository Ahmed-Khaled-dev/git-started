#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

void drawDialogue(RenderWindow& window, string title, string imagePath, string font_type) {
    Font font;
    font.loadFromFile(font_type);

    Texture texture;
    texture.loadFromFile(imagePath);

    RectangleShape dialogueBox(Vector2f(700, 200));
    dialogueBox.setFillColor(Color::White);
    dialogueBox.setOutlineThickness(5);
    dialogueBox.setOutlineColor(Color::Black);
    dialogueBox.setPosition((window.getSize().x - dialogueBox.getSize().x) / 2, window.getSize().y - dialogueBox.getSize().y);
    //setPosition(150, 400)

    Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.7, 0.7);
    sprite.setPosition(50, 550);

    Text dialogueTitle;
    dialogueTitle.setString(title);
    dialogueTitle.setFont(font);
    dialogueTitle.setFillColor(Color::Black); //...controls text color
    dialogueTitle.setCharacterSize(35);    //...controls text size
    dialogueTitle.setPosition(350, 610);

    bool dialogue_open = true;
    while (window.isOpen() && dialogue_open) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Enter) {
                dialogue_open = false;
            }
        }

        window.clear(Color::White);
        window.draw(dialogueBox);
        window.draw(dialogueTitle);
        window.draw(sprite);
        window.display();
    }
}

int main()
{
    RenderWindow window(VideoMode(1000, 800), "SFML Dialog Box");

    string title = "Title";
    string image_path = "C:\\Users\\haneenpc\\Desktop\\SP Project\\new\\git-started\\man\\man.png";
    string font_type= "C:\\Users\\haneenpc\\Desktop\\SP Project\\new\\git-started\\font\\Roboto-Black.ttf";

    drawDialogue(window, title, image_path,font_type);

    return 0;
}
