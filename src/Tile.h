// This class is used to describe terrain tiles
#ifndef TILE_H
#define TILE_H
#include <string>
#include <list>
#include <SFML/Graphics.hpp>

class Tile
{
    friend class Level;

	public:
		Tile(int terrainType, sf::Texture& texture);
		Tile(int terrainType, sf::Texture& texture, sf::IntRect& textureRect);
		Tile(int terrainType);
		Tile();
		sf::Sprite getSprite() {return sprite;}
		std::string getType(){return tileType;}
		const int& getTerrainDef() { return terrainDef; }
		void setSprite(sf::Texture& texture, sf::IntRect& textureRect);

	private:
		std::string tileType;						// The type of terrain tyle
		int moveCost;								// The amount of movement points it costs to cross this tile
		int terrainDef;								// The amount of defense a unit gains on this tile
		sf::Sprite sprite;

		void setStats(int terrainType);
};
#endif //TILE_H
