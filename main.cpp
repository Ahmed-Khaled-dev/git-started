#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void PLAY_MUSIC_FROM_FILE(const std::string& filePath, sf::Music& music); //function to play music

int main() {

    sf::Music music;

    PLAY_MUSIC_FROM_FILE( "audio/lepo.wav", music);/* 1-path of the music is written as a spring 
    2- mp3 require licence 3-i made it to accept the music as an argument to be able to view it inside the function  */
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == Keyboard::Key::Space) {
                    if (music.getStatus() == sf::SoundSource::Status::Playing) {
                        music.pause(); //if music is being played --> pause it
                    }
                    else if (music.getStatus() == sf::SoundSource::Status::Paused) {
                        music.play(); //if music is paused --> play it

                    }
                }
                if (event.key.code == Keyboard::Key::Escape) {
                    music.stop(); // way to close the music
                }
                 if (event.key.code == sf::Keyboard::Key::Up) {  //volume can be from(0 to 1) 0 --> muted 1 --> the oringinal volume
                    music.setVolume(music.getVolume() + 10); //new volume = old volume +10%
                
                }
                if (event.key.code == sf::Keyboard::Key::Down) { //new volume = old volume -10%
                    music.setVolume(music.getVolume() - 10);
               
                }
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
void PLAY_MUSIC_FROM_FILE(const std::string& filePath, sf::Music& music) {

    if (!music.openFromFile(filePath)) {
        cout << "error";
    }
    music.setLoop(true);
    music.play();
}