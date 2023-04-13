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
void ShowCliCursor(Clock &clock, bool & show_cursor,Time &text_effect_time);
void SetCliTexts(Text &text, Text &text_cli_final,string &user_input ,string final_input ,bool &show_cursor);
int main()
{
    string user_cli_input,final_cli_input;
    Font cli_font;
    cli_font.loadFromFile("resources/fonts/Roboto-Black.ttf");
    Text cli_text("", cli_font);
    Text text_cli_final("", cli_font);
    Event event;
    Time text_effect_time; 
    bool show_cursor;
    Clock clock; //for cursor
      Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);/* 1-path of the music is written as a string 
    2- mp3 require licence (i tried to play mp3 files alot of time and it failed and found out that it require some soet of licence 
    but you can change the file type using Audacity)
    * 3-i made it to accept the music as an argument to be able to view it inside the function  */

    const int window_width = 1000;
    const int window_height = 800;
    const string window_name = "git started";
    RenderWindow window(VideoMode(window_width, window_height), window_name);
  

    
    CircleShape diamond(100, 4);//deafault number of points is 30 (the circle) 2x <------------
    shapesProperities(diamond, Color::Magenta, Color::Green, 500 , 500, 0);

    CircleShape circle1(50,8);//deafault number of points is 30 (the circle) 2x <------------
    shapesProperities(circle1, Color::Red, Color::Green, 700, 500, 15);

    CircleShape circle2(50,8);// (if you want it a normal circle --> CircleShape circle2(50);) 2x <-----------
    shapesProperities(circle2, Color::Blue, Color::Green, 300, 500, 15);

    Font font;
    if (!font.loadFromFile("resources/fonts/arial.TTF")) {
         cout << "Error has happened while loading the font" << endl;
    }

    Text text1("Hello", font, 35);//a way to 1 - text.setFont(); 2 - text.setString(); 3 - text.setCharacterSize(); in one line  
    textProperities(diamond, text1, Color::Black);

    Text text2("+vol", font, 35);
    textProperities(circle1, text2, Color::Black);

    Text text3("-vol", font, 35);
    textProperities(circle2, text3, Color::Black);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
            if (event.type == Event::TextEntered) {  //take input from user
                if (isprint(event.text.unicode))      //filter out symbols (only characters in ascii code enters)
                    user_cli_input+= event.text.unicode;
            }
            if (event.type == Event::KeyPressed) {    //if user wants to erase what he wrote
                if (event.key.code == Keyboard::BackSpace) {
                    if (!user_cli_input.empty())
                        user_cli_input.pop_back();             //pop it from the string
                }
                if (event.key.code == Keyboard::Return) {  //user clicks enter and the text will be transfered at the top of the screen
                        final_cli_input += ( user_cli_input + "\n") ;
                        user_cli_input.clear();
                }
            }
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
        
        
        ShowCliCursor(clock, show_cursor, text_effect_time);
        SetCliTexts(cli_text,text_cli_final,user_cli_input,final_cli_input,show_cursor);
        window.clear();
        window.draw(cli_text);
        window.draw(text_cli_final);
        window.draw(diamond);
        window.draw(circle1);
        window.draw(circle2);
        window.draw(text1);
        window.draw(text2);
        window.draw(text3);
        window.display();
    }
  
    
}

void ShowCliCursor(Clock &clock, bool & show_cursor,Time &text_effect_time){
     text_effect_time += clock.restart();

        if (text_effect_time >= seconds(0.5f)) //cursor time to appear
        {
            show_cursor = !show_cursor;
            text_effect_time = Time::Zero;
        }
   
}
void SetCliTexts(Text &cli_text, Text &text_cli_final,string &user_input ,string final_input ,bool &show_cursor){
        cli_text.setString(user_input + (show_cursor ? '|' : ' ')); //shape of cursor
        cli_text.setPosition(0,200);
        text_cli_final.setString(final_input);
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