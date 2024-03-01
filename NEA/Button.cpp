#include "Button.h"

Button::Button(float x, float y, float width, float height, 
	sf::Font* font, std::string text, 
	sf::Color idleColour, sf::Color hoverColour, sf::Color activeColour)
{
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	
	this->buttonState = Nothing;
	
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(12);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2.f  - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColour = idleColour;
	this->activeColour = activeColour;
	this->hoverColour = hoverColour;

	if (!this->buttonSoundBuffer.loadFromFile("Sprites and Textures/Button Sound.mp3"))
	{
		std::cout << "Failed";
	}
	this->buttonSound.setBuffer(this->buttonSoundBuffer);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (this->buttonState == Pressed)
		return true;

	return false;
}

void Button::update(sf::Vector2f mousePos)
{
	//Update the bool for pressed and hover
	
	this->buttonState = Nothing;

	//Hover


	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = Hover;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonSound.play();
			this->buttonState = Pressed;
		}
	}

	switch (this->buttonState)
	{
	case Nothing:
		this->shape.setFillColor(this->idleColour);
		break;
	case Hover:
		this->shape.setFillColor(this->hoverColour);
		break;
	case Pressed:
		this->shape.setFillColor(this->activeColour);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
