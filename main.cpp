#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;
void playMusicFromFile(string file_path, Music& music);
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text);
void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position);
void setTextProperties(RectangleShape& rectangle, Text& text, Color color);
void ShowCliCursor(Clock& clock, bool& show_cursor, Time& text_effect_time);
void SetCliTexts(Text& text, Text& text_cli_final, string& user_input, string final_input, bool& show_cursor);
int main()
{
    string user_cli_input, final_cli_input;
    Font cli_font;
    cli_font.loadFromFile("resources/fonts/Roboto-Black.ttf");
    Text cli_text("", cli_font);
    Text text_cli_final("", cli_font);
    Event event;
    Time text_effect_time;
    bool show_cursor;
    Clock clock; //for cursor
    Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);
    
    const int window_width = 1000;
    const int window_height = 800;
    const string window_name = "git started";
    RenderWindow window(VideoMode(window_width, window_height), window_name);

    RectangleShape vol_status_button(Vector2f(225,75));
    setButtonProperties(vol_status_button, Color::White , 500,500);

    RectangleShape vol_inc_button(Vector2f(150, 50));
    setButtonProperties(vol_inc_button, Color::Red, 750 , 500);

    RectangleShape vol_dec_button(Vector2f(150, 50));
    setButtonProperties(vol_dec_button, Color::Blue, 250 , 500);

    Font buttons_font;
    if (!buttons_font.loadFromFile("resources/fonts/arial.TTF")) {
        cout << "Error has happened while loading the font" << endl;
    }

    Text vol_status_text("Hello", buttons_font , 35);//a way to 1 - text.setFont(); 2 - text.setString(); 3 - text.setCharacterSize(); in one line  
    setTextProperties(vol_status_button, vol_status_text, Color::Black);

    Text vol_up_text("+vol", buttons_font , 35);
    setTextProperties(vol_inc_button, vol_up_text, Color::Black);

    Text vol_down_text("-vol", buttons_font , 35);
    setTextProperties(vol_dec_button, vol_down_text, Color::Black);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::TextEntered) {  //take input from user
                if (isprint(event.text.unicode))      //filter out symbols (only characters in ascii code enters)
                    user_cli_input += event.text.unicode;
            }
            if (event.type == Event::KeyPressed) {    //if user wants to erase what he wrote
                if (event.key.code == Keyboard::BackSpace) {
                    if (!user_cli_input.empty())
                        user_cli_input.pop_back();             //pop it from the string
                }
                if (event.key.code == Keyboard::Return) {  //user clicks enter and the text will be transfered at the top of the screen
                    final_cli_input += (user_cli_input + "\n");
                    user_cli_input.clear();
                }
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {

                if (vol_status_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    if (music.getStatus() == SoundSource::Status::Playing) {
                        music.pause();   //if music is being played --> pause it
                        updateButtonText(vol_status_button, vol_status_text, "Paused");
                    }
                    else if (music.getStatus() == SoundSource::Status::Paused) {
                        music.play();
                        updateButtonText(vol_status_button, vol_status_text, "Playing");
                    }
                }

                if (vol_inc_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    music.setVolume(music.getVolume() + 10); //new volume = current volume+10
                }

                if (vol_dec_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    music.setVolume(music.getVolume() - 10);
                }

            }
            if (event.type == Event::MouseMoved) {
                if (vol_status_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    vol_status_button.setFillColor(Color::Yellow); //when you hover on the rectangle a function changes its color
                }
                else {
                    vol_status_button.setFillColor(Color::Magenta);

                }
                if (vol_inc_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    vol_inc_button.setFillColor(Color::Cyan);
                }
                else {
                    vol_inc_button.setFillColor(Color::Red);

                }
                if (vol_dec_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) {
                    vol_dec_button.setFillColor(Color::Cyan);
                }
                else {
                    vol_dec_button.setFillColor(Color::Blue);

                }
            }

            ShowCliCursor(clock, show_cursor, text_effect_time);
            SetCliTexts(cli_text, text_cli_final, user_cli_input, final_cli_input, show_cursor);
            window.clear();
            window.draw(cli_text);
            window.draw(text_cli_final);
            window.draw(vol_status_button);
            window.draw(vol_inc_button);
            window.draw(vol_dec_button);
            window.draw(vol_status_text);
            window.draw(vol_up_text);
            window.draw(vol_down_text);
            window.display();
        }
    }
    
}

void ShowCliCursor(Clock& clock, bool& show_cursor, Time& text_effect_time) {
    text_effect_time += clock.restart();

    if (text_effect_time >= seconds(0.5f)) //cursor time to appear
    {
        show_cursor = !show_cursor;
        text_effect_time = Time::Zero;
    }

}
void SetCliTexts(Text& cli_text, Text& text_cli_final, string& user_input, string final_input, bool& show_cursor) {
    cli_text.setString(user_input + (show_cursor ? '|' : ' ')); //shape of cursor
    cli_text.setPosition(0, 200);
    text_cli_final.setString(final_input);
}
void playMusicFromFile(const string file_path, Music& music) {

    if (!music.openFromFile(file_path)) {
        cout << "error";
    }
    music.setLoop(true); // loops the music
    music.play();
}
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text) {

    text.setString(new_text);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    text.setPosition(rectangle.getPosition());
}
void setTextProperties(RectangleShape& rectangle, Text& text, Color color) {

    text.setFillColor(Color::Black);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    //making the center of the text at its center
    text.setPosition(rectangle.getPosition()); //assigning the text with the center of the circle
}
void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position){

    rectangle.setFillColor(fillcolor);
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setPosition(x_position, y_position);
}