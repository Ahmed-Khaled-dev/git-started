#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

/** note that some variables should be in the while(window.isOpen()) loop because it needs to be updated */

int p1 = 0, delay = 0;


void respawning_commits_and_get_its_postion(CircleShape commit[])
{
    for (int i = 1; i <= 4; i++)
    {
        commit[i].setRadius(30);
        commit[i].setFillColor(Color::Black);
        commit[i].setOrigin(30, 30);
        commit[i].setPosition(149 * (i) * 2, 413);

    }
        
}


void sprite_animation_and_position(Sprite& head, Vector2i& position_of_mouse, CircleShape commit[], bool& clicked, int& move)
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
    for (int i = 0; i < 5; i++)
    {

        bool contained = commit[i].getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) ;
        if ( clicked) {
            move = 50;
        }
        cout << head.getPosition().x - commit[1].getPosition().x  << '\t' <<move<<endl;
        if (commit[i].getGlobalBounds().contains(Vector2f(position_of_mouse.x, position_of_mouse.y)) && move){
            if(head.getPosition().x - commit[i].getPosition().x < 0){
                head.setTextureRect(IntRect(2 * 200.25, 0, 200.25, 301));
                head.move(7.0, 0);}
            else if (head.getPosition().x - commit[i].getPosition().x > 0){
                 head.setTextureRect(IntRect(3 * 200.25, 0, 200.25, 301));
                head.move(-7.0, 0);}
            else if (abs(head.getPosition().x - commit[i].getPosition().x) <=6){
                move = 0;
                }
            
        }
    }

}

int main()
{
    ContextSettings Settings;
    Settings.antialiasingLevel = 18;
    RenderWindow window(VideoMode(1920, 1080), "GitStarted", Style::Default, Settings);
    //all the needed variables
    RectangleShape line(Vector2f(150, 5));
    window.setFramerateLimit(60);
    CircleShape commit[5];
    Sprite head;
    Texture octacat;
    octacat.loadFromFile("octocat.png");
    octacat.setSmooth(true);
    head.setTexture(octacat);
    head.setTextureRect(IntRect(0, 0, 200.25, 301));
    head.setScale(0.8, 0.8);
    head.setOrigin(100.125, 150.5);
    head.setPosition(0, 200);
    bool clicked, move_right = false, move_left = false;
    octacat.setSmooth(true);
    respawning_commits_and_get_its_postion(commit);
    int move = 0;
    // 3  variables for getting the mainmenu cordssetting




    while (window.isOpen())
    {
        Mouse mouse;
        clicked = Mouse::isButtonPressed(Mouse::Left);
        Vector2i position = mouse.getPosition(window);
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
       
        sprite_animation_and_position(head, position, commit, clicked, move);

        

        window.clear(Color :: White);
        window.draw(head);
        for (int i = 0; i < 5; i++)
            window.draw(commit[i]);
        window.display();
        
    }
    return 0;
}