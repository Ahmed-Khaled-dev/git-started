#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

struct commit{
    string message;
    CircleShape circle;
};

void addCommit(int &commits_count, commit commits[], string commit_message, int window_length, int window_width);

const int WINDOW_LENGTH = 1920, WINDOW_WIDTH = 1080;
const string GAME_TITLE = "Git Started";

RenderWindow window(VideoMode(WINDOW_LENGTH, WINDOW_WIDTH), GAME_TITLE);

int main(){

    int commits_count = 0;
    const int MAX_COMMITS = 100;

    commit commits[MAX_COMMITS];

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                addCommit(commits_count, commits, "initial commit", WINDOW_LENGTH, WINDOW_WIDTH);
            }
        }
        window.clear(Color::Black);
        for (int i = 0; i < commits_count; i++)
        {
            window.draw(commits[i].circle);
        }
        window.display();
    }

    return 0;
}

void addCommit(int &commits_count, commit commits[], string commit_message, int window_length, int window_width){
    if (commits_count == 0)
    {
        CircleShape circle(25.f);
        circle.setFillColor(Color::Red);
        circle.setPosition(window_length/2, window_width/3);
        //circle.setPointCount(1000000);

        commit new_commit = {commit_message, circle};
        commits[commits_count] = new_commit;
        commits_count++;
    }
    else
    {
        // Push the old commit $x to the left, then add a new commit in the middle of the screen
        // Then add an arrow that points from the new commit to the old commit
    }
}