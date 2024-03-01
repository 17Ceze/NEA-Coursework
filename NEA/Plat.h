#pragma once
#include "Precomp.h"
class Plat
{
	private:
		sf::Sprite sprite;
		sf::Texture textureSheet;
		
		sf::IntRect spriteFrame;

		//Private Functions
		void initVariables();
		void initTexture();
		void initSprite();
		

	public:
		Plat();
		~Plat();


		//Acccessors
		const sf::Vector2f getPosition() const;
		const sf::FloatRect getGlobalBounds() const;

		//Modifiers
		void setPosition(const float x, const float y);


		//Functions
		void update();
		void render(sf::RenderTarget& target);

};