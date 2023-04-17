#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
    Color color = {225, 227, 227};
    double size = 35;
    double speed = 0.09f;
    String script = "This is our game\ngit-started\nwelcome boo!";
}dialogue_text;

// Functions definition 
void menuScreen(RenderWindow& window,RectangleShape& start_button,RectangleShape& options_button,RectangleShape& close_button,Font buttons_font);
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box);
void printDialogueText(dialogueText& dialogue_text);
void playMusicFromFile(string file_path, Music& music);
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text);
void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position);
void setButtonTextProperties(RectangleShape& rectangle, Text& text, Color color);
void showCliCursor(Clock& cursor_clock, bool& show_cursor, Time& cli_cursor_time);
void setCliTexts(Text& text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor);

int main()
{
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    string mode=" ";

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Git Started!");
    dialogue_box.font.loadFromFile(dialogue_box.font_type);
    dialogue_box.texture.loadFromFile(dialogue_box.image_path);
    dialogue_text.font.loadFromFile(dialogue_text.font_type);
    Font cli_font;
    cli_font.loadFromFile("resources/fonts/Roboto-Black.ttf");
    string user_cli_input, final_cli_input;
    Text cli_text("", cli_font), cli_text_final("", cli_font);
    Time cli_cursor_time;
    bool show_cursor;
    Clock cursor_clock;
    Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);

    RectangleShape vol_dec_button(Vector2f(150, 50)), vol_status_button(Vector2f(225,50)), vol_inc_button(Vector2f(150, 50));
    setButtonProperties(vol_dec_button, Color::Blue, 100, 50);
    setButtonProperties(vol_status_button, Color::White, 300, 50);
    setButtonProperties(vol_inc_button, Color::Red, 500, 50);

    Font buttons_font;
    if (!buttons_font.loadFromFile("resources/fonts/minecraft_font.ttf")) {
        cout << "Error has happened while loading the font" << endl;
    }

    // A way to 1 - text.setFont(); 2 - text.setString(); 3 - text.setCharacterSize(); in one line  
    Text vol_status_text("Hello", buttons_font , 35), vol_inc_text("+vol", buttons_font , 35);
    Text vol_dec_text("-vol", buttons_font , 35);
    setButtonTextProperties(vol_status_button, vol_status_text, Color::Black);
    setButtonTextProperties(vol_inc_button, vol_inc_text, Color::Black);
    setButtonTextProperties(vol_dec_button, vol_dec_text, Color::Black);

    // Menu Screen buttons & text
    RectangleShape start_button(Vector2f(406,121)),options_button(Vector2f(323,68)),close_button(Vector2f(316,116));
    
    Event event;
    menuScreen(window,start_button,options_button,close_button,buttons_font);
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || mode == "close") 
            {
                window.close();
            }
            // Take input from user
            if (event.type == Event::TextEntered) 
            { 
                // Filter out symbols (only characters in ascii code enters)
                if (isprint(event.text.unicode))     
                    user_cli_input += event.text.unicode;
            }
            // If user wants to erase what he wrote
            if (event.type == Event::KeyPressed) 
            {    
                if (event.key.code == Keyboard::BackSpace) 
                {
                    if (!user_cli_input.empty())
                        user_cli_input.pop_back();
                }
                // User clicks enter and the text will be transfered at the top of the screen
                if (event.key.code == Keyboard::Return) 
                {
                    final_cli_input += (user_cli_input + "\n");
                    user_cli_input.clear();
                }
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
            {
                if (vol_status_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    if (music.getStatus() == SoundSource::Status::Playing) 
                    {
                        music.pause();   
                        updateButtonText(vol_status_button, vol_status_text, "Paused");
                    }
                    else if (music.getStatus() == SoundSource::Status::Paused) 
                    {
                        music.play();
                        updateButtonText(vol_status_button, vol_status_text, "Playing");
                    }
                }
                if (vol_inc_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    music.setVolume(music.getVolume() + 10); //new volume = current volume+10
                }

                if (vol_dec_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    music.setVolume(music.getVolume() - 10);
                }

                if (start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    mode="start";
                }
                if (options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    mode="options";
                }
                if (close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    mode = "close";
                }
            }
            if (event.type == Event::MouseMoved) {
                if (vol_status_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    // When you hover on the rectangle a function changes its color
                    vol_status_button.setFillColor(Color::Yellow); 
                }
                else 
                {
                    vol_status_button.setFillColor(Color::Magenta);
                }
                if (vol_inc_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    vol_inc_button.setFillColor(Color::Cyan);
                }
                else 
                {
                    vol_inc_button.setFillColor(Color::Red);
                }
                if (vol_dec_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    vol_dec_button.setFillColor(Color::Cyan);
                }
                else 
                {
                    vol_dec_button.setFillColor(Color::Blue);

                }
            }
        }
       if(mode =="start")
        {
        drawDialogue(window, dialogue_box);
        printDialogueText(dialogue_text);
        showCliCursor(cursor_clock, show_cursor, cli_cursor_time);
        setCliTexts(cli_text, cli_text_final, user_cli_input, final_cli_input, show_cursor);
        window.clear(Color::Black);
        window.draw(dialogue_box.shape);
        window.draw(dialogue_box.title);
        window.draw(dialogue_box.sprite);
        window.draw(dialogue_text.text);
        window.draw(cli_text);
        window.draw(cli_text_final);
        window.draw(vol_status_button);
        window.draw(vol_inc_button);
        window.draw(vol_dec_button);
        window.draw(vol_status_text);
        window.draw(vol_inc_text);
        window.draw(vol_dec_text);
        window.display();
        }
        else if(mode =="options")
        {
            //write here "options" screen propertiess
        }
    }
}

void menuScreen(RenderWindow& window,RectangleShape& start_button,RectangleShape& options_button,RectangleShape& close_button,Font buttons_font)
{
    window.clear(Color::Black);
    setButtonProperties(start_button, Color::Green, 754, 474);
    setButtonProperties(options_button, Color::Yellow, 801, 653);
    setButtonProperties(close_button, Color::Red, 1561, 138);
    Text start_text("Start", buttons_font , 50), options_text("Options", buttons_font , 40);
    Text close_text("Close", buttons_font , 35);
    setButtonTextProperties(start_button, start_text, Color::Black);
    setButtonTextProperties(options_button, options_text, Color::Black);
    setButtonTextProperties(close_button, close_text, Color::Black);
    window.draw(start_button);
    window.draw(options_button);
    window.draw(close_button);
    window.draw(start_text);
    window.draw(options_text);
    window.draw(close_text);
    window.display();
    
}
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box) 
{
    //Dialogue box
    dialogue_box.shape.setSize(Vector2f(750,300));
    dialogue_box.shape.setFillColor(Color::Black);
    dialogue_box.shape.setOutlineThickness(5);
    dialogue_box.shape.setOutlineColor(Color::White);
    dialogue_box.shape.setPosition((window.getSize().x - dialogue_box.shape.getSize().x) / 2, window.getSize().y - dialogue_box.shape.getSize().y);
    
    //Sprite
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(450, 750);

    //Title
    dialogue_box.title.setString(dialogue_box.title_content);
    dialogue_box.title.setFont(dialogue_box.font);
    dialogue_box.title.setFillColor(Color::White);
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

void showCliCursor(Clock& cursor_clock, bool& show_cursor, Time& cli_cursor_time) {
    cli_cursor_time += cursor_clock.restart();

    // Cursor time to appear
    if (cli_cursor_time >= seconds(0.5f)) 
    {
        show_cursor = !show_cursor;
        cli_cursor_time = Time::Zero;
    }
}

void setCliTexts(Text& cli_text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor) {
    // Shape of cursor
    cli_text.setString(user_cli_input + (show_cursor ? '|' : ' ')); 
    cli_text.setPosition(1500, 950);
    cli_text_final.setString(final_cli_input);
    cli_text_final.setPosition(1500, 500);
}

void playMusicFromFile(const string file_path, Music& music) {
    if (!music.openFromFile(file_path)) {
        cout << "Error playing music";
    }
    // Loops the music
    music.setLoop(true); 
    music.play();
}

void updateButtonText(RectangleShape& rectangle, Text& text, string new_text) {
    text.setString(new_text);
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    text.setPosition(rectangle.getPosition());
}

void setButtonTextProperties(RectangleShape& rectangle, Text& text, Color color) {
    text.setFillColor(Color::Black);
    // Making the center of the text at its center
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    // Assigning the text with the center of the button
    text.setPosition(rectangle.getPosition()); 
}

void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position){
    rectangle.setFillColor(fillcolor);
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setPosition(x_position, y_position);
}
