#pragma once
#include "Tile.h"
#include "Precomp.h"



 
class Tilemap
{
private:
	std::vector< std::vector<Tile*>>tiles;
	std::vector<sf::Texture*> textureSheets;

	unsigned tileSize;
	


public:
	Tilemap(unsigned width, unsigned height, std::vector<sf::Texture*> texture_sheets, unsigned tile_size);
	~Tilemap();
	
	//Inline Functions
	inline const unsigned& getTileSize() const { return this->tileSize; };

	//Functions 
	void addTile(unsigned x, unsigned y,unsigned texture_index, sf::IntRect texture_rect);
	void removeTile(unsigned x, unsigned y);
	void addDamagingTile(unsigned x, unsigned y, unsigned texture_index, sf::IntRect texture_rect);
	void update();
	void render(sf::RenderTarget& target);

	std::vector<std::vector<Tile*>>& getTiles() { return this->tiles; }

	
};
