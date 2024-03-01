#include "LevelEnd.h"

void LevelEnd::initVariables()
{
	this->animationStates = levelEndState::Touched;
}

void LevelEnd::initTexture()
{
	//lLoad a texture
	if (!this->textureSheet.loadFromFile("Sprites and Textures/End (Idle).png"))
	{
		std::cout << "Failed";
	}

}

void LevelEnd::initSprite()
{
	//Set the texture to the sprite

	this->sprite.setTexture(this->textureSheet);

	//Resize the sprite
	this->sprite.scale(1.f, 1.f);
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->sprite.setTextureRect(this->currentFrame);


}

void LevelEnd::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->currentFrame.left = 0.f;
}

LevelEnd::LevelEnd()
{
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

LevelEnd::~LevelEnd()
{

}

const sf::Vector2f LevelEnd::getPosition() const
{
	return this->sprite.getPosition();;
}

const sf::FloatRect LevelEnd::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void LevelEnd::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void LevelEnd::update()
{

}

const bool& LevelEnd::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

void LevelEnd::resetAnimationTImer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void LevelEnd::updateAnimations()
{
	/*if (this->animationStates == levelEndState::Touched)
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
	*/
}

void LevelEnd::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
