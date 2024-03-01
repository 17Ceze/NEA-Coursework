#pragma once
#include "Precomp.h"




enum PLAYER_ANIMATION_STATES { Idle = 0, Left_Move, Right_Move, Jumping };

class Player
{

private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	sf::Clock dtClock;
	sf::Clock dashTimer;
	float dt;

	//Animation
	short animationStates;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Sounds
	//Jumping
	sf::Sound jumpingSound;
	sf::SoundBuffer pJumpingSound;
	//Running
	sf::Sound runningSound;
	sf::SoundBuffer pRunningSound;


	// Player Physics 
	sf::Vector2f velocity;
	float maxVelocity;
	float minVelocity;
	float acceleration;
	float drag;
	float gravity;
	float MaxYVelocity;
	float jumpVelocity;
	bool canJump;
	float jumpTimer;
	bool canDash;
	float dashspeed;
	float maxDashTime;
	bool lookingLeft = false;
	
	
	
	

	//Health Points
	
	//Private functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void initPhysics();

public:
	Player();
	virtual ~Player();

	//Accessors 
	const bool& getAnimationSwitch();
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const float getvelocityY() const;
	const float getVelocityX() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVeloictyY();
	void resetVelocityX();
	void setCanJump(const bool canJump) { this->canJump = canJump; }
	void setCanDash(const bool canDash) { this->canDash = canDash; }
	void updateDt();


	//Functions
	inline bool jumpKeyPressed();
	inline bool dashKeyPressed();
	inline bool leftKeyPressed();
	inline bool rightKeyPressed();
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y);
	void updatePhysics();
	void update();
	void updateAnimations();
	void updateMovement();
	void render(sf::RenderTarget& target);
	
};