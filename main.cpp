#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

struct commit{
    string message;
    Sprite sprite;
};

void addCommit(int &commits_count, commit commits[], Texture& commit_textures, string commit_message, int window_length, int window_width);

const int WINDOW_X = 1600, WINDOW_Y = 1000;
const string GAME_TITLE = "Git Started";

RenderWindow window(VideoMode(WINDOW_X, WINDOW_Y), GAME_TITLE);

int main(){

    int commits_count = 0;
    const int MAX_COMMITS = 100;

    commit commits[MAX_COMMITS];

    Texture commit_textures;
    if (!commit_textures.loadFromFile("resources/sprites/commits_sprites.png"))
    {
        cout << "Error loading commit sprites" << endl;
    }
    commit_textures.setSmooth(true);

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
                addCommit(commits_count, commits, commit_textures, "initial commit", WINDOW_X, WINDOW_Y);
            }
        }
        window.clear({43, 45, 47});
        for (int i = 0; i < commits_count; i++)
        {
            window.draw(commits[i].sprite);
            //cout << "Commit number " << i << " X-position -> " << commits[i].sprite.getPosition().x << endl;
        }
        window.display();
    }

    return 0;
}

void addCommit(int& commits_count, commit commits[], Texture& commit_textures, string commit_message, int window_length, int window_width){
    // All the following are the same for both conditions
    Sprite commit_sprite;
    commit_sprite.setTexture(commit_textures);
    commit_sprite.scale(Vector2f(0.5, 0.5));
    //commit_sprite.setColor({241, 80, 47});
    if (commits_count == 0)
    {
        // I cut from the texture a circle **without** an arrow
        commit_sprite.setTextureRect(IntRect(287, 70, 156, 156)); 
        commit_sprite.setPosition(window_length/2, window_width/3);
    }
    else
    {
        const int circle_length = 60;
        const int arrow_length = 125;
        for (int i = 0; i < commits_count; i++)
        {
            commits[i].sprite.move(Vector2f(-(circle_length + arrow_length), 0));
        }
        // I cut from the texture a circle **with** an arrow
        commit_sprite.setTextureRect(IntRect(37, 278, 406, 432));
        commit_sprite.setPosition(window_length/2 - arrow_length, window_width/3);
    }

    commit new_commit = {commit_message, commit_sprite};
    commits[commits_count] = new_commit;
    commits_count++;
}