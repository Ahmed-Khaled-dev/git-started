#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
using namespace sf;



void history_or_saved_progress(Text& text);

int main() {

	RenderWindow window(VideoMode(800, 600), "Git");
	Event event;
	Text text;
	Font font;
	font.loadFromFile("Creepster.ttf");
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setCharacterSize(50);
	
	while (window.isOpen())
	{
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		history_or_saved_progress(text);

		window.clear(Color::White);
		window.draw(text);
		window.display();

	}
}




void history_or_saved_progress(Text& text) {
	fstream infile;
	infile.open("History.txt", ios::in);
	vector <string> lines;
	string line;
	while (getline(infile, line, '*')) {
		lines.push_back(line);
	}
	text.setString(lines[0]);
}