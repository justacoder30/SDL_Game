#include "Map.h"
#include <tmxlite/TileLayer.hpp>

tmx::Map Map::map;

const std::uint32_t FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const std::uint32_t FLIPPED_VERTICALLY_FLAG = 0x40000000;
const std::uint32_t FLIPPED_DIAGONALLY_FLAG = 0x20000000;


std::vector<Texture*> GetTextures(std::vector<tmx::Tileset> tileSets) {
	std::vector<Texture*> texure;

	for (auto ts : tileSets)
	{
		texure.push_back(new Texture(ts.getImagePath()));
	}

	return texure;
}

Rect getSrcById(int index, int tileCountX, int tileCountY, int mapTileSize) {
    int cnt = 0;
    Rect src;
    for (int y = 0; y < tileCountY; ++y) {
        for (int x = 0; x < tileCountX; ++x) {
            if (cnt == index) {
                src.x = x * mapTileSize;
                src.y = y * mapTileSize;
                src.w = mapTileSize;
                src.h = mapTileSize;
            }
            cnt++;
        }
    }

    return src;
}

void Map::CreateMap(const tmx::Map& map, std::uint32_t layerIndex, const std::vector<Texture*> textures, std::vector<Entity*>& Entities) {
    const auto& layers = map.getLayers();
    const auto& layer = layers[layerIndex]->getLayerAs<tmx::TileLayer>();
    const auto mapSize = map.getTileCount();
    const auto mapTileSize = map.getTileSize();

    const auto& tileSets = map.getTilesets();

    for (auto i = 0u; i < tileSets.size(); ++i)
    {
        //check tile ID to see if it falls within the current tile set
        const auto& ts = tileSets[i];
        const auto& tileIDs = layer.getTiles();

        const auto tileCountX = textures[i]->getWidth() / mapTileSize.x;
        const auto tileCountY = textures[i]->getHeight() / mapTileSize.y;

        for (auto y = 0u; y < mapSize.y; ++y)
        {
            for (auto x = 0u; x < mapSize.x; ++x)
            {
                const auto idx = y * mapSize.x + x;
                //auto idIndex = (tileIDs[idx].ID - ts.getFirstGID());
                if (idx < tileIDs.size() &&
                    tileIDs[idx].ID >= ts.getFirstGID() &&
                    tileIDs[idx].ID < (ts.getFirstGID() + ts.getTileCount()))
                {
                    //tex coords
                    auto idIndex = (tileIDs[idx].ID - ts.getFirstGID());  
                    
                    SDL_FlipMode flip;
                    float rotate = CaculateRotate(tileIDs[idx].flipFlags, flip);

                    Rect src = getSrcById(idIndex, tileCountX, tileCountY, mapTileSize.x);
                    Rect dst = Rect(x * mapTileSize.x, y * mapTileSize.x, mapTileSize.x, mapTileSize.x);

                    TiledMap* tiled = new TiledMap(*textures[i], dst, src, rotate, flip);
                    Entities.push_back(tiled);

                    if (layers[layerIndex]->getName() == "Terrain")
                        Collisions.push_back(tiled);

                }
            }
        }
    }
}

Vector Map::GetPos(std::string name)
{
    auto tileSets = Map::map.getTilesets();
    const auto& mapLayers = Map::map.getLayers();

    for (auto i = 0u; i < mapLayers.size(); ++i)
    {
        if (mapLayers[i]->getName() == name) {
            const auto& layer1 = mapLayers[i]->getLayerAs<tmx::ObjectGroup>();
            const auto& obj = layer1.getObjects();
            return Vector(obj[0].getPosition().x, obj[0].getPosition().y);
        }
    }

    return Vector();
}

void Map::InitMap(std::string f_path)
{
    if (!Map::map.load(f_path))
        std::cout << "Failed to load map: " << f_path << std::endl;
}

float Map::CaculateRotate(uint8_t flags, SDL_FlipMode& flip)
{
    flip = SDL_FLIP_NONE;

    bool flippedHorizontally = (flags & tmx::TileLayer::FlipFlag::Horizontal);
    bool flippedVertically = (flags & tmx::TileLayer::FlipFlag::Vertical);
    bool flippedDiagonally = (flags & tmx::TileLayer::FlipFlag::Diagonal);
    float rotation = 0.f;

    if (flippedDiagonally)
    {
        if (flippedHorizontally && !flippedVertically)
        {
            rotation = 90.f;
        }
        else if (!flippedHorizontally && flippedVertically)
        {
            rotation = 270.f;
        }
        else if (flippedHorizontally && flippedVertically)
        {
            rotation = 270.f; 
            flip = SDL_FLIP_VERTICAL;
        }
        else
        {
            rotation = 90.f; 
            flip = SDL_FLIP_VERTICAL;
        }
    }
    else
    {
        if (flippedHorizontally && flippedVertically)
        {
            rotation = 180.f;
        }
        else if (flippedHorizontally)
        {
            // flip X
            rotation = 0.f; 
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (flippedVertically)
        {
            // flip Y
            rotation = 0.f;
            flip = SDL_FLIP_VERTICAL;
        }
    }

    return rotation;
}

Map::Map(int level, std::vector<Entity*>& Entities)
{
    InitMap("resource/Map/map" + std::to_string(level) + ".tmx");

    auto tileSets = map.getTilesets();
	std::vector<Texture*> texure = GetTextures(map.getTilesets());

	const auto& mapLayers = map.getLayers();
	for (auto i = 0u; i < mapLayers.size(); ++i)
	{
        if (mapLayers[i]->getType() == tmx::Layer::Type::Tile)
		{
			CreateMap(map, i, texure, Entities);
		}
	}
}

TiledMap::TiledMap(Texture _texure, Rect _dst, Rect _src, float _rotate, SDL_FlipMode _flip)
{
	tex = _texure;
    dst = _dst;
	src = _src;

    rect = dst;
    old_rect = rect;

    rotate = _rotate;

    flip = _flip;
}

void TiledMap::Update()
{
    dst.x = rect.x + Global.camera.current_pos.x;
    dst.y = rect.y + Global.camera.current_pos.y;
}

void TiledMap::Draw()
{    
	window.blit(tex, dst, src, rotate, flip);
}
