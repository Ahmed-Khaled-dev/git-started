#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;
const int WINDOW_WIDTH = 1920;
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
bool checkInputEquality(string& edit_window_input, string&);
void createCliInputShape(RectangleShape &form);
void createCliOutputShape(RectangleShape &form);
void createEditWindowShape(RectangleShape &form);
void setEditWindowText(Text & edit_text, string& edit_input, bool&, RectangleShape& rectangle);
void setCliTexts(Text& text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape&);
void showCursor(Clock& cursor_clock, bool& show_cursor,bool& , Time& cursor_time);
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box);
void printDialogueText(dialogueText& dialogue_text);
void playMusicFromFile(string file_path, Music& music);
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text);
void setButtonProperties(RectangleShape& rectangle, Color fillcolor, float x_position, float y_position);
void setButtonTextProperties(RectangleShape& rectangle, Text& text, Color color);
void setSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, Sprite& option_menu);
void controlSfxAndMusicTexts(optionMenu& sfx_text, optionMenu& music_text, RectangleShape& mouse_cursor, Sound& pop);
void controlOptionsExitButton(Sprite& options_exit_button, RectangleShape& mouse_cursor, Sprite& option_menu);
void controlSfxAndMusicVolume(optionMenu& sfx_text, Music& music, Sound& pop, Sprite slider_bar[], CircleShape contoroller[], Sprite& option_menu, RectangleShape& mouse_cursor);
void showContinuationMessage(dialogueText &dialogue_text);

int main()
{
    const int WINDOW_WIDTH = 1920;
    const int WINDOW_HEIGHT = 1080;
    string current_screen = "main menu";
struct commit{
    string message;
    Sprite sprite;
};

void addCommit(unsigned short int &commits_count, commit commits[], Texture& commit_textures, string commit_message);

const unsigned short int WINDOW_X = 1600, WINDOW_Y = 1000;
const string GAME_TITLE = "Git Started";
/** note that some variables should be in the while(window.isOpen()) loop because it needs to be updated */
unsigned short int p1 = 0, delay = 0; //used for the animation

void addCommit(unsigned short int &commits_count, commit commits[], Texture& commit_textures, string commit_message);

void spriteAnimationAndPosition(Sprite& head, Vector2i& position_of_mouse, commit commit[], bool& clicked, bool& head_should_move);

RenderWindow window(VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);

    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Git Started!");

    // Dialogue box
    dialogue_box.font.loadFromFile(dialogue_box.font_type);
    dialogue_box.texture.loadFromFile(dialogue_box.image_path);
    dialogue_text.font.loadFromFile(dialogue_text.font_type);
    unsigned short int commits_count = 0;
int main()
{
    RenderWindow window(VideoMode(1920, 1080), "GitStarted");
    //all the needed variables
    window.setFramerateLimit(60);
    Sprite head;
    Texture octacat, commit_textures;
    octacat.loadFromFile("octocat.png");
    octacat.setSmooth(true);
    commit_textures.loadFromFile("commits_sprites.png");
    head.setTexture(octacat);
    commit_textures.setSmooth(true);
    head.setTextureRect(IntRect(0, 0, 200.25, 301));
    head.setScale(0.8, 0.8);
    head.setOrigin(100.125, 150.5);
    head.setPosition(0, 200);
    bool clicked;
    octacat.setSmooth(true);
    bool head_should_move = 0;
     unsigned short int commits_count = 0;
    const unsigned short int MAX_COMMITS = 100;

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
    //cli_font.loadFromFile("resources/fonts/arial.ttf");
    if (!cli_font.loadFromFile("resources/fonts/Roboto-Black.ttf")) {
        cout << "Error has happened while loading the command line font" << endl;
    }

    Font arial;
    if (!arial.loadFromFile("resources/fonts/arial.ttf")) {
        cout << "Error has happened while loading arial font" << endl;
    }

    // View
    View view;
    //FloatRect((1700/2).f, (1080/2).f, 2400.f, 1400.f))
    view.setCenter(sf::Vector2f(WINDOW_WIDTH/2, (WINDOW_HEIGHT/2)));
    view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Music
    Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);
    music.setVolume(0);

    // Command line interface (CLI)
    string user_cli_input, final_cli_input;
    Text cli_text("", cli_font), cli_text_final("", cli_font);
    bool show_cli_cursor = 0, cli_selected = 0;
    Clock cursor_clock;
    RectangleShape cli_output_shape, cli_input_shape;
    
    // Edit Window
    RectangleShape edit_window_shape;
    string edit_window_input = "type here", checker = "Hi, this is for check";
    Text edit_window_text(edit_window_input ,cli_font);
    edit_window_text.setCharacterSize(22);
    Time cursor_time;
    bool edit_window_selected = 0, show_edit_window_cursor = 0;
    // Save button
    RectangleShape edit_window_save_button(Vector2f(120, 50));
    Text edit_window_save_text("Save", arial , 35);
    setButtonProperties(edit_window_save_button, Color(2,118,36), 522, 621);
    setButtonTextProperties(edit_window_save_button, edit_window_save_text, Color::White);
    // Game window is the window containing the dialogue box, edit window, cli etc.
    // Back button
    RectangleShape game_window_back_button(Vector2f(140, 50));
    Text game_window_back_text("Back", buttons_font,35);
    setButtonProperties(game_window_back_button, Color::Blue, 1600, 40);
    setButtonTextProperties(game_window_back_button, game_window_back_text, Color::Black);    
    // Options button
    RectangleShape game_window_options_button(Vector2f(200, 50));
    Text game_window_options_text("Options", buttons_font, 35);
    setButtonProperties(game_window_options_button, Color::Yellow, 1800, 40);
    setButtonTextProperties(game_window_options_button, game_window_options_text, Color::Black);
    // Main.cpp Rectangle 
    RectangleShape edit_window_title(Vector2f(500, 80));
    Text edit_window_title_text("Main.cpp", cli_font, 35);
    setButtonProperties(edit_window_title, Color(110, 164, 198), 330, 85);
    setButtonTextProperties(edit_window_title, edit_window_title_text, Color::Black);  

    // Main Menu
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
    RectangleShape main_menu_start_button(Vector2f(406,121)),main_menu_options_button(Vector2f(323,80));
    RectangleShape main_menu_close_button(Vector2f(230,75));
    setButtonProperties(main_menu_start_button, Color::Green, 960, 520);
    setButtonProperties(main_menu_options_button, Color::Yellow, 960, 670);
    setButtonProperties(main_menu_close_button, Color::Red, 1720, 180);
    Text main_menu_start_text("Start", buttons_font , 53), main_menu_options_text("Options", buttons_font , 40);
    Text main_menu_close_text("Close", buttons_font , 33);
    setButtonTextProperties(main_menu_start_button, main_menu_start_text, Color::Black);
    setButtonTextProperties(main_menu_options_button, main_menu_options_text, Color::Black);
    setButtonTextProperties(main_menu_close_button, main_menu_close_text, Color::Black);
    
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
    option_menu.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0);
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
    Texture commit_textures;
    if (!commit_textures.loadFromFile("resources/sprites/commits_sprites.png"))
    {
        cout << "Error loading commit sprites" << endl;
    }
    commit_textures.setSmooth(true);

    while (window.isOpen())
    {
        Mouse mouse;
        Vector2i position = mouse.getPosition(window);
        Vector2f worldPos = window.mapPixelToCoords(position);
        mouse_cursor.setPosition(worldPos.x, worldPos.y);
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || current_screen == "close") 
            {
                window.close();
            }
            //mouse click cli
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                    if (cli_output_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "levels")
                    {
                        cli_selected = true;
                    }
                    else
                    {
                        cli_selected = false;
                        show_cli_cursor = false;
                    }
                    // Mouse clicked on edit window
                    if (edit_window_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "levels")
                    {
                        edit_window_selected = true;
                    }
                    else
                    {
                        edit_window_selected = false;
                        show_edit_window_cursor = false;
                    }
                    if (edit_window_save_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "levels") 
                    {
                        checkInputEquality(edit_window_input, checker);
                    }
                    if (game_window_back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "levels") 
                    {
                        current_screen = "main menu";
                    }
                    if (game_window_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "levels") 
                    {
                        current_screen = "options_in_game";
                    }
                    if (main_menu_start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                    {
                        current_screen = "levels";
                    }
                    if (main_menu_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                    {
                        current_screen = "options";
                    }
                    if (main_menu_close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && current_screen == "main menu") 
                    {
                        current_screen = "close";
                    }
            }
            if (event.type == Event::TextEntered) 
            { 
                if (edit_window_selected && current_screen == "levels")
                {
                    const short int edit_window_max_chars = 600;
                    if (edit_window_input.length() < edit_window_max_chars && (edit_window_text.findCharacterPos(edit_window_input.size()).y < edit_window_shape.getGlobalBounds().height))
                    {
                        if (isprint(event.text.unicode))     
                            edit_window_input += event.text.unicode;
                        // Bounds for text
                        Vector2f pos = edit_window_text.findCharacterPos(edit_window_input.size());  
                        
                        if(!((edit_window_shape.getGlobalBounds()).contains(pos))){
                            char temp_last = edit_window_input[edit_window_input.size()-1];
                            char temp_b_last = edit_window_input[edit_window_input.size()-2];
                            edit_window_input.pop_back();
                            edit_window_input.pop_back();
                            edit_window_input += ("\n");
                        
                            edit_window_input += temp_b_last;
                            edit_window_input += temp_last;
                        }
                    }
                    else
                        edit_window_selected = false;
                }
                // Filter out symbols (only characters in ascii code enters)
                if (cli_selected && current_screen == "levels")
                {
                    if (isprint(event.text.unicode))     
                        user_cli_input += event.text.unicode;
                         
                        Vector2f pst = cli_text.findCharacterPos(user_cli_input.size());  
                        
                        if (!(cli_output_shape.getGlobalBounds().contains(pst)))
                        {
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
                if(edit_window_selected)
                {
                    if (event.key.code == Keyboard::BackSpace) 
                    {
                        if (!edit_window_input.empty())
                            edit_window_input.pop_back();
                    }
                    if (event.key.code == Keyboard::Return) 
                    {
                        edit_window_input += ( "\n");  
                    }
                }
            }
            if (event.type == Event::MouseMoved) {
                if (main_menu_start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    main_menu_start_button.setFillColor(Color(34, 139, 34));
                    main_menu_start_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    main_menu_start_button.setFillColor(Color::Green);
                    main_menu_start_button.setScale(1.0f, 1.0f);
                }
                if (main_menu_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    main_menu_options_button.setFillColor(Color(153, 153, 0));
                    main_menu_options_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    main_menu_options_button.setFillColor(Color::Yellow);
                    main_menu_options_button.setScale(1.0f, 1.0f);
                }
                if (main_menu_close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    main_menu_close_button.setFillColor(Color(139, 0, 0));
                    main_menu_close_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    main_menu_close_button.setFillColor(Color::Red);
                    main_menu_close_button.setScale(1.0f, 1.0f);
                }
                if (edit_window_save_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    edit_window_save_button.setFillColor(Color(34, 139, 34));
                    edit_window_save_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    edit_window_save_button.setFillColor(Color(2,118,36));
                    edit_window_save_button.setScale(1.0f, 1.0f);
                }
                if (game_window_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    game_window_options_button.setFillColor(Color(153, 153, 0));
                    game_window_options_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    game_window_options_button.setFillColor(Color::Yellow);
                    game_window_options_button.setScale(1.0f, 1.0f);
                }
                if (game_window_back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))) 
                {
                    game_window_back_button.setFillColor(Color(153, 153, 0));
                    game_window_back_button.setScale(0.9f, 0.9f);
                }
                else 
                {
                    game_window_back_button.setFillColor(Color::Yellow);
                    game_window_back_button.setScale(1.0f, 1.0f);
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
        
        window.clear(Color(223, 221, 221));
        if(current_screen == "main menu")
        {
           
            window.draw(main_menu);
            window.draw(main_menu_start_button);
            window.draw(main_menu_options_button);
            window.draw(main_menu_close_button);
            window.draw(main_menu_start_text);
            window.draw(main_menu_options_text);
            window.draw(main_menu_close_text);
            window.draw(game_title);
        }
        else if(current_screen == "levels")
        {   
            drawDialogue(window, dialogue_box);
            createCliInputShape(cli_input_shape);
            createEditWindowShape(edit_window_shape);
            createCliOutputShape(cli_output_shape);
            printDialogueText(dialogue_text);
            showCursor(cursor_clock, show_cli_cursor,cli_selected, cursor_time);
            showCursor(cursor_clock, show_edit_window_cursor,edit_window_selected, cursor_time);
            setCliTexts(cli_text, cli_text_final, user_cli_input, final_cli_input, show_cli_cursor,cli_output_shape,cli_input_shape);
            showContinuationMessage(dialogue_text);
            setEditWindowText(edit_window_text,edit_window_input,show_edit_window_cursor,edit_window_shape);
            window.draw(dialogue_box.body_shape);
            window.draw(edit_window_shape);
            window.draw(cli_input_shape);
            window.draw(cli_output_shape);
            window.draw(dialogue_box.title_shape);
            window.draw(dialogue_box.title);   
            window.draw(dialogue_box.sprite);
            window.draw(dialogue_text.script_text);
            window.draw(dialogue_text.continuation_text);
            window.draw(edit_window_text);
            window.draw(cli_text);
            window.draw(edit_window_save_button);
            window.draw(edit_window_save_text);
            window.draw(cli_text_final);  
            window.draw(game_window_back_button);
            window.draw(game_window_back_text);   
            window.draw(game_window_options_button);
            window.draw(game_window_options_text); 
            window.draw(edit_window_title);
            window.draw(edit_window_title_text);   
        }
        else if(current_screen == "options")
        {
            // Write here "options" screen properties
                addCommit(commits_count, commits, commit_textures, "initial commit", WINDOW_X, WINDOW_Y);
                addCommit(commits_count, commits, commit_textures, "initial commit");
            }
        }
            if (event.type == Event::Closed)
                window.close();
        
            if (Keyboard::isKeyPressed(Keyboard::Up))
                addCommit(commits_count, commits, commit_textures, "initial commit");
            
        }
       
        spriteAnimationAndPosition(head, position, commits, clicked, head_should_move);

        
        // Unsigned char stores from 0 -> 255 (RGB range)
        const unsigned char bg_color_rgb[3] = {43, 45, 47};
        window.clear({bg_color_rgb[0], bg_color_rgb[1], bg_color_rgb[2]});
        for (unsigned short int i = 0; i < commits_count; i++)
        {
            window.draw(commits[i].sprite);
            //cout << "Commit number " << i << " X-position -> " << commits[i].sprite.getPosition().x << endl;
        }
        window.setView(view);
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

void showCursor(Clock& cursor_clock, bool& show_cursor, bool& selected, Time& cursor_time) {
    if(selected)
    {
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
    text.setFillColor(color);
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
void addCommit(int& commits_count, commit commits[], Texture& commit_textures, string commit_message, int window_length, int window_width){
void addCommit(int& commits_count, commit commits[], Texture& commit_textures, string commit_message){
void addCommit(unsigned short int& commits_count, commit commits[], Texture& commit_textures, string commit_message){
    // All the following are the same for both conditions
    Sprite commit_sprite;
    commit_sprite.setTexture(commit_textures);
    const float COMMIT_SCALING = 0.5;
    commit_sprite.scale(Vector2f(COMMIT_SCALING, COMMIT_SCALING));

    if (commits_count == 0)
    {
        // I cut from the texture a circle **without** an arrow
        commit_sprite.setTextureRect(IntRect(287, 70, 156, 156)); 
        commit_sprite.setPosition(WINDOW_X/2, WINDOW_Y/3);
    }
    else
    {
        const unsigned short int circle_length = 60;
        const unsigned short int arrow_length = 125;
        for (unsigned short int i = 0; i < commits_count; i++)
        {
            commits[i].sprite.move(Vector2f(-(circle_length + arrow_length), 0));
        }
        // I cut from the texture a circle **with** an arrow
        commit_sprite.setTextureRect(IntRect(37, 278, 406, 432));
        commit_sprite.setPosition(WINDOW_X/2 - arrow_length, WINDOW_Y/3);
    }

    commit new_commit = {commit_message, commit_sprite};
    commits[commits_count] = new_commit;
    commits_count++;
}

<<<<<<< HEAD
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
    if (options_exit_button.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()))
    {
        options_exit_button.setColor(Color :: Red);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (current_screen == "options_in_game")
            {
                current_screen = "levels";
            }
            else if (current_screen == "options")
            {
                current_screen = "main menu";
            }
        }
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
        if(slider_bar[0].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse :: isButtonPressed(Mouse :: Left))){
            slider[0].setPosition(mouse_cursor.getPosition().x, slider[0].getPosition().y);
            pop.setVolume(((slider[0].getPosition().x - (option_menu.getGlobalBounds().left + 151) ) * 100.0) / (option_menu.getGlobalBounds().left + 151 + 499.0));
            }
        if (slider_bar[1].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse :: isButtonPressed(Mouse :: Left))){
             slider[1].setPosition(mouse_cursor.getPosition().x, slider[1].getPosition().y);
             music.setVolume(((slider[1].getPosition().x - (option_menu.getGlobalBounds().left + 151)) * 100.0) / (option_menu.getGlobalBounds().left + 151 + 499.0));
        }
}

void setCliTexts(Text& cli_text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape& rectangle_upper) {
    // Shape of cursor
    cli_text.setString(user_cli_input + (show_cursor ? '|' : ' ')); 
    cli_text.setPosition(rectangle.getPosition());
    cli_text_final.setFillColor(Color::White);
    cli_text_final.setString(final_cli_input);
    cli_text_final.setPosition(rectangle_upper.getPosition().x+7, rectangle_upper.getPosition().y+7);
}

void setEditWindowText(Text & edit_text,string& edit_input,bool& show_cursor, RectangleShape& rectangle){
    edit_text.setString(edit_input + (show_cursor ? '|' : ' '));
    edit_text.setPosition(rectangle.getPosition().x+7, rectangle.getPosition().y+90);
    edit_text.setFillColor(Color::White);
}

void createEditWindowShape(RectangleShape &form){
    form.setSize(Vector2f(500,600));
    form.setFillColor(Color(0,116,185));
    form.setOutlineThickness(8);
    form.setOutlineColor(Color::Black);
    form.setPosition(80,45);
}

void createCliOutputShape(RectangleShape &form){
    form.setSize(Vector2f(650,60));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200,900);
}

void createCliInputShape(RectangleShape &form){
    form.setSize(Vector2f(650,200));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200,700);
}

bool checkInputEquality(string& edit_window_input, string& checker){
    if(edit_window_input == checker)
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
#include<iostream>
using namespace std;
using namespace sf;

/** note that some variables should be in the while(window.isOpen()) loop because it needs to be updated */

short int p1 = 0, delay = 0;




void sprite_animation_and_position(Sprite& head, Vector2i& position_of_mouse, CircleShape commit[], bool& clicked, bool& move)
=======


}

void spriteAnimationAndPosition(Sprite& head, Vector2i& position_of_mouse, commit commit[], bool& clicked, bool& head_should_move)
>>>>>>> 3152766 (edited the name of the fucntions and improved the speed)
{
    if (true) //sprite animation
    {
        head.setTextureRect(IntRect(p1 * 200.25, 0, 200.25, 301));
        delay++;
        if (delay >= 20)
        {
            p1++;
            delay = 0;
        }
        if (p1 == 2)
            p1 = 0;
    }
<<<<<<< HEAD
    for (short int i = 0; i < 5; i++)
    {

        bool contained = commit[i].getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) ;
        if ( clicked) {
            move = 1;
        }
        cout << head.getPosition().x - commit[1].getPosition().x  << '\t' <<move<<endl;
        if (commit[i].getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) && move){
            if(head.getPosition().x - commit[i].getPosition().x < 0){
                head.setTextureRect(IntRect(2 * 200.25, 0, 200.25, 301));
                head.move(1.0, 0);}
            else if (head.getPosition().x - commit[i].getPosition().x > 0){
                 head.setTextureRect(IntRect(3 * 200.25, 0, 200.25, 301));
                head.move(-1.0, 0);}
            else if (abs(head.getPosition().x - commit[i].getPosition().x) <=6){
                move = 0;
=======
    for (short int i = 0; i < 100; i++)
    {
        if ( clicked ) {
            head_should_move = 1;
        }
       // cout << head.getPosition().x - commit[1].sprite.getPosition().x  << '\t' <<head_should_move<<endl;
        if (commit[i].sprite.getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) && head_should_move){
            if(head.getPosition().x - commit[i].sprite.getPosition().x < 0){
                head.setTextureRect(IntRect(2 * 200.25, 0, 200.25, 301));
                head.move(5.0, 0);}
            else if (head.getPosition().x - commit[i].sprite.getPosition().x > 0){
                 head.setTextureRect(IntRect(3 * 200.25, 0, 200.25, 301));
                head.move(-5.0, 0);}
            else if (abs(head.getPosition().x - commit[i].sprite.getPosition().x) == 0){
                head_should_move = 0;
>>>>>>> 3152766 (edited the name of the fucntions and improved the speed)
                }
            
        }
    }
<<<<<<< HEAD

}
=======
>>>>>>> 3152766 (edited the name of the fucntions and improved the speed)
}
