#pragma once
#include "Precomp.h"
class Tile
{

private:
	sf::Sprite sprite;
	const bool damaging;

public:
	Tile(const unsigned& grid_pos_x, const unsigned& grid_pos_y, const unsigned& tile_size, 
		sf::Texture* texture_sheet, sf::IntRect texture_rect, bool damaging = false);

	const sf::FloatRect getGlobalbounds() const;

	void update();
	bool isDamaging() const { return damaging; };
	void render(sf::RenderTarget& target);


};

