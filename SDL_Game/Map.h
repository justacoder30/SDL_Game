#pragma once
#include "Texture.h"
#include "Vector.h"
#include "Entity.h"
#include <tmxlite/Map.hpp>

class TiledMap : public Entity
{
private:
	Rect src;
	Rect dst;
public:
	TiledMap() {}
	TiledMap(Texture _texure, Rect _dst, Rect _src);
	void Update();
	void Draw();
};

class Map
{
private:
	std::vector<TiledMap*> tiledmap;
	//static tmx::Map map;
public:
	Map() {}
	Map(int level, std::vector<Entity*>& Entities);
	void CreateMap(const tmx::Map& map, std::uint32_t layerIndex, const std::vector<Texture*> textures, std::vector<Entity*>& Entities);
};

