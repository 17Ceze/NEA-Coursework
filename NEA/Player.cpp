#include "Player.h"

void Player::initVariables()
{
	this->animationStates = PLAYER_ANIMATION_STATES::Idle;
}


void Player::initTexture()
{
		//lLoad a texture
		if (!this->textureSheet.loadFromFile("Sprites and Textures/Kim Pine Full Sprite Sheet 3.png"))
		{
			std::cout << "Failed";
		}

		//Load a sound
		if (!this->pJumpingSound.loadFromFile("Sprites and Textures/Jump Sound.mp3"))
		{
			std::cout << "Failed";
		}
		this->jumpingSound.setBuffer(this->pJumpingSound);
}

void Player::initSprite()
{
	//Set the texture to the sprite

	this->sprite.setTexture(this->textureSheet);

	//Resize the sprite
	this->sprite.scale(1.f, 1.f);
	this->currentFrame = sf::IntRect(0, 0 , 48, 95);
	this->sprite.setTextureRect(this->currentFrame);
}

void Player::initAnimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
	this->currentFrame.left = 0.f;

}

void Player::initPhysics()
{
	this->maxVelocity = 5.f;
	this->minVelocity = 1.f;
	this->acceleration = 1.05f;
	this->drag = 0.96f;
	this->gravity = 1.5f;
	this->MaxYVelocity = -10.f;
	this->jumpVelocity = -60.0f;
	this->dashspeed = 15.f;
	this->maxDashTime = .1f;

}

Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->initPhysics();

	

}

Player ::~Player()
{

}

const bool& Player::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch; //Have not documented this yet as I have not fixed the animation yet
}

const sf::Vector2f Player::getPosition() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

const float Player::getvelocityY() const
{
	return this->velocity.y;
}

const float Player::getVelocityX() const
{
	return this->velocity.x;
}

void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Player::resetVeloictyY()
{
	this->velocity.y = 0.f;
}

void Player::resetVelocityX()
{
	this->velocity.x = 0.f;
}

void Player::updateDt()
{
	// Updates Delta TIme with the time that elapses after each frame
		this->dt = this->dtClock.getElapsedTime().asSeconds();
}


void Player::updateAnimations()
{
	if (this->animationStates == PLAYER_ANIMATION_STATES::Idle)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.25f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 49.25f;
			if (this->currentFrame.left >= 147.75f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animationStates == PLAYER_ANIMATION_STATES::Right_Move)
	{

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 92.0f;
			this->currentFrame.left += 49.1f;
			if (this->currentFrame.left >= 245.9f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	else if (this->animationStates == PLAYER_ANIMATION_STATES::Left_Move)
	{

		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 92.0f;
			this->currentFrame.left += 49.1f;
			if (this->currentFrame.left >= 245.9f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);
			
		}
		this->sprite.setScale(-1.f, 1.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 3.f, 0.f);
	}
	/*
	else if (this->animationStates == PLAYER_ANIMATION_STATES::Jumping)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwitch())
		{
			this->currentFrame.top = 196.0f;
			this->currentFrame.left += 59.8f;
			if (this->currentFrame.left >= 778.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sprite.setTextureRect(this->currentFrame);

		}
		this->sprite.setScale(1.f, 1.f);
		this->sprite.setOrigin(0.f, 0.f);
	}
	*/
	else
	{
		this->animationTimer.restart();
	}
}

void Player::updateMovement()
{
		//Move Player
		
	if (canDash)
	{
		if (leftKeyPressed())
		{
			this->move(-1.f, 0.f);
			this->lookingLeft = true;


		}
		else if (rightKeyPressed())
		{
			this->move(1.f, 0.f);
			this->lookingLeft = false;


		}
	}
	if (canJump && jumpKeyPressed())
	{

		this->velocity.y = jumpVelocity;
		this->canJump = false;
		this->jumpingSound.play();
		this->animationStates = PLAYER_ANIMATION_STATES::Jumping;

		if(this->velocity.y < -60.f)
			this->velocity.y = -60.f;

		


	}
	if (dashKeyPressed() && canDash)
	{
		this->canDash = false;
		this->dashTimer.restart();
		if (this->lookingLeft == true)
		{
			this->velocity.x = dashspeed * -1.f;
		}
		else
		{
			this->velocity.x = dashspeed;
		}
	}
	if (!canDash)
	{
		if ((dashTimer.getElapsedTime().asSeconds()) > maxDashTime)
		{
			canDash = true;
			this->velocity.x = 0.f;
			
		}
	}
		

	if (this->velocity.x > 0.f)
	{
		this->animationStates = PLAYER_ANIMATION_STATES::Right_Move;
	}
	else if (this->velocity.x < 0.f)
	{
		this->animationStates = PLAYER_ANIMATION_STATES::Left_Move;
	}
	else
	{
		this->animationStates = PLAYER_ANIMATION_STATES::Idle;
	}
}

inline bool Player::jumpKeyPressed()
{
	return(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W));
}
inline bool Player::dashKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift));
}
inline bool Player::leftKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left));
}
inline bool Player::rightKeyPressed()
{
	return (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right));
}

void Player::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Player::move(const float dir_x, const float dir_y)
{
	//Accceleration
	this->velocity.x += dir_x * this->acceleration;
	

	//Limit Velocity
	if (std::abs(this->velocity.x) > this->maxVelocity)
	{
		this->velocity.x = this->maxVelocity * ((this->velocity.x < 0.f) ? -1.f : 1.f);
	}

}	

void Player::updatePhysics()
{
	//Gravity
	this->velocity.y += gravity * 1.f;

	//Deceleration
	this->velocity *= this->drag;

	//Limit Deceleration
	if (std::abs(this->velocity.x) < this->minVelocity)
		this->velocity.x = 0.f;
	if (std::abs(this->velocity.y) < this->minVelocity)
		this->velocity.y = 0.f;
	if (std::abs(this->velocity.x) <= 1.f)
		this->velocity.x = 0.f;

	this->sprite.move(this->velocity);

	
}

void Player::update()
{
	this->updateDt();
	this->updateMovement();
	this->updatePhysics();
	this->updateAnimations();
	
}



void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
};