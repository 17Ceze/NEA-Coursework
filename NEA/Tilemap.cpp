#include "Tilemap.h"


Tilemap::Tilemap(unsigned width, unsigned height, std::vector<sf::Texture*> texture_sheets, unsigned tile_size)
    : textureSheets(texture_sheets), tileSize(tile_size)
{
    this->tiles.resize(height, std::vector<Tile*>(width, nullptr));
}

Tilemap::~Tilemap()
{
    for (auto& row : this->tiles)
    {
        for (auto& tile : row)
        {
            delete tile;
        }
    }
}

void Tilemap::addTile(unsigned x, unsigned y,unsigned texture_index, sf::IntRect texture_rect)
{
    if (y < this->tiles.size() && x < this->tiles[y].size())
    {
        delete this->tiles[y][x];
        this->tiles[y][x] = new Tile(x, y, this->tileSize, this->textureSheets[texture_index], sf::IntRect(0, 0, this->tileSize, this->tileSize), false);
    }
}

void Tilemap::removeTile(unsigned x, unsigned y)
{
    if (y < this->tiles.size() && x < this->tiles[y].size())
    {
        delete this->tiles[y][x];
        this->tiles[y][x] = nullptr;
    }
}

void Tilemap::addDamagingTile(unsigned x, unsigned y, unsigned texture_index, sf::IntRect texture_rect)
{
    if (y < this->tiles.size() && x < this->tiles[y].size())
    {
        delete this->tiles[y][x];
        this->tiles[y][x] = new Tile(x, y, this->tileSize, this->textureSheets[texture_index], sf::IntRect(0, 0, this->tileSize, this->tileSize), true);
    }
}


void Tilemap::update()
{
    for (auto& row : this->tiles)
    {
        for (auto& tile : row)
        {
            if (tile != nullptr)
            {
                tile->update();
            }
        }
    }
}

void Tilemap::render(sf::RenderTarget& target)
{
    for (auto& row : this->tiles)
    {
        for (auto& tile : row)
        {
            if (tile != nullptr)
            {
                tile->render(target);
            }
        }
    }
}

