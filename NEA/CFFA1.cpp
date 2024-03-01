#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

int main()
{
	//Window Creation
	sf::RenderWindow window(sf::VideoMode(650, 480), "CFFA Window", sf::Style::Titlebar | sf::Style::Close);
	sf::Event ev;

	//Game Loop
	while (window.isOpen())
	{
		//Event Polling 
		while (window.pollEvent(ev)
		{
			switch (ev.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (ev.keycode == sf::Keyboard:Escape)
					window.close();
				break;
			}
		}
		
		//Update


		//Render
		window.clear(sf::Color::Green;

		//Draw Game	

		window.display();


	}

	return 0;
}