#pragma once
#include "Texture.h"
#include "Vector.h"
#include "Entity.h"
#include <tmxlite/Map.hpp>
#include <unordered_map>

struct GeometryBatch {
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;
};

class Map : public Entity
{
private:
    float width;
    float height;
    inline static tmx::Map map;

    std::unordered_map<SDL_Texture*, GeometryBatch> batches;
    std::vector<Texture> textures;

    void InitMap(const std::string& f_path);
    float CaculateRotate(uint8_t flags, SDL_RendererFlip& flip);
    Rect getSrcById(int index, int tileCountX, int tileCountY, int mapTileSize);
    void BuildGeometryBatches(const tmx::Map& map, uint32_t layerIndex);

public:
    Map() {}
    Map(const std::string& level);

    std::vector<Rect> GetObjectGroup(const std::string& name);
    float getWidth() const;
    float getHeight() const;

    void Update();
    void Draw();
};
