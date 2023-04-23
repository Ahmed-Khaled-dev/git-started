#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;
const int WINDOW_WIDTH = 1980;
const int WINDOW_HEIGHT = 1080;
string current_screen = "main menu";

RenderWindow window(VideoMode::getDesktopMode(), "Git Started!");
// Structs
struct dialogueBox
{
    Font font;
    Texture texture; 
    Sprite sprite;
    Text title;
    string title_content = "Mentor";
    double title_size = 25;
    string image_path = "resources/sprites/man.png";
    string font_type= "resources/fonts/Roboto-Black.ttf";
    RectangleShape body_shape;
    RectangleShape title_shape;
}dialogue_box;

struct dialogueText
{
    Font font;
    Time time;
    Time continuation_fade_time;
    Clock clock;
    Clock continuation_fade_clock;
    Text script_text;
    Text continuation_text;
    string font_type = "resources/fonts/Roboto-Black.ttf";
    Color color = Color::Black;
    double size = 32;
    double script_speed = 0.09f;
    double continuation_delay = 0.8f;
    String script_content = " ";
    string continuation_content = "Press down to continue...";
    vector <String> new_script  = { "This is our game git-started\nwelcome",
    "we will help you learn git\nand or github","in a fun easy way","so... lets git started!" };
    int current_script_index = 0;
    bool script_ended = 0;
    bool continuation_message_running = 0;
    bool script_part_ended = 0;
}dialogue_text;

struct optionMenu {
    Font font;
    Text text;
    String option_font_type = "resources/fonts/minecraft_font.ttf";
    const int short  size = 60;
};

// Functions declaration
// Functions definition
bool check_string(string&  user_edit_input,string&);
void createCommandShape(RectangleShape &form);
void setEditWindowText(Text & edit_text,string& edit_input,bool&,RectangleShape& rectangle);
void createCliShape(RectangleShape &form);
void createEditWindowShape(RectangleShape &form);
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box);
void printDialogueText(dialogueText& dialogue_text);
void playMusicFromFile(string file_path, Music& music);
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text);
void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position);
void setButtonTextProperties(RectangleShape& rectangle, Text& text, Color color);
void showCursor(Clock& cursor_clock, bool& show_cursor,bool& , Time& cursor_time);
void setCliTexts(Text& text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape&);
void setSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, Sprite& option_menu);
void controlSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, RectangleShape& mouse_cursor, Sound& pop);
void controlOptionsExitButton(Sprite& options_exit_button, RectangleShape& mouse_cursor, Sprite& option_menu);
void controlSfxAndMusicVolume(optionMenu& sfx_text, Music& music, Sound& pop, Sprite slider_bar[], CircleShape contoroller[], Sprite& option_menu, RectangleShape& mouse_cursor);
void showContinuationMessage(dialogueText &dialogue_text);

int main()
{

  
    // Dialogue box
    dialogue_box.font.loadFromFile(dialogue_box.font_type);
    dialogue_box.texture.loadFromFile(dialogue_box.image_path);
    dialogue_text.font.loadFromFile(dialogue_text.font_type);

    // Fonts
    Font buttons_font;
    if (!buttons_font.loadFromFile("resources/fonts/minecraft_font.ttf")) {
        cout << "Error has happened while loading the buttons font" << endl;
    }
    Font game_title_font;
    if (!game_title_font.loadFromFile("resources/fonts/Glitch inside.otf")) {
        cout << "Error has happened while loading the game title font" << endl;
    }
    Font cli_font;
    cli_font.loadFromFile("resources/fonts/arial.ttf");
    if (!cli_font.loadFromFile("resources/fonts/Roboto-Black.ttf")) {
        cout << "Error has happened while loading the command line font" << endl;
    }
     View view;
    //FloatRect((1700/2).f, (1080/2).f, 2400.f, 1400.f))
    view.setCenter(sf::Vector2f(WINDOW_WIDTH/2, (WINDOW_HEIGHT/2)));
    view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Music
    Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);
    music.setVolume(0);

    if (!buttons_font.loadFromFile("resources/fonts/arial.TTF")) {
        cout << "Error has happened while loading the font" << endl;
    }



    // Command line
    string user_cli_input, final_cli_input;
    Text cli_text("", cli_font), cli_text_final("", cli_font);
    bool show_cli_cursor=0,cli_selected=false;
    Clock cursor_clock;
    RectangleShape cli_shape,command_shape;
    
    //Edit Window
    RectangleShape edit_window_shape;
    string user_edit_input="type here",checker="Hi,this is for check";
    Text edit_window_text(user_edit_input ,cli_font);
    edit_window_text.setCharacterSize(22);
    Time cursor_time;
    bool edit_selected=false,show_edit_cursor=false;
    //save button
    RectangleShape save_button(Vector2f(120, 50));
    Text save_text("Save", cli_font , 35);
    setButtonProperties(save_button, Color(2,118,36), 515,615);
    setButtonTextProperties(save_button, save_text, Color::Black);
    //back button
    RectangleShape back_button(Vector2f(120, 50));
    Text back_text("Back",cli_font,35);
    setButtonProperties(back_button, Color::Blue, 1700,40);
    setButtonTextProperties(back_button, back_text, Color::Black);    
    //options button
    RectangleShape optn_button(Vector2f(150, 50));
    Text optn_text("Options",cli_font,35);
    setButtonProperties(optn_button, Color::Blue, 1860,40);
    setButtonTextProperties(optn_button, optn_text, Color::Black);  
    //rectangle main.cpp 
    RectangleShape rec_edit(Vector2f(500, 80));
    Text rect_text("main.cpp",cli_font,35);
    setButtonProperties(rec_edit, Color::Blue, 330,85);
    setButtonTextProperties(rec_edit, rect_text, Color::Black);  



    Text game_title;
    game_title.setString("\t  Git \n Started");
    game_title.setFont(game_title_font);
    game_title.setOutlineThickness(-4);
    game_title.setFillColor(Color(50, 50, 50)); // Dark grey fill
    game_title.setOutlineColor(Color(100, 255, 30)); 
    game_title.setCharacterSize(120);
    game_title.setPosition(620, 80);
    /*Git Green: RGB(52, 111, 69)
    Git Blue: RGB(0, 116, 184)
    Git Yellow: RGB(241, 196, 15)
    Git Orange: RGB(235, 97, 0)
    Green outline Color(100, 255, 30)
    Dark grey fill Color(50, 50, 50)*/

    // Main Menu Screen buttons 
    RectangleShape start_button(Vector2f(406,121)),options_button(Vector2f(323,80)),close_button(Vector2f(230,75));
    setButtonProperties(start_button, Color::Green, 960, 520);
    setButtonProperties(options_button, Color::Yellow, 960, 670);
    setButtonProperties(close_button, Color::Red, 1720, 180);
    Text start_text("Start", buttons_font , 53), options_text("Options", buttons_font , 40);
    Text close_text("Close", buttons_font , 33);
    setButtonTextProperties(start_button, start_text, Color::Black);
    setButtonTextProperties(options_button, options_text, Color::Black);
    setButtonTextProperties(close_button, close_text, Color::Black);
    
    Texture main_menu_bg;
    main_menu_bg.loadFromFile("resources/sprites/main_menu_bg.png");
    Sprite main_menu(main_menu_bg);
    
    // Option menu
    RectangleShape mouse_cursor (Vector2f(15, 15));
    Texture slider_bar_texture, option_menu_texture, options_exit_button_texture;
    options_exit_button_texture.loadFromFile("resources/sprites/Exit.png");
    option_menu_texture.loadFromFile("resources/sprites/Option menu.png");
    slider_bar_texture.loadFromFile("resources/sprites/slide.png");
    option_menu_texture.setSmooth(true);
    options_exit_button_texture.setSmooth(true);
    Sprite slider_bar[2], option_menu, options_exit_button;
    CircleShape slider[2];
    for (int i = 0; i < 2; i++){
        slider_bar[i].setTexture(slider_bar_texture);
        slider[i].setRadius(15);
        slider[i].setOrigin(15, 15);
    }
    option_menu.setTexture(option_menu_texture);
    options_exit_button.setTexture(options_exit_button_texture);
    option_menu.setOrigin(400, 300);
    option_menu.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    options_exit_button.setPosition(option_menu.getGlobalBounds().left + 739, option_menu.getGlobalBounds().top + 16);
    SoundBuffer pop_effect;
    pop_effect.loadFromFile("resources/sound_effects/pop.wav");
    Sound pop;
    pop.setBuffer(pop_effect);
    optionMenu sfx_text, music_text;
    slider[0].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 414);
    slider[1].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 245);
    slider_bar[0].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 409);
    slider_bar[1].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 240);
    pop.setVolume(0);
    setSfxAndMusicTexts(sfx_text, music_text, option_menu);
    // Option menu




    Event event;
    while (window.isOpen())
    {
        Mouse mouse;
        Vector2i position = mouse.getPosition(window);
        mouse_cursor.setPosition(position.x, position.y);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || current_screen == "close") 
            {
                window.close();
            }
            //mouse click cli
             if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                

            
                    if (cli_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        cli_selected = true;
                    }
                    else
                    {
                       cli_selected = false;
                       show_cli_cursor=false;
                    }
                     //mouse click edit
                     if (edit_window_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        edit_selected = true;
                    }
                    else
                    {
                       edit_selected = false;
                       show_edit_cursor=false;
                    }
                    
                    if (save_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                    {
                        check_string(user_edit_input,checker);
                    }
                     if (back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                    {
                        current_screen="main menu";
                    }
                    if (optn_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                    {
                        current_screen="options";
                    }
                    
                
            }
           
           
           
            if (event.type == Event::TextEntered) 
            { 
                if(edit_selected){
                     if(user_edit_input.length()<580&&(edit_window_text.findCharacterPos(user_edit_input.size()).y<edit_window_shape.getGlobalBounds().height)){
                        if (isprint(event.text.unicode))     
                            user_edit_input += event.text.unicode;
                        //bounds for text
                        Vector2f pos = edit_window_text.findCharacterPos(user_edit_input.size());  
                        
                        if(!(edit_window_shape.getGlobalBounds().contains(pos))){
                            char temp_last =user_edit_input[user_edit_input.size()-1],temp_b_last=user_edit_input[user_edit_input.size()-2];
                            user_edit_input.pop_back();
                            user_edit_input.pop_back();
                            user_edit_input+=("\n");
                        
                            user_edit_input+=temp_b_last;
                            user_edit_input+=temp_last;

                        }
                    }else {edit_selected=false;}
                }
                // Filter out symbols (only characters in ascii code enters)
                if(cli_selected)
                {
                    
                     if (isprint(event.text.unicode))     
                        user_cli_input += event.text.unicode;
                         
                         Vector2f pst = cli_text.findCharacterPos(user_cli_input.size());  
                        
                        if(!(cli_shape.getGlobalBounds().contains(pst))){
                            user_cli_input.pop_back();
                        
                         }
               
                }
            }
            // If user wants to erase what he wrote
            
            if (event.type == Event::KeyPressed) 
            {    
                if(cli_selected){
                     if (event.key.code == Keyboard::BackSpace) 
                     {
                          if (!user_cli_input.empty())
                             user_cli_input.pop_back();
                     }
                        // User clicks enter and the text will be transfered at the top of the screen
                    if (event.key.code == Keyboard::Return) 
                    {
                           final_cli_input += ("$ "+ user_cli_input + "\n");
                           user_cli_input.clear();
                    }
                }

                if(edit_selected){
                     if (event.key.code == Keyboard::BackSpace) 
                     {
                          if (!user_edit_input.empty())
                             user_edit_input.pop_back();
                     }
                        // User clicks enter and the text will be transfered at the top of the screen
                    if (event.key.code == Keyboard::Return) 
                    {
                           user_edit_input += ( "\n");
                          
                    }
                }
            }
        
        
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) 
            {

                if (start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                {
                    current_screen = "levels";
                }
                if (options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                {
                    current_screen = "options";
                }
                if (close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                {
                    current_screen = "close";
                }
            }
            if (event.type == Event::MouseMoved) {
                if (start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    start_button.setFillColor(Color(34, 139, 34));
                    start_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    start_button.setFillColor(Color::Green);
                    start_button.setScale(1.0f, 1.0f);
                }
                if (options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    options_button.setFillColor(Color(153, 153, 0));
                    options_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    options_button.setFillColor(Color::Yellow);
                    options_button.setScale(1.0f, 1.0f);
                }
                if (close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    close_button.setFillColor(Color(139, 0, 0));
                    close_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    close_button.setFillColor(Color::Red);
                    close_button.setScale(1.0f, 1.0f);
                }
                
                if (save_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    save_button.setFillColor(Color(34, 139, 34));
                    save_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    save_button.setFillColor(Color(2,118,36));
                    save_button.setScale(1.0f, 1.0f);
                }
                if (optn_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    optn_button.setFillColor(Color(34, 139, 34));
                    optn_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    optn_button.setFillColor(Color(2,118,36));
                    optn_button.setScale(1.0f, 1.0f);
                }
                                if (back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    back_button.setFillColor(Color(34, 139, 34));
                    back_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    back_button.setFillColor(Color(2,118,36));
                    back_button.setScale(1.0f, 1.0f);
                }
            }
            // Check if down arrow (later space) key has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Down))
            { 
                if (!dialogue_text.script_ended && current_screen == "levels" && dialogue_text.script_part_ended)
                {
                    if(dialogue_text.new_script[dialogue_text.current_script_index] == dialogue_text.new_script.back())
                    {
                        dialogue_text.script_ended = 1;
                    }    
                    // Clear the current text and reset the script_content to the next string
                    dialogue_text.script_text.setString("");
                    dialogue_text.script_content = dialogue_text.new_script[dialogue_text.current_script_index];
                    dialogue_text.current_script_index++;
                }
            }
        }
        window.setView(view);
        window.clear(Color(223, 221, 221));
        if(current_screen == "main menu")
        {
           
            window.draw(main_menu);
            window.draw(start_button);
            window.draw(options_button);
            window.draw(close_button);
            window.draw(start_text);
            window.draw(options_text);
            window.draw(close_text);
            window.draw(game_title);
        }
        else if(current_screen == "levels")
        {   
        drawDialogue(window, dialogue_box);
        createCommandShape(command_shape);
        createEditWindowShape(edit_window_shape);
        createCliShape(cli_shape);
        printDialogueText(dialogue_text);
        showCursor(cursor_clock, show_cli_cursor,cli_selected, cursor_time);
        showCursor(cursor_clock, show_edit_cursor,edit_selected, cursor_time);
        setCliTexts(cli_text, cli_text_final, user_cli_input, final_cli_input, show_cli_cursor,cli_shape,command_shape);
        showContinuationMessage(dialogue_text);
        window.draw(dialogue_box.body_shape);
        setEditWindowText(edit_window_text,user_edit_input,show_edit_cursor,edit_window_shape);
        window.draw(edit_window_shape);
        window.draw(command_shape);
        window.draw(cli_shape);
        window.draw(dialogue_box.title_shape);
        window.draw(dialogue_box.title);   
        window.draw(dialogue_box.sprite);
        window.draw(dialogue_text.script_text);
        window.draw(dialogue_text.continuation_text);
        window.draw(edit_window_text);
        window.draw(cli_text);
        window.draw(save_button);
        window.draw(save_text);
        window.draw(cli_text_final);  
        window.draw(back_button);
        window.draw(back_text);   
        window.draw(optn_button);
        window.draw(optn_text); 
        window.draw(rec_edit);
        window.draw(rect_text);   
        }
        else if(current_screen == "options")
        {
            controlOptionsExitButton(options_exit_button, mouse_cursor, option_menu);   
            controlSfxAndMusicTexts(sfx_text, music_text, mouse_cursor, pop);
            controlSfxAndMusicVolume(sfx_text, music , pop, slider_bar, slider, option_menu, mouse_cursor);
            window.draw(main_menu);
            window.draw(option_menu);
            for (int i = 0; i < 2; i++)     
                window.draw(slider[i]);;
            window.draw(sfx_text.text);
            window.draw(music_text.text);
            window.draw(options_exit_button);
        }
        window.display();
    }
    }

void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box) 
{
    //Dialogue box (big)
    dialogue_box.body_shape.setSize(Vector2f(900,260));
    dialogue_box.body_shape.setFillColor(Color(44,240,83));
    dialogue_box.body_shape.setOutlineThickness(5);
    dialogue_box.body_shape.setOutlineColor(Color::Black);
    dialogue_box.body_shape.setPosition(80,700);
    
    //Dialogue box (small)
    dialogue_box.title_shape.setSize(Vector2f(900,65));
    dialogue_box.title_shape.setFillColor(Color(95,219,120));
    dialogue_box.title_shape.setOutlineThickness(0.8f);
    dialogue_box.title_shape.setOutlineColor(Color(72,84,74));
    dialogue_box.title_shape.setPosition(80, 700);

    //Sprite
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(15, 630);

    //Title
    dialogue_box.title.setString(dialogue_box.title_content);
    dialogue_box.title.setFont(dialogue_box.font);
    dialogue_box.title.setFillColor(Color(57,60,58));
    dialogue_box.title.setStyle(Text::Italic);
    dialogue_box.title.setCharacterSize(dialogue_box.title_size);
    dialogue_box.title.setPosition(220, 720);
}

void showContinuationMessage(dialogueText &dialogue_text)
{
    dialogue_text.continuation_fade_time += dialogue_text.continuation_fade_clock.restart();
    if(dialogue_text.continuation_fade_time >= seconds(dialogue_text.continuation_delay))
    {
        dialogue_text.continuation_message_running =! dialogue_text.continuation_message_running;
        dialogue_text.continuation_fade_time = Time::Zero;
    }

    if(!dialogue_text.script_ended && dialogue_text.script_part_ended)
    {
        dialogue_text.continuation_text.setString((dialogue_text.continuation_message_running ? dialogue_text.continuation_content : ""));
        dialogue_text.continuation_text.setFont(dialogue_text.font);
        dialogue_text.continuation_text.setFillColor(Color(57,60,58));
        dialogue_text.continuation_text.setCharacterSize(24);
        dialogue_text.continuation_text.setStyle(Text::Italic);
        dialogue_text.continuation_text.setPosition(670, 925);
    }
    else if (!dialogue_text.script_part_ended)
    {
        dialogue_text.continuation_text.setFillColor(Color::Transparent);
    }
}

void printDialogueText(dialogueText& dialogue_text)
{
    dialogue_text.script_text.setFont(dialogue_text.font);
    dialogue_text.script_text.setFillColor(dialogue_text.color);
    dialogue_text.script_text.setCharacterSize(dialogue_text.size);
    dialogue_text.script_text.setPosition(250, 780);
    dialogue_text.time += dialogue_text.clock.restart();
    while (dialogue_text.time >= seconds(dialogue_text.script_speed))
    {
        dialogue_text.time -= seconds(dialogue_text.script_speed);
        if (dialogue_text.script_content.getSize() > 0)
        {
            // Start from index zero
            dialogue_text.script_text.setString(dialogue_text.script_text.getString() + dialogue_text.script_content[0]); 
            // Pop front
            dialogue_text.script_content = dialogue_text.script_content.toAnsiString().substr(1);
            if (dialogue_text.script_content.isEmpty())
            {
                dialogue_text.script_part_ended = 1;
            }
            else
            {
                dialogue_text.script_part_ended = 0;
            }
        } 
    }  
}

void showCursor(Clock& cursor_clock, bool& show_cursor,bool& selected, Time& cursor_time) {
    if(selected){
         cursor_time += cursor_clock.restart();
         // Cursor time to appear
            
        if (cursor_time >= seconds(0.5f)) 
        {
            show_cursor = !show_cursor;
            cursor_time = Time::Zero;
        }
    }
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
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(Color::Black);
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setPosition(x_position, y_position);
}



void setSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, Sprite& option_menu){
    music_text.font.loadFromFile(sfx_text.option_font_type);
    sfx_text.font.loadFromFile(sfx_text.option_font_type);
    music_text.text.setFont(music_text.font);
    sfx_text.text.setFont(sfx_text.font);
    music_text.text.setString("MUSIC");
    sfx_text.text.setString("SFX");
    music_text.text.setFillColor(Color :: White);
    sfx_text.text.setFillColor(Color :: White);
    music_text.text.setCharacterSize(music_text.size);
    sfx_text.text.setCharacterSize(sfx_text.size);
    sfx_text.text.setPosition(option_menu.getGlobalBounds().left + 375, option_menu.getGlobalBounds().top + 321);
    music_text.text.setPosition(option_menu.getGlobalBounds().left + 327, option_menu.getGlobalBounds().top + 163);
}

void controlOptionsExitButton(Sprite& options_exit_button, RectangleShape& mouse_cursor, Sprite& option_menu){
    if (options_exit_button.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds())){
        options_exit_button.setColor(Color :: Red);
        if (Mouse::isButtonPressed(Mouse::Left))
            current_screen = "main menu";
    } 
    else
        options_exit_button.setColor(Color :: White);
}

void controlSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, RectangleShape& mouse_cursor, Sound& pop){
    if (sfx_text.text.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()))
        sfx_text.text.setFillColor(Color :: Red);
    else
        sfx_text.text.setFillColor(Color :: White);
    if (music_text.text.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()))
        music_text.text.setFillColor(Color :: Red);
    else
        music_text.text.setFillColor(Color :: White);
    if (sfx_text.text.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse :: isButtonPressed(Mouse :: Left)))
        pop.play();
}

// This function is designed to adjust the volume of the slider based on its X-coordinate within the slider bar
// As the X-coordinate increases, the volume will also increase accordingly.
void controlSfxAndMusicVolume(optionMenu& sfx_text, Music& music, Sound& pop, Sprite slider_bar[], CircleShape slider[], Sprite& option_menu, RectangleShape& mouse_cursor){
    Mouse mouse;
    Vector2i po = mouse.getPosition();
        if(slider_bar[0].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse :: isButtonPressed(Mouse :: Left))){
            slider[0].setPosition(po.x, slider[0].getPosition().y);
            pop.setVolume(((slider[0].getPosition().x - (option_menu.getGlobalBounds().left + 151) ) * 100.0) / (option_menu.getGlobalBounds().left + 151 + 499.0));
            }
        if (slider_bar[1].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse :: isButtonPressed(Mouse :: Left))){
             slider[1].setPosition(po.x, slider[1].getPosition().y);
             music.setVolume(((slider[1].getPosition().x - (option_menu.getGlobalBounds().left + 151)) * 100.0) / (option_menu.getGlobalBounds().left + 151 + 499.0));
        }
}

void setCliTexts(Text& cli_text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape& rectangle_upper) {
    // Shape of cursor
    cli_text.setString( user_cli_input + (show_cursor ? '|' : ' ')); 
    cli_text.setPosition(rectangle.getPosition());
    cli_text_final.setFillColor(Color::White);
    cli_text_final.setString(final_cli_input);
    cli_text_final.setPosition(rectangle_upper.getPosition().x+7,rectangle_upper.getPosition().y+7);
}

void setEditWindowText(Text & edit_text,string& edit_input,bool& show_cursor, RectangleShape& rectangle){
    edit_text.setString(edit_input+ (show_cursor ? '|' : ' '));
    edit_text.setPosition(rectangle.getPosition().x+7,rectangle.getPosition().y+7);
    edit_text.setFillColor(Color::White);
}

void createEditWindowShape(RectangleShape &form){
    form.setSize(Vector2f(500,600));
    form.setFillColor(Color(0,116,184));
    form.setOutlineThickness(8);
    form.setOutlineColor(Color::Black);
    form.setPosition(80,45);
}

void createCliShape(RectangleShape &form){
    form.setSize(Vector2f(650,60));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200,900);
}

void createCommandShape(RectangleShape &form){
    form.setSize(Vector2f(650,200));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200,700);
}

bool check_string(string&  user_edit_input,string&checker){
   
    if(user_edit_input==checker)
    {
       // cout<<"ye";
        return 1; 
    }
   
    else
    {
       // cout<<"da";
        return 0;
    }
    
}