#pragma once
#include "Precomp.h"

enum buttonStates{Nothing = 0, Pressed, Hover};

class Button
{
private:
	short buttonState;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	

	sf::Color idleColour;
	sf::Color hoverColour;
	sf::Color activeColour;

	sf::Sound buttonSound;
	sf::SoundBuffer buttonSoundBuffer;

public:
	Button(float x, float y, float width, float height, 
		sf::Font* font, std::string text, 
		sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour);
	~Button();

	//Accessors 
	const bool isPressed() const;


	//Functions
	void update(sf::Vector2f mousePos);
	void render(sf::RenderTarget& target);

};

