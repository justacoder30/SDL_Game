#include "Map.h"
#include <tmxlite/TileLayer.hpp>

tmx::Map Map::map;

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

        //std::cout << ts.getFirstGID() << " ";
        for (auto y = 0u; y < mapSize.y; ++y)
        {
            for (auto x = 0u; x < mapSize.x; ++x)
            {
                const auto idx = y * mapSize.x + x;
                //auto idIndex = (tileIDs[idx].ID - ts.getFirstGID());
                //std::cout << tileIDs[idx].ID << " ";
                if (idx < tileIDs.size() &&
                    tileIDs[idx].ID >= ts.getFirstGID() &&
                    tileIDs[idx].ID < (ts.getFirstGID() + ts.getTileCount()))
                {
                    //tex coords
                    auto idIndex = (tileIDs[idx].ID - ts.getFirstGID());

                    Rect src = getSrcById(idIndex, tileCountX, tileCountY, mapTileSize.x);
                    Rect dst = Rect(x * mapTileSize.x, y * mapTileSize.x, mapTileSize.x, mapTileSize.x);

                    TiledMap* tiled = new TiledMap(*textures[i], dst, src);
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

Map::Map(int level, std::vector<Entity*>& Entities)
{
    InitMap("resource/Map1/map1.tmx");

    auto tileSets = map.getTilesets();
	std::vector<Texture*> texure = GetTextures(map.getTilesets());

	const auto& mapLayers = map.getLayers();
    //const auto& layer1 = layers[layerIndex]->getLayerAs<tmx::ObjectGroup>();
	for (auto i = 0u; i < mapLayers.size(); ++i)
	{
        if (mapLayers[i]->getType() == tmx::Layer::Type::Tile)
		{
			CreateMap(map, i, texure, Entities);
		}
	}
}

TiledMap::TiledMap(Texture _texure, Rect _dst, Rect _src)
{
	tex = _texure;
    dst = _dst;
	src = _src;

    rect = dst;
    old_rect = rect;
}

void TiledMap::Update()
{
    dst.x = rect.x + Global.camera.current_pos.x;
    dst.y = rect.y + Global.camera.current_pos.y;
}

void TiledMap::Draw()
{    
	window.blit(tex, dst, src);
}
