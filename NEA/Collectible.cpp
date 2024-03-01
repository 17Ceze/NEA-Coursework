#include "Collectible.h"

void Collectible::initVariables()
{
	this->animationStates = animationStates::Untaken;
}

void Collectible::initTexture()
{
	//lLoad a texture
	if (!this->textureSheet.loadFromFile("Sprites and Textures/Strawberry.png"))
	{
		std::cout << "Failed";
	}

}

void Collectible::initSprite()
{
	//Set the texture to the sprite

	this->sprite.setTexture(this->textureSheet);

	//Resize the sprite
	this->sprite.scale(3.f, 3.f);
	this->currentFrame = sf::IntRect(0, 0, 34, 32);
	this->sprite.setTextureRect(this->currentFrame);

	
}

void Collectible::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->currentFrame.left = 0.f;
}

Collectible::Collectible()
{
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Collectible::~Collectible()
{

}

const sf::Vector2f Collectible::getPosition() const
{
	return this->sprite.getPosition();;
}

const sf::FloatRect Collectible::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Collectible::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Collectible::update()
{

}

const bool& Collectible::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void Collectible::resetAnimationTImer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Collectible::updateAnimations()
{
	if (this->animationStates == animationStates::Untaken)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 32.f;
			if (this->currentFrame.left >= 544.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else
	{
		this->animationTimer.restart();
	}
}

void Collectible::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
