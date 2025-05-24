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
	SDL_FlipMode flip;
	TiledMap() {}
	TiledMap(Texture _texure, Rect _dst, Rect _src, float _rotate = 0.0, SDL_FlipMode _flip = SDL_FLIP_NONE);
	void Update();
	void Draw();
};

class Map
{
private:
	std::vector<TiledMap*> tiledmap;
	static tmx::Map map;

	void InitMap(std::string f_path);
	float CaculateRotate(uint8_t flags, SDL_FlipMode& flip);
public:
	Map() {}
	Map(int level, std::vector<Entity*>& Entities);
	void CreateMap(const tmx::Map& map, std::uint32_t layerIndex, const std::vector<Texture*> textures, std::vector<Entity*>& Entities);
	Vector GetPos(std::string name);
};

