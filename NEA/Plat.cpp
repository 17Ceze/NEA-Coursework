#include "Plat.h"

void Plat::initVariables()
{
	
}

void Plat::initTexture()
{
	//lLoad a texture
	if (!this->textureSheet.loadFromFile("Sprites and Textures/grass tile 2.png"))
	{
		std::cout << "Failed";
	}

}

void Plat::initSprite()
{
	//Set the texture to the sprite

	this->sprite.setTexture(this->textureSheet);

	//Resize the sprite
	this->sprite.scale(3.f, 3.f);
	this->spriteFrame = sf::IntRect(0, 0, 32, 32);



}



Plat::Plat()
{
	this->initTexture();
	this->initSprite();
}

Plat::~Plat()
{

}

const sf::Vector2f Plat::getPosition() const
{
	return this->sprite.getPosition();;
}

const sf::FloatRect Plat::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Plat::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Plat::update()
{

}



void Plat::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
