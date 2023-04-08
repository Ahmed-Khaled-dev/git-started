#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void playMusicFromFile(string file_path, Music& music); //function to play music

const int window_width =1000;
const int window_height =1000;
const string window_name="git started";

int main() {

    Music music;

    playMusicFromFile( "audio/lepo.wav", music);/* 1-path of the music is written as a string 
    2- mp3 require licence (i tried to play mp3 files alot of time and it failed and found out that it require some soet of licence 
    but you can change the file type using Audacity)
    * 3-i made it to accept the music as an argument to be able to view it inside the function  */
    
    RenderWindow window( VideoMode(window_width, window_height), window_name);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Space) {
                    if (music.getStatus() == sf::SoundSource::Status::Playing) {
                        music.pause(); //if music is being played --> pause it
                    }
                    else if (music.getStatus() == SoundSource::Status::Paused) {
                        music.play(); //if music is paused --> play it

                    }
                }
                if (event.key.code == Keyboard::Key::Escape) {
                    music.stop(); // way to close the music
                }
                 if (event.key.code == Keyboard::Key::Up) {  //volume can be from(0 to 1) 0 --> muted 1 --> the oringinal volume
                    music.setVolume(music.getVolume() + 10); //new volume = old volume +10%
                
                }
                if (event.key.code == Keyboard::Key::Down) { //new volume = old volume -10%
                    music.setVolume(music.getVolume() - 10);
               
                }
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
void playMusicFromFile(const string file_path, Music& music) {

    if (!music.openFromFile(file_path)) {
        cout << "error";
    }
    music.setLoop(true);
    music.play();
}