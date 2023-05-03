#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace sf;

unsigned short int graph_smoke_animation_delay = 0, current_smoke_animation_frame = 0;
short int index_of_the_last_commit = 0;
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
string current_screen = "main menu";
string levels_screens[10] = {"intro level", "init level", "commit level", "checkout level"};
int current_level_screen_index = 0;

RenderWindow window(VideoMode::getDesktopMode(), "Git Started!");
// Structs

struct graphHead{
    // We have 4 animation frames for the octocat movement (0, 1, 2, 3)
    unsigned short int current_animation_frame = 0, idle_animation_delay = 0;
    unsigned short int latest_commit_movement_delay = 0;
    short int distance_to_checkout_commit = 0, distance_to_latest_commit = (50 + 135);
    short int x_border_deflection_velocity = 3, y_border_deflection_velocity = 3;
}graph_head;

struct commit{
    string message;
    Sprite sprite;
};

struct gameLevel
{
    vector <pair<int,string>> new_script;
    string level_commands [5];
};

struct dialogueBox{
    Font font;
    Texture texture;
    Sprite sprite;
    Text title;
    string title_content = "Mentor";
    double title_size = 25;
    string image_path = "resources/sprites/man.png";
    string font_type = "resources/fonts/Roboto-Black.ttf";
    RectangleShape body_shape;
    RectangleShape title_shape;
}dialogue_box;

struct continuationMessage
{
    Time continuation_fade_time;
    Clock continuation_fade_clock;
    Font font;
    Text continuation_text;
    double continuation_delay = 0.8f;
    string continuation_content = "Press down to continue...";
    bool continuation_message_running = 0;
    bool sub_script_ended = 0;   // For the sub-strings inside the whole script vector
    string font_type = "resources/fonts/BreeSerif-Regular.ttf";
    bool commands_flag = 0;
}continuation_message;

struct dialogueText
{
    Font font;
    Time time;
    Clock typewrite_clock; // For the typewriting effect
    Text script_text;
    string font_type = "resources/fonts/BreeSerif-Regular.ttf";
    Color color = Color::Black;
    double size = 29;
    double script_speed = 0.01f;
    String script_content = " ";
    int current_script_index = 0;
    // The whole vector/dialogue/script
    bool script_ended = 0;
     
}dialogue_text;

int current_level_screen = 0;
// For the vectors of pairs
// If bool = 1 
// Then it tells the dialogue that it should wait for a command before this dialogue sub-script
// If bool = 2
// Then it tells the dialogue that it should wait for the user to edit in the edit menu before this sub-script
gameLevel level[4] = {
    /*level_0 (intro)*/{{
    {0 ,"And last place goes to... (name)!\n*You are devastated but you saw it coming*\nbecause your team's code was full of errors\nand was disorganized"},
    {0 ,"* Suddenly...\nsomeone appears in front of you, they look\nsimilar to you but older *"},
    {0 ,"Hello!, I finally succeeded in going back\nin time to help you learn from our mistakes."},
    {0 ,"I am you but from the future. I remember this\nday clearly. I was filled with disappointment\nbecause of my failure,"},
    {0,"But fear not, I am here to introduce\nyou to a system that changed my life."}, 
    {0 ,"I am talking about \"GIT\",\n\"GIT\" is a free version control system that tracks\nall versions of your code."},
    {0 ,"It is created for the sake of aiding us in\nwriting our code. It has useful commands that\nhelp us in working with others quickly\nand efficiently."},
    {0 ,"I will take you back with my time machine to\nthe start of the contest and walk you through all\nthe GIT commands."},
    {0 ,"I will try my best to teach you everything about\nGIT so that you can start your project again with\nGIT and have a shot in winning this contest\nAre you ready to Git started?"}}},
    /*level_1 (git init)*/{{
    {0,"Let me show you around our time machine.\nThis blue box is our IDE, where you\nwill write the code you want."},
    {0,"This black box  is the command line window,\nwhere you will write the suitable \"GIT\" commands\nfor GIT to execute, also known as the \"Console\"."},
    {0,"Here is your git graph, it is a diagram\nthat shows how the commands are translated and\nmakes it easier to understand how they work."},
    {0,"After showing you around, let's start our\nadventure by telling you what the word \"command\"\nmeans in \"GIT\"."},
    {0,"\"Commands\" are a set of instructions, each one\nof them is responsible for making a certain job."},
    {0,"We will start with our first command \"Git init\".\nIt's responsible for watching your current\nfolder called a git repository."},
    {0,"All of our git commands won't work unless we\ninitialize a repository. That's why\n\"Git init\" has to be the first command to be executed."},
    {0,"Let's try executing it together. Please type\n\"git init\" in the command line (the black box)"},
    {1,"Would you look at that!! That's our head.\nDoes it remind you of something?"},
    {0,"This Octocat symbolizes the head in git.\nIt is inspired from the github logo and it will\naccompany you throughout the game."},
    {0,"You will get to know more about the\n\"head\" in the upcoming levels..."}}
    ,{"git init"}},
    /*level_2 (git commit)*/{{
    {0,"Now that you've created your first repository\n(which we will call \"repo\" from now),\nyou'll start by writing your code."},
    {0,"Throughout each big step,\nyou will need to keep track of your history."},
    {0,"Imagine this; you are working on\na huge project with your team,"},
    {0,"One of your team mates messed up a part of\ntheir code, they can't remember what part\ngot messed up,"},
    {0,"Neither can they go back to the code that\nworked fine, Scary to imagine right?"},
    {0,"That's where \"commits\" come in hand.\n\"commits\" are like checkpoints in games\nbut for your code."},
    {0,"We will use the \"git commit <commit_message>\"\ncommand."},
    {0,"But first, let's write some code together!\nIn the \"main.cpp\" edit window, we need\nto write code using C++"},
    {0,"For example, try writing: \"int i = 5;\""},
    {2,"Now you need to commit your changes\nto mark this checkpoint!"},
    {0,"In the command line write:\ngit commit, name it any thing you want\nfor example \"First Variable!\""},
    {1,"Congratulations! you have just written your\nfirst commit.\nThe circle that just appeared represents our commit."},
    {0,"As you can see, our Head (Octocat) has appeared\nabove our commit."},
    {0,"He will be standing on the latest commit\nwe create."},
    {0,"It's your turn to write another piece of\ncode and commit your changes!"},
    {0,"Try adding another variable in \"main.cpp\"\nedit window."},
    {2,"Commit your changes with the message\nthat describes it best!"},
    {1,"Notice that the Head moves onto your\nnew commit."},
    {0,"Now it is time for you to try out for yourself,\ngood luck!"}},
    {"git commit","git commit"}},
    /*level_3 (git checkout)*/{{
    {0,"Look at all the commits you have;\nyou must be proud of yourself!"},
    {0,"Now as mentioned before our friend (the Head)\nis looking at the latest commit that we created."},
    {0,"But now you need to look at a previous checkpoint\nof your code, what do we need to do?"},
    {0,"We need to move the Head to the\ncommit we want.Each commit has a specified number\nto show it, this number is called \"commit hash\""},
    {0,"We will use a new command which is\n\"git checkout <commit hash>\". Now, we want to\ncheckout to our first commit."},
    {0,"Write in the console:\n\"git checkout\" and the \"hash\"of that commit."},
    {1,"As you can see in the edit menu,\nYour code has changed to what you first wrote\nin the previous level!"},
    {0,"Now let's checkout again to our last commit.\nHere you have your latest code again!"},
    {0,"The \"git checkout\" command has a lot of benefits\nthat you will discover more into the next levels."}},
    {"git checkout"}}};

struct optionMenu{
    Font font;
    Text text;
    String option_font_type = "resources/fonts/minecraft_font.ttf";
    const int short  size = 64;
};

// Functions declaration
bool checkInputEquality(string& current_edit_window_input, string&correct_string, bool& edit_window_changed);
void createCliInputShape(RectangleShape &form);
void createCliOutputShape(RectangleShape &form);
void createEditWindowShape(RectangleShape &form);
void setEditWindowText(Text & edit_text, string& edit_input, bool&, RectangleShape& rectangle);
void setCliTexts(Text& text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape&);
void showCursor(Clock& cursor_clock, bool& show_cursor, bool&, Time& cursor_time);
void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box);
void printDialogueText(dialogueText& dialogue_text);
void playMusicFromFile(string file_path, Music& music);
void updateButtonText(RectangleShape& rectangle, Text& text, string new_text);
void setButtonProperties(RectangleShape& rectangle, int red_intensity, int green_intensity, int blue_intensity, float x_position, float y_position);
void setButtonTextProperties(RectangleShape& rectangle, Text& text, Color color);
void setSfxTexts(optionMenu& sfx_text, Sprite& option_menu);
void controlSfxTexts(optionMenu& sfx_text, RectangleShape& mouse_cursor, Sound& pop, Event& Event);
void controlOptionsExitButton(Sprite& options_exit_button, RectangleShape& mouse_cursor, Sprite& option_menu);
void setSliderMoveLimits(Sprite slider_bar[], CircleShape slider[]);
void controlSfxAndMusicVolume(optionMenu& sfx_text, Music& music, Sound& pop_commit, Sprite slider_bar[], CircleShape slider[], Sprite& option_menu, RectangleShape& mouse_cursor, Event& event, bool& change_sfx_volume, bool& change_music_volume);
void addCommit(unsigned short int& commits_count, commit commits[], Texture& commit_textures, string commit_message);
void headBorderDeflection(Sprite& head, bool& window_collision_mode, bool& additional_commit_created);
void headIdleAnimation(Sprite& head, bool& additional_commit_created);
void calculateHeadDistance(Sprite& head, Vector2i& position_of_mouse, commit commit[]);
void headAnimationAndMovement(Sprite& head);
void moveHeadToLatestCommit(Sprite& head, bool& additional_commit_created);
void makeSmoke(Sprite& smoke, bool& should_create_smoke);
void setTextOriginAndPosition(Text& text, float x_position, float y_position);
void showContinuationMessage(continuationMessage& continuation_message,bool& edit_window_changed);

int main()
{
    // Dialogue box
    dialogue_box.texture.loadFromFile(dialogue_box.image_path);
    dialogue_box.font.loadFromFile(dialogue_box.font_type);
    dialogue_text.font.loadFromFile(dialogue_text.font_type);
    continuation_message.font.loadFromFile(continuation_message.font_type);

    // Fonts
    Font buttons_font;
    if (!buttons_font.loadFromFile("resources/fonts/Righteous-Regular.ttf")) {
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
    view.setCenter(sf::Vector2f(WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2)));
    view.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Music
    Music music;
    playMusicFromFile("resources/audio/lepo.wav", music);
    music.setVolume(0);

    // Transition slide
    Texture transition_slide;
    transition_slide.loadFromFile("resources/sprites/transition.jpeg");
    Sprite transition_slide_bg;
    transition_slide_bg.setTexture(transition_slide);
    transition_slide_bg.setScale(1.195f, 1.1f);
    int transition_level_texts_index = 0;
    // Transition array of strings (could be put in the levels struct)
    string transition_level_texts[10] = {"Please enter your name:","The Git Beginning!\n(git init) \n\n\npress space to continue ","Committing to Success:\nCrafting Meaningful\nCommits \n(git commit) \n\npress space to continue","TimeWarper:\nNavigating the Timeline\n(git checkout)  \npress space to continue","thank you"};
    Text transition_text(transition_level_texts[transition_level_texts_index], game_title_font, 29);
    transition_text.setPosition(1310, 650);
    transition_text.setFillColor(Color::White);

    // Levels menu
    RectangleShape levels_back_button(Vector2f(125, 60)), level_buttons_bg(Vector2f(1140, 830)), intro_level_button(Vector2f(1000, 150));
    RectangleShape init_level_button(Vector2f(1000, 150)), commit_level_button(Vector2f(1000, 150)), checkout_level_button(Vector2f(1000, 150));

    setButtonProperties(levels_back_button, 46, 139, 87, 77, 45);
    setButtonProperties(level_buttons_bg, 200, 200, 200, 960, 510);
    setButtonProperties(intro_level_button, 112, 128, 144, 960, 245);
    setButtonProperties(init_level_button, 112, 128, 144, 960, 430);
    setButtonProperties(commit_level_button, 112, 128, 144, 960, 650);
    setButtonProperties(checkout_level_button, 112, 128, 144, 960, 825);

    Texture levels_menu;
    if (!levels_menu.loadFromFile("resources/sprites/levels-menu.jpg")) {
        cout << "Error has happened while loading the levels_menu background" << endl;
    }
    Sprite levels_menu_bg;
    levels_menu_bg.setTexture(levels_menu);
    levels_menu_bg.setOrigin(levels_menu_bg.getLocalBounds().width / 2.0f, levels_menu_bg.getLocalBounds().height / 2.0f);
    levels_menu_bg.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    levels_menu_bg.setScale(1.52f, 1.52f);

    // A way to 1 - text.setFont(); 2 - text.setString(); 3 - text.setCharacterSize(); in one line  
    Text levels_back_button_text("Back", buttons_font, 32), intro_levels_category("Intro", buttons_font, 32);
    Text commits_levels_category("Commits", buttons_font, 32);
    Text intro_level_text("Tragic Failure: The Cost of Poor Organization (intro)", buttons_font, 29);
    Text init_level_text("The Git Beginning! (git init)", buttons_font, 29);
    Text commit_level_text("Committing to Success: Crafting Meaningful Commits (git commit)", buttons_font, 29);
    Text checkout_level_text("TimeWarper: Navigating the Timeline (git checkout)", buttons_font, 29);

    commits_levels_category.setFillColor(Color::Black);
    intro_levels_category.setFillColor(Color::Black);

    setButtonTextProperties(levels_back_button, levels_back_button_text, Color::Black);
    setButtonTextProperties(intro_level_button, intro_level_text, Color::White);
    setButtonTextProperties(init_level_button, init_level_text, Color::White);
    setButtonTextProperties(commit_level_button, commit_level_text, Color::White);
    setButtonTextProperties(checkout_level_button, checkout_level_text, Color::White);

    setTextOriginAndPosition(intro_levels_category, 960, 140);
    setTextOriginAndPosition(commits_levels_category, 960, 545);

    // Command line interface (CLI)
    RectangleShape cli_output_shape, cli_input_shape;
    string user_cli_input, final_cli_input, commit_message;
    int commands_entered_counter = 0;
    Text cli_text("", cli_font), cli_text_final("", cli_font);
    string cli_commit_msg_request = " # Please enter the commit message \nfor your changes in  the command line.";
    bool show_cli_cursor = 0, cli_selected = 0, commit_command_entered = 0, correct_command = 0;
    Clock cursor_clock;
    

    // Edit Window
    RectangleShape edit_window_shape;
    string current_edit_window_input = "type here", old_edit_window_input = "type here";
    const short int EDIT_WINDOW_MAX_CHARS = 600;
    Text edit_window_text(current_edit_window_input ,cli_font);
    edit_window_text.setCharacterSize(22);
    Time cursor_time;
    bool edit_window_selected = 0, show_edit_window_cursor = 0, edit_window_changed = 0;
    // Next button
    RectangleShape game_window_next_button(Vector2f(140, 50));
    Text game_window_next_text("Next", buttons_font, 35);
    setButtonProperties(game_window_next_button, 75, 181, 67, 1420, 40);
    setButtonTextProperties(game_window_next_button, game_window_next_text, Color::White);
    // Save button
    RectangleShape edit_window_save_button(Vector2f(120, 50));
    Text edit_window_save_text("Save", arial, 35);
    setButtonProperties(edit_window_save_button, 2, 118, 36, 522, 621);
    setButtonTextProperties(edit_window_save_button, edit_window_save_text, Color::White);
    // Game window is the window containing the dialogue box, edit window, cli etc.
    // Back button
    RectangleShape game_window_back_button(Vector2f(140, 50));
    Text game_window_back_text("Back", buttons_font, 35);
    setButtonProperties(game_window_back_button, 0, 0, 255, 1600, 40);
    setButtonTextProperties(game_window_back_button, game_window_back_text, Color::Black);
    // Options button
    RectangleShape game_window_options_button(Vector2f(200, 50));
    Text game_window_options_text("Options", buttons_font, 35);
    setButtonProperties(game_window_options_button, 255, 255, 0, 1800, 40);
    setButtonTextProperties(game_window_options_button, game_window_options_text, Color::Black);
    // Main.cpp Rectangle 
    RectangleShape edit_window_title(Vector2f(500, 80));
    Text edit_window_title_text("Main.cpp", cli_font, 35);
    setButtonProperties(edit_window_title, 110, 164, 198, 330, 85);
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
    RectangleShape main_menu_start_button(Vector2f(406, 121)), main_menu_options_button(Vector2f(323, 80));
    RectangleShape main_menu_close_button(Vector2f(230, 75));
    setButtonProperties(main_menu_start_button, 0, 128, 0, 960, 520);
    setButtonProperties(main_menu_options_button, 255, 255, 0, 960, 670);
    setButtonProperties(main_menu_close_button, 255, 0, 0, 1720, 180);
    Text main_menu_start_text("Start", buttons_font, 53), main_menu_options_text("Options", buttons_font, 40);
    Text main_menu_close_text("Close", buttons_font, 33);
    setButtonTextProperties(main_menu_start_button, main_menu_start_text, Color::Black);
    setButtonTextProperties(main_menu_options_button, main_menu_options_text, Color::Black);
    setButtonTextProperties(main_menu_close_button, main_menu_close_text, Color::Black);

    Texture main_menu_bg;
    main_menu_bg.loadFromFile("resources/sprites/main_menu_bg.png");
    Sprite main_menu(main_menu_bg);

    // Option menu
    RectangleShape mouse_cursor(Vector2f(15, 15));
    Texture slider_bar_texture, option_menu_texture, options_exit_button_texture;
    options_exit_button_texture.loadFromFile("resources/sprites/Exit.png");
    option_menu_texture.loadFromFile("resources/sprites/Option menu.png");
    slider_bar_texture.loadFromFile("resources/sprites/slide.png");
    option_menu_texture.setSmooth(true);
    options_exit_button_texture.setSmooth(true);
    Sprite slider_bar[2], option_menu, options_exit_button;
    CircleShape slider[2];
    for (int i = 0; i < 2; i++) {
        slider_bar[i].setTexture(slider_bar_texture);
        slider[i].setRadius(15);
        slider[i].setOrigin(15, 15);
    }
    option_menu.setTexture(option_menu_texture);
    options_exit_button.setTexture(options_exit_button_texture);
    option_menu.setOrigin(400, 300);
    option_menu.setPosition(WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
    options_exit_button.setPosition(option_menu.getGlobalBounds().left + 739, option_menu.getGlobalBounds().top + 16);
    optionMenu sfx_text;
    slider[0].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 414);
    slider[1].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 245);
    slider_bar[0].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 409);
    slider_bar[1].setPosition(option_menu.getGlobalBounds().left + 151, option_menu.getGlobalBounds().top + 240);
    bool change_music_volume = 0, change_sfx_volume = 0;
    setSfxTexts(sfx_text, option_menu);
    // Option menu

    // Graph
    Sprite head, smoke;
    Texture octacat, commit_textures, smoke_texture;
    octacat.loadFromFile("resources/sprites/octocat.png");
    octacat.setSmooth(true);
    commit_textures.loadFromFile("resources/sprites/commits_sprites.png");
    commit_textures.setSmooth(true);
    smoke_texture.loadFromFile("resources/sprites/smoke.png");
    smoke_texture.setSmooth(true);
    smoke.setTexture(smoke_texture);
    head.setTexture(octacat);
    head.setTextureRect(IntRect(0, 0, 200.25, 301));
    head.setScale(0.8, 0.8);
    head.setOrigin(100.125, 150.5);
    head.setPosition(200, 200);
    bool additional_commit_created = 0;
    bool window_collision_mode = 1;
    bool should_create_smoke = 0;
    unsigned short int commits_count = 0;
    const unsigned short int MAX_COMMITS = 100;
    SoundBuffer pop_buff;
    pop_buff.loadFromFile("resources/audio/pop.wav");
    Sound pop_commit;
    pop_commit.setBuffer(pop_buff);
    pop_commit.setVolume(0);
    commit commits[MAX_COMMITS];
    window.setFramerateLimit(60);

    Event event;
    while (window.isOpen())
    {
        Mouse mouse;
        Vector2i position = mouse.getPosition(window);
        Vector2f world_pos = window.mapPixelToCoords(position);
        mouse_cursor.setPosition(world_pos.x, world_pos.y);

        while (window.pollEvent(event))
        {
            if((Keyboard::isKeyPressed(Keyboard:: Insert)) && current_screen == levels_screens[current_level_screen_index])
            {
                dialogue_text.current_script_index = level[current_level_screen].new_script.size() - 1;
            }
            if((Keyboard::isKeyPressed(Keyboard:: Space)) && current_screen == "transition slide")
            {
                current_screen = levels_screens[current_level_screen_index];
                transition_level_texts_index++;
                transition_text.setString(transition_level_texts[transition_level_texts_index]);
            }
            if ((Keyboard::isKeyPressed(Keyboard::Up)) && current_screen == levels_screens[current_level_screen_index]) {
                addCommit(commits_count, commits, commit_textures, "initial commit");
                pop_commit.play();
                window_collision_mode = 0;
                should_create_smoke = 1;
                if (index_of_the_last_commit == 0)
                    head.setPosition(commits[index_of_the_last_commit].sprite.getPosition().x + 40, commits[0].sprite.getPosition().y - 100);
                else if (index_of_the_last_commit == 1) {
                    head.setPosition(commits[index_of_the_last_commit - 1].sprite.getPosition().x + (40), commits[0].sprite.getPosition().y - 100);
                    additional_commit_created = 1;
                }
                else {
                    head.setPosition(commits[index_of_the_last_commit - 1].sprite.getPosition().x + (40 + 125), commits[0].sprite.getPosition().y - 100);
                    additional_commit_created = 1;
                }
            }
            if (event.type == Event::Closed || current_screen == "close")
            {
                window.close();
            }
            // Mouse click CLI
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                if (current_screen == levels_screens[current_level_screen_index]) 
                {
                    if (game_window_back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "levels menu";
                        current_level_screen_index = 0;
                        dialogue_text.script_text.setString("");
                        dialogue_text.current_script_index = 0;
                        continuation_message.sub_script_ended = 1;
                        user_cli_input.clear();
                        final_cli_input.clear();
                        commands_entered_counter = 0;
                        dialogue_text.script_ended = 0;
                    }
                    if (game_window_next_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_level_screen_index++;
                        current_screen = levels_screens[current_level_screen_index];
                        current_level_screen++;
                        //reset the dialogues in the array of structs
                        current_screen = "transition slide";
                        dialogue_text.script_text.setString("");
                        continuation_message.sub_script_ended = 1;
                        dialogue_text.current_script_index = 0;
                        dialogue_text.script_ended = 0;
                        user_cli_input.clear();
                        final_cli_input.clear();
                        commands_entered_counter = 0;
                    }
                    if (edit_window_save_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        edit_window_changed = checkInputEquality(current_edit_window_input, old_edit_window_input, edit_window_changed);
                    }
                    if (game_window_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "options_in_game";
                    }
                    if (cli_output_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        cli_selected = true;
                    }
                    else
                    {
                        cli_selected = false;
                        show_cli_cursor = false;
                    }
                    // Mouse clicked on edit window
                    if (edit_window_shape.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        edit_window_selected = true;
                    }
                    else
                    {
                        edit_window_selected = false;
                        show_edit_window_cursor = false;
                    }
                }
                else if (current_screen == "main menu") {
                    if (main_menu_start_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "levels menu";
                    }
                    if (main_menu_options_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "options";
                    }
                    if (main_menu_close_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "close";
                    }
                }
                else if (current_screen == "levels menu") {
                    if (levels_back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = "main menu";
                    }
                    else if (intro_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_level_screen = 0;
                        current_screen = levels_screens[0];
                        current_level_screen_index = 0;
                        current_screen = "transition slide";
                    }
                    else if (init_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = levels_screens[1];
                        current_level_screen_index = 1;
                        current_level_screen = 1;
                    }
                    else if (commit_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = levels_screens[2];
                        current_level_screen_index = 2;
                        current_level_screen = 2;
                    }
                    else if (checkout_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                    {
                        current_screen = levels_screens[3];
                        current_level_screen_index = 3;
                        current_level_screen = 3;
                    }
                }
            }
            if (event.type == Event::TextEntered)
            {
                if (edit_window_selected && current_screen == levels_screens[current_level_screen_index] && level[current_level_screen].new_script[dialogue_text.current_script_index].first == 2)
                {
                    if ( (edit_window_text.findCharacterPos(current_edit_window_input.size()).y < edit_window_shape.getGlobalBounds().height))
                    {
                        // Write in edit window
                        if (isprint(event.text.unicode)){
                            current_edit_window_input += event.text.unicode;
                        }
                        
                        // Bounds for text
                        Vector2f edit_window_char_pos = edit_window_text.findCharacterPos(current_edit_window_input.size());  
                        
                        if(!((edit_window_shape.getGlobalBounds()).contains(edit_window_char_pos))){
                            char temp_last = current_edit_window_input[current_edit_window_input.size()-1];
                            char temp_before_last = current_edit_window_input[current_edit_window_input.size()-2];
                            current_edit_window_input.pop_back();
                            current_edit_window_input.pop_back();
                            current_edit_window_input += ("\n");
                            current_edit_window_input += temp_before_last;
                            current_edit_window_input += temp_last;
                        }
                    }
                    else
                        edit_window_selected = false;
                }
                // Filter out symbols (only characters in ascii code enters)
                if (cli_selected && current_screen == levels_screens[current_level_screen_index])
                    // User inputs in the cli
                    if (isprint(event.text.unicode))    
                    { 
                        user_cli_input += event.text.unicode;
                        // Bounds for the cli text
                        Vector2f cli_char_pos = cli_text.findCharacterPos(user_cli_input.size());  
                        
                        if (!(cli_output_shape.getGlobalBounds().contains(cli_char_pos)))
                        {
                            user_cli_input.pop_back();
                        }
                }
            }
            if (event.type == Event::KeyPressed) 
            {    
                if(cli_selected)
                {
                    // Delete option
                    if (event.key.code == Keyboard::BackSpace) 
                    {
                    if (!user_cli_input.empty())
                        user_cli_input.pop_back();
                    }
                    // User clicks enter and the text will be transfered at the top of the screen
                    if (event.key.code == Keyboard::Return && (!dialogue_text.script_ended) && !continuation_message.commands_flag && (!user_cli_input.empty())) 
                    {
                        if(level[current_level_screen].new_script[dialogue_text.current_script_index].first == 1)
                        // Continuation flag is used for stopping input from user after the correct command
                        {
                            if(user_cli_input == level[current_level_screen].level_commands[commands_entered_counter] || (commit_command_entered))
                                correct_command = 1;
                            else 
                                correct_command = 0;

                            if(correct_command)
                            {
                                // Commit message
                                if(commit_command_entered && level[current_level_screen].level_commands[commands_entered_counter] == "git commit")
                                {
                                    final_cli_input = "commit successful \n";
                                    commit_message = user_cli_input;
                                    user_cli_input.clear();
                                    commands_entered_counter++;
                                    correct_command = 0;
                                    commit_command_entered = 0;
                                    continuation_message.commands_flag = 1;
                                }
                                // This condition needs a follow up, each command is special
                                // So we use this if condition to adjust the uniqueness of each one
                                else if(level[current_level_screen].level_commands[commands_entered_counter] == "git commit")
                                {
                                    final_cli_input.clear();
                                    final_cli_input = (cli_commit_msg_request+'\n');
                                    commit_command_entered = 1;
                                    continuation_message.commands_flag = 0;
                                }
                                else
                                {
                                    final_cli_input += ("$ "+ user_cli_input + "\t\t\t\t\t\t correct!!!"+"\n");
                                    continuation_message.commands_flag = 1;
                                    commands_entered_counter++;   
                                    //correct_command = 0;
                                }
                            }
                            else
                            {
                                final_cli_input = user_cli_input + "\t\t\t\t\t\tincorrect command\n";   
                            }
                            user_cli_input.clear();
                        }
                    }
                }
                // Delete and enter for edit window
                if(edit_window_selected && level[current_level_screen].new_script[dialogue_text.current_script_index].first==2)
                {
                    if (event.key.code == Keyboard::BackSpace && level[current_level_screen].new_script[dialogue_text.current_script_index].first==2) 
                    {
                        if (!current_edit_window_input.empty())
                            current_edit_window_input.pop_back();
                    }
                    if (event.key.code == Keyboard::Return && level[current_level_screen].new_script[dialogue_text.current_script_index].first==2) 
                    {
                        current_edit_window_input += ("\n");
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
                    edit_window_save_button.setFillColor(Color(2, 118, 36));
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
                if (levels_back_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {
                    levels_back_button.setFillColor(Color(140, 140, 140));
                    levels_back_button.setScale(0.9f, 0.9f);
                }
                else
                {
                    levels_back_button.setFillColor(Color(46, 139, 87));
                    levels_back_button.setScale(1.0f, 1.0f);
                }
                if (init_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    init_level_button.setFillColor(Color(140, 140, 140));
                    init_level_button.setScale(0.9f, 0.9f);
                }
                else
                {
                    init_level_button.setFillColor(Color(112, 128, 144));
                    init_level_button.setScale(1.0f, 1.0f);

                }
                if (intro_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    intro_level_button.setFillColor(Color(140, 140, 140));
                    intro_level_button.setScale(0.9f, 0.9f);
                }
                else
                {
                    intro_level_button.setFillColor(Color(112, 128, 144));
                    intro_level_button.setScale(1.0f, 1.0f);

                }
                if (commit_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    commit_level_button.setFillColor(Color(140, 140, 140));
                    commit_level_button.setScale(0.92f, 0.92f);
                }
                else
                {
                    commit_level_button.setFillColor(Color(112, 128, 144));
                    commit_level_button.setScale(1.0f, 1.0f);

                }
                if (checkout_level_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    checkout_level_button.setFillColor(Color(140, 140, 140));
                    checkout_level_button.setScale(0.9f, 0.9f);
                }
                else
                {
                    checkout_level_button.setFillColor(Color(112, 128, 144));
                    checkout_level_button.setScale(1.0f, 1.0f);

                }
                if (game_window_next_button.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
                {

                    game_window_next_button.setFillColor(Color(75, 181, 67));
                    game_window_next_button.setScale(0.9f, 0.9f);
                }
                else
                {
                    game_window_next_button.setFillColor(Color(25, 135, 84));
                    game_window_next_button.setScale(1.0f, 1.0f);
                }
            }
           // Check if down arrow (later space) key has been pressed
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {        
                if (!dialogue_text.script_ended && current_screen == levels_screens[current_level_screen_index] && continuation_message.sub_script_ended && continuation_message.commands_flag == 0 && level[current_level_screen].new_script[dialogue_text.current_script_index].first == 0)
                {
                    if (level[current_level_screen].new_script[dialogue_text.current_script_index] == level[current_level_screen].new_script.back())
                    {
                        dialogue_text.script_ended = 1;
                    }    
                    // Clear the current text and reset the script content to the next string
                    dialogue_text.script_text.setString("");
                    dialogue_text.script_content = level[current_level_screen].new_script[dialogue_text.current_script_index].second;
                    dialogue_text.current_script_index++;
                }   
                else if (continuation_message.commands_flag == 1 && level[current_level_screen].new_script[dialogue_text.current_script_index].first==1)
                {
                    if(level[current_level_screen].new_script[dialogue_text.current_script_index] == level[current_level_screen].new_script.back())
                    {
                        dialogue_text.script_ended = 1;
                    }
                    //level[current_level_screen].new_script[dialogue_text.current_script_index].first = 0;
                    dialogue_text.script_text.setString("");
                    dialogue_text.script_content = level[current_level_screen].new_script[dialogue_text.current_script_index].second; 
                    dialogue_text.current_script_index++;
                    continuation_message.commands_flag = 0;
                }
                else if(edit_window_changed == 1 && level[current_level_screen].new_script[dialogue_text.current_script_index].first == 2)
                {
                    if(level[current_level_screen].new_script[dialogue_text.current_script_index] == level[current_level_screen].new_script.back())
                    {
                        dialogue_text.script_ended = 1;
                    } 
                    //level[current_level_screen].new_script[dialogue_text.current_script_index].first=0;
                    dialogue_text.script_text.setString("");
                    dialogue_text.script_content = level[current_level_screen].new_script[dialogue_text.current_script_index].second; 
                    dialogue_text.current_script_index++;
                    edit_window_changed = 0;
                }
            }
        }
        window.clear(Color(223, 221, 221));
        if (current_screen == "main menu")
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
        else if(current_screen == "transition slide"){
            window.draw(transition_slide_bg);
            window.draw(transition_text);
        }
        // Checking if it's a level screen
        else if (current_screen == levels_screens[current_level_screen_index])
        {
            drawDialogue(window, dialogue_box);
            createCliInputShape(cli_input_shape);
            createEditWindowShape(edit_window_shape);
            createCliOutputShape(cli_output_shape);
            printDialogueText(dialogue_text);
            showCursor(cursor_clock, show_cli_cursor, cli_selected, cursor_time);
            showCursor(cursor_clock, show_edit_window_cursor, edit_window_selected, cursor_time);
            setCliTexts(cli_text, cli_text_final, user_cli_input, final_cli_input, show_cli_cursor, cli_output_shape, cli_input_shape);
            showContinuationMessage(continuation_message, edit_window_changed);
            setEditWindowText(edit_window_text, current_edit_window_input, show_edit_window_cursor, edit_window_shape);
            headIdleAnimation(head, additional_commit_created);
            headBorderDeflection(head, window_collision_mode, additional_commit_created);
            moveHeadToLatestCommit(head, additional_commit_created);
            calculateHeadDistance(head, position, commits);
            headAnimationAndMovement(head);
            window.draw(dialogue_box.body_shape);
            window.draw(edit_window_shape);
            window.draw(cli_input_shape);
            window.draw(cli_output_shape);
            window.draw(dialogue_box.title_shape);
            window.draw(dialogue_box.title);
            window.draw(dialogue_box.sprite);
            window.draw(dialogue_text.script_text);
            window.draw(continuation_message.continuation_text);
            window.draw(edit_window_text);
            window.draw(cli_text);
            window.draw(edit_window_save_button);
            window.draw(edit_window_save_text);
            window.draw(cli_text_final);
            window.draw(game_window_back_button);
            window.draw(game_window_back_text);
            window.draw(game_window_options_button);
            window.draw(game_window_options_text);
            if(dialogue_text.script_ended)
            {
                window.draw(game_window_next_button);
                window.draw(game_window_next_text);
            }
            window.draw(edit_window_title);
            window.draw(edit_window_title_text);
            for (unsigned short int i = 0; i < commits_count; i++)
                window.draw(commits[i].sprite);
            window.draw(head);
            if (should_create_smoke) {
                makeSmoke(smoke, should_create_smoke);
                window.draw(smoke);
            }
        }
        else if (current_screen == "options")
        {
            controlOptionsExitButton(options_exit_button, mouse_cursor, option_menu);
            controlSfxTexts(sfx_text, mouse_cursor, pop_commit, event);
            controlSfxAndMusicVolume(sfx_text, music, pop_commit, slider_bar, slider, option_menu, mouse_cursor, event, change_sfx_volume, change_music_volume);
            setSliderMoveLimits(slider_bar, slider);
            window.draw(main_menu);
            window.draw(option_menu);
            for (int i = 0; i < 2; i++)
                window.draw(slider[i]);;
            window.draw(sfx_text.text);
            window.draw(options_exit_button);
        }
        else if (current_screen == "options_in_game")
        {
            controlOptionsExitButton(options_exit_button, mouse_cursor, option_menu);
            controlSfxTexts(sfx_text, mouse_cursor, pop_commit, event);
            controlSfxAndMusicVolume(sfx_text, music, pop_commit, slider_bar, slider, option_menu, mouse_cursor, event, change_sfx_volume, change_music_volume);
            setSliderMoveLimits(slider_bar, slider);
            drawDialogue(window, dialogue_box);
            createCliInputShape(cli_input_shape);
            createEditWindowShape(edit_window_shape);
            createCliOutputShape(cli_output_shape);
            headIdleAnimation(head, additional_commit_created);
            window.draw(dialogue_box.body_shape);
            window.draw(edit_window_shape);
            window.draw(cli_input_shape);
            window.draw(cli_output_shape);
            window.draw(dialogue_box.title_shape);
            window.draw(dialogue_box.title);
            window.draw(dialogue_box.sprite);
            window.draw(dialogue_text.script_text);
            window.draw(continuation_message.continuation_text);
            window.draw(edit_window_text);
            window.draw(cli_text);
            window.draw(cli_text_final);
            window.draw(edit_window_title);
            window.draw(edit_window_title_text);
            for (unsigned short int i = 0; i < commits_count; i++)
                window.draw(commits[i].sprite);
            window.draw(head);
            window.draw(option_menu);
            for (int i = 0; i < 2; i++)
                window.draw(slider[i]);;
            window.draw(sfx_text.text);
            window.draw(options_exit_button);
        }
        else if (current_screen == "levels menu") {
            window.draw(levels_menu_bg);
            window.draw(levels_back_button);
            window.draw(level_buttons_bg);
            window.draw(intro_level_button);
            window.draw(init_level_button);
            window.draw(commit_level_button);
            window.draw(checkout_level_button);
            window.draw(levels_back_button_text);
            window.draw(intro_levels_category);
            window.draw(commits_levels_category);
            window.draw(intro_level_text);
            window.draw(init_level_text);
            window.draw(commit_level_text);
            window.draw(checkout_level_text);
        }
        window.setView(view);
        window.display();
    }
}

void drawDialogue(RenderWindow& window, dialogueBox& dialogue_box)
{
    //Dialogue box (big)
    dialogue_box.body_shape.setSize(Vector2f(900, 260));
    dialogue_box.body_shape.setFillColor(Color(44, 240, 83));
    dialogue_box.body_shape.setOutlineThickness(5);
    dialogue_box.body_shape.setOutlineColor(Color::Black);
    dialogue_box.body_shape.setPosition(80, 700);

    //Dialogue box (small)
    dialogue_box.title_shape.setSize(Vector2f(900, 65));
    dialogue_box.title_shape.setFillColor(Color(95, 219, 120));
    dialogue_box.title_shape.setOutlineThickness(0.8f);
    dialogue_box.title_shape.setOutlineColor(Color(72, 84, 74));
    dialogue_box.title_shape.setPosition(80, 700);

    //Sprite
    dialogue_box.sprite.setTexture(dialogue_box.texture);
    dialogue_box.sprite.setScale(0.8, 0.8);
    dialogue_box.sprite.setPosition(15, 630);

    //Title
    dialogue_box.title.setString(dialogue_box.title_content);
    dialogue_box.title.setFont(dialogue_box.font);
    dialogue_box.title.setFillColor(Color(57, 60, 58));
    dialogue_box.title.setStyle(Text::Italic);
    dialogue_box.title.setCharacterSize(dialogue_box.title_size);
    dialogue_box.title.setPosition(220, 720);
}

void showContinuationMessage(continuationMessage& continuation_message, bool& edit_window_changed) 
{
    continuation_message.continuation_fade_time += continuation_message.continuation_fade_clock.restart();
    if(continuation_message.continuation_fade_time >= seconds(continuation_message.continuation_delay))
    {
        continuation_message.continuation_message_running =! continuation_message.continuation_message_running;
        continuation_message.continuation_fade_time = Time::Zero;
    }
    if(!dialogue_text.script_ended && continuation_message.sub_script_ended && (level[current_level_screen].new_script[dialogue_text.current_script_index].first==0 || continuation_message.commands_flag ==1|| edit_window_changed==1))
    {
        continuation_message.continuation_text.setString((continuation_message.continuation_message_running ? continuation_message.continuation_content : ""));
        continuation_message.continuation_text.setFont(continuation_message.font);
        continuation_message.continuation_text.setFillColor(Color(57,60,58));
        continuation_message.continuation_text.setCharacterSize(24);
        continuation_message.continuation_text.setStyle(Text::Italic);
        continuation_message.continuation_text.setPosition(670, 925);
    }
    else if (!continuation_message.sub_script_ended)
    {
        continuation_message.continuation_text.setFillColor(Color::Transparent);
    }
}

void printDialogueText(dialogueText& dialogue_text)
{
    dialogue_text.script_text.setFont(dialogue_text.font);
    dialogue_text.script_text.setFillColor(dialogue_text.color);
    dialogue_text.script_text.setCharacterSize(dialogue_text.size);
    dialogue_text.script_text.setPosition(250, 780);
    //dialogue_text.script_text.setStyle(Text::Bold);
    dialogue_text.time += dialogue_text.typewrite_clock.restart();
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
                continuation_message.sub_script_ended = 1;
            }
            else
            {
                continuation_message.sub_script_ended = 0;
            }
        }
    }
}

void showCursor(Clock& cursor_clock, bool& show_cursor, bool& selected, Time& cursor_time) {
    if (selected)
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

void setTextOriginAndPosition(Text& text, float x_position, float y_position) {
    text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2, text.getLocalBounds().top + text.getLocalBounds().height / 2);
    text.setPosition(x_position, y_position);
}

void setButtonProperties(RectangleShape& rectangle, int red_intensity, int green_intensity, int blue_intensity, float x_position, float y_position)
{
    rectangle.setFillColor(Color(red_intensity, green_intensity, blue_intensity));
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(Color::Black);
    rectangle.setOrigin(rectangle.getSize() / 2.f);
    rectangle.setPosition(x_position, y_position);
    rectangle.setOutlineThickness(5);
    rectangle.setOutlineColor(Color::Black);
}

void setSfxTexts(optionMenu& sfx_text, Sprite& option_menu) {
    sfx_text.font.loadFromFile(sfx_text.option_font_type);
    sfx_text.text.setFont(sfx_text.font);
    sfx_text.text.setString("SFX");
    sfx_text.text.setFillColor(Color::White);
    sfx_text.text.setCharacterSize(sfx_text.size);
    sfx_text.text.setPosition(option_menu.getGlobalBounds().left + 357, option_menu.getGlobalBounds().top + 321);
}

void controlOptionsExitButton(Sprite& options_exit_button, RectangleShape& mouse_cursor, Sprite& option_menu) {
    if (options_exit_button.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()))
    {
        options_exit_button.setColor(Color::Red);
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (current_screen == "options_in_game")
            {
                current_screen = levels_screens[current_level_screen_index];
            }
            else if (current_screen == "options")
            {
                current_screen = "main menu";
            }
        }
    }
    else
        options_exit_button.setColor(Color::White);
}

void controlSfxTexts(optionMenu& sfx_text, RectangleShape& mouse_cursor, Sound& pop, Event& event) {
    if (sfx_text.text.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()))
        sfx_text.text.setFillColor({ 50, 50, 50 });
    else
        sfx_text.text.setFillColor(Color::Black);
    if (sfx_text.text.getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (Mouse::isButtonPressed(Mouse::Left))) {
        pop.play();
    }
}

void setSliderMoveLimits(Sprite slider_bar[], CircleShape slider[]) {
    if (slider[0].getPosition().x < slider_bar[0].getGlobalBounds().left)
        slider[0].setPosition(slider_bar[0].getGlobalBounds().left, slider[0].getPosition().y);
    if (slider[0].getPosition().x > (slider_bar[0].getGlobalBounds().left + 499))
        slider[0].setPosition(slider_bar[0].getGlobalBounds().left + 499, slider[0].getPosition().y);
    if (slider[1].getPosition().x < slider_bar[1].getGlobalBounds().left)
        slider[1].setPosition(slider_bar[1].getGlobalBounds().left, slider[1].getPosition().y);
    if (slider[1].getPosition().x > (slider_bar[1].getGlobalBounds().left + 499))
        slider[1].setPosition(slider_bar[1].getGlobalBounds().left + 499, slider[1].getPosition().y);
}

// This function is designed to adjust the volume of the slider based on its X-coordinate within the slider bar
// As the X-coordinate increases, the volume will also increase accordingly.
void controlSfxAndMusicVolume(optionMenu& sfx_text, Music& music, Sound& pop_commit, Sprite slider_bar[], CircleShape slider[], Sprite& option_menu, RectangleShape& mouse_cursor, Event& event, bool& change_sfx_volume, bool& change_music_volume) {
    if (slider_bar[0].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (event.type == Event::MouseButtonPressed))
        change_sfx_volume = 1;
    if (slider_bar[1].getGlobalBounds().intersects(mouse_cursor.getGlobalBounds()) && (event.type == Event::MouseButtonPressed))
        change_music_volume = 1;
    if (event.type == Event::MouseButtonReleased && change_music_volume)
        change_music_volume = 0;
    if (event.type == Event::MouseButtonReleased && change_sfx_volume)
        change_sfx_volume = 0;
    if (change_sfx_volume) {
        slider[0].setPosition(mouse_cursor.getPosition().x, slider[0].getPosition().y);
        pop_commit.setVolume(((slider[0].getPosition().x - (slider_bar[0].getGlobalBounds().left)) * 100) / (option_menu.getGlobalBounds().left + 499));
        change_music_volume = 0;

    }
    if (change_music_volume) {
        slider[1].setPosition(mouse_cursor.getPosition().x, slider[1].getPosition().y);
        music.setVolume(((slider[1].getPosition().x - (slider_bar[1].getGlobalBounds().left)) * 100) / (option_menu.getGlobalBounds().left + 499));
        change_sfx_volume = 0;
    }
}


void setCliTexts(Text& cli_text, Text& cli_text_final, string& user_cli_input, string final_cli_input, bool& show_cursor, RectangleShape& rectangle, RectangleShape& rectangle_upper) {
    // Shape of cursor
    cli_text.setString(user_cli_input + (show_cursor ? '|' : ' ')); 
    cli_text.setPosition(rectangle.getPosition().x+7, rectangle.getPosition().y+7);
    cli_text_final.setFillColor(Color::White);
    cli_text_final.setString(final_cli_input);
    cli_text_final.setPosition(rectangle_upper.getPosition().x+7, rectangle_upper.getPosition().y+7);
   // cout<<user_cli_input<<'\n'<<final_cli_input;
}

void setEditWindowText(Text& edit_text, string& edit_input, bool& show_cursor, RectangleShape& rectangle) {
    edit_text.setString(edit_input + (show_cursor ? '|' : ' '));
    edit_text.setPosition(rectangle.getPosition().x + 7, rectangle.getPosition().y + 90);
    edit_text.setFillColor(Color::White);
}

void createEditWindowShape(RectangleShape& form) {
    form.setSize(Vector2f(500, 600));
    form.setFillColor(Color(0, 116, 185));
    form.setOutlineThickness(8);
    form.setOutlineColor(Color::Black);
    form.setPosition(80, 45);
}

void createCliOutputShape(RectangleShape& form) {
    form.setSize(Vector2f(650, 60));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200, 900);
}

void createCliInputShape(RectangleShape& form) {
    form.setSize(Vector2f(650, 200));
    form.setFillColor(Color::Black);
    form.setOutlineThickness(5);
    form.setOutlineColor(Color(241, 196, 15));
    form.setPosition(1200, 700);
}

void makeSmoke(Sprite& smoke, bool& should_create_smoke) {
    smoke.setScale(0.2, 0.2);
    smoke.setTextureRect(IntRect(current_smoke_animation_frame * 1380.571428571429, 0, 1380.571428571429, 2000.000));
    smoke.setPosition(WINDOW_WIDTH / 2.0 - 90 + 800, WINDOW_HEIGHT / 3.0 - 170);
    graph_smoke_animation_delay++;
    if (graph_smoke_animation_delay >= 3) {
        current_smoke_animation_frame++;
        graph_smoke_animation_delay = 0;
    }
    if (current_smoke_animation_frame > 6) {
        current_smoke_animation_frame = 0;
        should_create_smoke = 0;
    }
}

void addCommit(unsigned short int& commits_count, commit commits[], Texture& commit_textures, string commit_message) {
    // All the following are the same for both conditions
    Sprite commit_sprite;
    commit_sprite.setColor({ 43, 45, 47 });
    commit_sprite.setTexture(commit_textures);
    const float COMMIT_SCALING = 0.5;
    commit_sprite.scale(Vector2f(COMMIT_SCALING, COMMIT_SCALING));

    if (commits_count == 0)
    {
        // I cut from the texture a circle *without* an arrow
        commit_sprite.setTextureRect(IntRect(287, 70, 156, 156));
        commit_sprite.setPosition(WINDOW_WIDTH / 2.0 + 800, WINDOW_HEIGHT / 3.0);
    }
    else
    {
        const unsigned short int CIRCLE_LENGTH = 60;
        const unsigned short int ARROW_LENGTH = 125;
        for (unsigned short int i = 0; i < commits_count; i++)
        {
            commits[i].sprite.move(Vector2f(-(CIRCLE_LENGTH + ARROW_LENGTH), 0));
            index_of_the_last_commit = commits_count;
        }
        // I cut from the texture a circle *with* an arrow
        commit_sprite.setTextureRect(IntRect(37, 278, 406, 432));
        commit_sprite.setPosition(1920 / 2 - ARROW_LENGTH + 800, 1080 / 3);
    }

    commit new_commit = { commit_message, commit_sprite };
    commits[commits_count] = new_commit;
    commits_count++;
}
void moveHeadToLatestCommit(Sprite& head, bool& additional_commit_created) {
    if (additional_commit_created)
    {
        graph_head.latest_commit_movement_delay++;
        if (graph_head.distance_to_latest_commit > 0 && graph_head.latest_commit_movement_delay >= 10)
        {
            head.setTextureRect(IntRect(2 * 200.25, 0, 200.25, 301));
            head.move(5, 0);
            graph_head.distance_to_latest_commit -= 5;
        }
        if (graph_head.distance_to_latest_commit <= 0) {
            graph_head.distance_to_latest_commit = (50 + 135);
            additional_commit_created = 0;
            graph_head.latest_commit_movement_delay = 0;
        }
    }
}

void headBorderDeflection(Sprite& head, bool& window_collision_mode, bool& additional_commit_created) {
    if (!additional_commit_created)
    {
        head.setTextureRect(IntRect(graph_head.current_animation_frame * 200.25, 0, 200.25, 301));
        if (window_collision_mode) {
            head.setPosition(head.getPosition().x + graph_head.x_border_deflection_velocity, head.getPosition().y + graph_head.y_border_deflection_velocity);
            if (head.getPosition().x < (0 + 50 * 0.8) || head.getPosition().x >(WINDOW_WIDTH - (50 * 0.8)))
                graph_head.x_border_deflection_velocity *= -1;
            if (head.getPosition().y < (0 + 100 * 0.8) || head.getPosition().y >(WINDOW_HEIGHT - (100 * 0.8)))
                graph_head.y_border_deflection_velocity *= -1;
        }
    }
}
void headIdleAnimation(Sprite& head, bool& additional_commit_created) {
    if (!additional_commit_created) {
        head.setTextureRect(IntRect(graph_head.current_animation_frame * 200.25, 0, 200.25, 301));
        graph_head.idle_animation_delay++;
        if (graph_head.idle_animation_delay >= 20) {
            graph_head.current_animation_frame++;
            graph_head.idle_animation_delay = 0;
        }
        if (graph_head.current_animation_frame == 2)
            graph_head.current_animation_frame = 0;
    }
}

void calculateHeadDistance(Sprite& head, Vector2i& position_of_mouse, commit commit[])
{
    for (short int i = 0; i < 100; i++)
    {
        if (commit[i].sprite.getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) && (Mouse::isButtonPressed(Mouse::Left))) {
            if (i == 0 && head.getPosition().x - commit[i].sprite.getPosition().x < 0) {
                graph_head.distance_to_checkout_commit = head.getPosition().x - commit[i].sprite.getPosition().x - 40;
            }
            else if (i == 0 && head.getPosition().x - commit[i].sprite.getPosition().x > 0)
            {
                graph_head.distance_to_checkout_commit = head.getPosition().x - commit[i].sprite.getPosition().x - 40;
            }
            else if (i != 0 && head.getPosition().x - commit[i].sprite.getPosition().x > 0)
            {
                graph_head.distance_to_checkout_commit = head.getPosition().x - commit[i].sprite.getPosition().x - (40 + 125);
            }
            else if (i != 0 && head.getPosition().x - commit[i].sprite.getPosition().x < 0)
            {
                graph_head.distance_to_checkout_commit = head.getPosition().x - commit[i].sprite.getPosition().x - (40 + 125);
            }
        }
    }
}

void headAnimationAndMovement(Sprite& head) {
    if (graph_head.distance_to_checkout_commit < 0)
    {
        head.move(5, 0);
        head.setTextureRect(IntRect(2 * 200.25, 0, 200.25, 301));
        graph_head.distance_to_checkout_commit += 5;
    }
    else if (graph_head.distance_to_checkout_commit > 0)
    {
        head.move(-5, 0);
        head.setTextureRect(IntRect(3 * 200.25, 0, 200.25, 301));
        graph_head.distance_to_checkout_commit -= 5;
    }
}

bool checkInputEquality(string& input, string& correct_string ,bool& edit_window_changed ){
    if(input != correct_string || (edit_window_changed==1 && (input == correct_string)))
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