#pragma once
#include "Precomp.h"
enum levelEndState{ Untouched = 0, Touched };

class LevelEnd
{
private:
	sf::Sprite sprite;
	sf::Texture textureSheet;
	sf::Clock animationTimer;

	//Animation
	short animationStates;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Private Functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();

public:
	LevelEnd();
	~LevelEnd();


	//Acccessors
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	//Modifiers
	void setPosition(const float x, const float y);


	//Functions
	void update();
	const bool& getAnimationSwitch();
	void resetAnimationTImer();
	void updateAnimations();
	void render(sf::RenderTarget& target);

};

