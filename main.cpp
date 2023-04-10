#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

void playMusicFromFile(string file_path, Music& music);
void updateDiamondText(CircleShape& diamond, Text& text, string new_text);
void changeCircleColor(CircleShape& circle, Color color);
void shapesProperities(CircleShape& circle, Color fillcolor, Color outlinecolor, float x_position, float y_position, float outlinethickness);
void textProperities(CircleShape& circle ,Text& text,Color color);

int main() {

    Music music;

    playMusicFromFile("resources/lepo.wav", music);/* 1-path of the music is written as a string 
    2- mp3 require licence (i tried to play mp3 files alot of time and it failed and found out that it require some soet of licence 
    but you can change the file type using Audacity)
    * 3-i made it to accept the music as an argument to be able to view it inside the function  */

    const int window_width = 1000;
    const int window_height = 1000;
    const string window_name = "git started";
    RenderWindow window(VideoMode(window_width, window_height), window_name);

    CircleShape diamond(100, 4);//deafault number of points is 30 (the circle) 2x <------------
    shapesProperities(diamond, Color::Magenta, Color::Green, 500 , 500, 0);

    CircleShape circle1(50,8);//deafault number of points is 30 (the circle) 2x <------------
    shapesProperities(circle1, Color::Red, Color::Green, 700, 500, 15);

    CircleShape circle2(50,8);// (if you want it a normal circle --> CircleShape circle2(50);) 2x <-----------
    shapesProperities(circle2, Color::Blue, Color::Green, 300, 500, 15);

    Font font;
    if (!font.loadFromFile("resources/arial.TTF")) {
         cout << "Error has happened while loading the font" << endl;
    }

    Text text1("Hello", font, 35);//a way to 1 - text.setFont(); 2 - text.setString(); 3 - text.setCharacterSize(); in one line  
    textProperities(diamond, text1, Color::Black);

    Text text2("+vol", font, 35);
    textProperities(circle1, text2, Color::Black);

    Text text3("-vol", font, 35);
    textProperities(circle2, text3, Color::Black);

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (diamond.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    if (music.getStatus() == SoundSource::Status::Playing) {
                        music.pause();   //if music is being played --> pause it
                        updateDiamondText(diamond, text1, "Paused");
                    }
                    else if (music.getStatus() == SoundSource::Status::Paused) {
                        music.play();
                        updateDiamondText(diamond, text1, "Playing");
                    }
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (circle1.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    music.setVolume(music.getVolume() + 10);//new volume = current volume+10
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                if (circle2.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    music.setVolume(music.getVolume() - 10);
                }
                
            }
            if (event.type == Event::MouseMoved) {
                if (diamond.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    changeCircleColor(diamond, Color::Yellow); //when you hover on the rectangle a function changes its color
                }
                else {
                    changeCircleColor(diamond, Color::Magenta);

                }
            }
            if (event.type == Event::MouseMoved) {
                if (circle1.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    changeCircleColor(circle1, Color::Cyan);
                }
                else {
                    changeCircleColor(circle1, Color::Red);

                }
            }
            if (event.type == Event::MouseMoved) {
                if (circle2.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    changeCircleColor(circle2, Color::Cyan);
                }
                else {
                    changeCircleColor(circle2, Color::Blue);

                }
            }
        }
        window.clear();
        window.draw(diamond);
        window.draw(circle1);
        window.draw(circle2);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.display();
    }

    return 0;
}
void playMusicFromFile(const string file_path, Music& music) {

    if (!music.openFromFile(file_path)) {
        cout << "error";
    }
    music.setLoop(true); // loops the music
    music.play();
}
void updateDiamondText(CircleShape& diamond, Text& text, string new_text) {

    text.setString(new_text);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    text.setPosition(diamond.getPosition());
}
void changeCircleColor(CircleShape& circle, Color color) {
    circle.setFillColor(color);
}
void shapesProperities(CircleShape& circle, Color fillcolor, Color outlinecolor, float x_position, float y_position, float outlinethickness )
{
    circle.setFillColor(fillcolor);
    circle.setOutlineColor(outlinecolor); //creates an outline with color ( if you want to make it an inline reverse the outlinethickness 15-->(-15)) 
    circle.setOutlineThickness(outlinethickness);     // defines the thickness of that outline
    circle.setOrigin(circle.getRadius(), circle.getRadius()); //makes the origin of the circle at its center
    circle.setPosition(x_position, y_position); 
}
 void textProperities(CircleShape& circle, Text& text, Color color) {

     text.setFillColor(Color::Black);
     text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
     //making the center of the text at its center
     text.setPosition(circle.getPosition()); //assigning the text with the center of the circle
}