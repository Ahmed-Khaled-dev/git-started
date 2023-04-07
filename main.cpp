#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

/** note that some variables should be in the while(window.isOpen()) loop because it needs to be updated */

int p1 = 0, delay = 0;
ContextSettings Settings;
RenderWindow window(VideoMode(1920, 1080), "GitStarted", sf::Style::Default, Settings);


void respawning_commits_and_get_its_postion(CircleShape commit[])
{
    for (int i = 1; i <= 4; i++)
    {
        commit[i].setRadius(30);
        commit[i].setFillColor(Color::Black);
        commit[i].setOrigin(30, 30);
        commit[i].setPosition(149 * (i + i), 413);
        

    }
        
}


bool commits_condtions(Vector2i& postion, CircleShape commit[])
{
    for (int i = 0; i < 5; i++)
    {
        if (commit[i].getGlobalBounds().contains(Vector2f(postion.x, postion.y))) {
            return true;
        }
    }
    
}


void sprite_animation_and_position(Sprite& head, Vector2i& position_of_head, CircleShape commit[], bool& clicked)
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
    for (size_t i = 0; i < 5; i++)
    {
        CircleShape la(25);
        la.setPosition(0, 0);
        la.setFillColor(Color::Black);
        if (commit[i].getGlobalBounds().contains(Vector2f(position_of_head.x, position_of_head.y)) && clicked) {
            head.setPosition(commit[i].getPosition().x, commit[i].getPosition().y - 130);
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
    bool clicked;
    octacat.setSmooth(true);
    respawning_commits_and_get_its_postion(commit);
    
    // 3  variables for getting the mainmenu cords




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
       
        cout << position.x << '\t' << position.y << endl;

        sprite_animation_and_position(head, position, commit, clicked);

        

        window.clear(Color :: White);
        window.draw(head);
        for (int i = 0; i < 5; i++)
            window.draw(commit[i]);
        window.display();
        
    }
    return 0;
}