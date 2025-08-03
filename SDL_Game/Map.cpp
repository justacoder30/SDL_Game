#include "Map.h"
#include <tmxlite/TileLayer.hpp>
#include <filesystem>

std::vector<Texture> GetTextures(const std::vector<tmx::Tileset>& tileSets) {
	std::vector<Texture> texure;
	texure.reserve(tileSets.size());

	for (auto ts : tileSets)
	{
		texure.push_back(Texture(ts.getImagePath()));
	}

	return texure;
}

float min(const float& a, const float& b) {
	return (a < b) ? a : b;
}

float max(const float& a, const float& b) {
    return (a > b) ? a : b;
}

void Map::BuildGeometryBatches(const tmx::Map& map, uint32_t layerIndex)
{
    const auto& layer = map.getLayers()[layerIndex]->getLayerAs<tmx::TileLayer>();
    const auto& tileIDs = layer.getTiles();
    const auto& mapSize = map.getTileCount();
    const auto& mapTileSize = map.getTileSize();
    const auto& tileSets = map.getTilesets();

    int maxX = 0, maxY = 0;
    this->mapTileSize = mapTileSize.x;

    for (size_t i = 0; i < tileSets.size(); ++i)
    {
        const auto& ts = tileSets[i];
        int tileCountX = textures[i].getWidth() / mapTileSize.x;
        int tileCountY = textures[i].getHeight() / mapTileSize.y;

        //SDL_Texture* texPtr = textures[i].getTex();
        auto& batch = batches[textures[i].getTex()];

        for (uint32_t y = 0; y < mapSize.y; ++y)
        {
            for (uint32_t x = 0; x < mapSize.x; ++x)
            {
                const auto idx = y * mapSize.x + x;
                if (idx >= tileIDs.size()) continue;

                const auto& tile = tileIDs[idx];
                if (tile.ID < ts.getFirstGID() || tile.ID >= ts.getFirstGID() + ts.getTileCount())
                    continue;

                int idIndex = tile.ID - ts.getFirstGID();
                SDL_RendererFlip flip;
                float rotate = CaculateRotate(tile.flipFlags, flip);

                Rect src = getSrcById(idIndex, tileCountX, tileCountY, mapTileSize.x);
                Rect dst(x * mapTileSize.x, y * mapTileSize.y, mapTileSize.x, mapTileSize.y);

                SDL_Vertex verts[4];
                float px[4] = { dst.x, dst.x + dst.w, dst.x + dst.w, dst.x };
                float py[4] = { dst.y, dst.y, dst.y + dst.h, dst.y + dst.h };

                Vector center(dst.w / 2.0f, dst.h / 2.0f);
                float cx = dst.x + center.x;
                float cy = dst.y + center.y;
                float angleRad = rotate * M_PI / 180.0f;
                float cosA = cosf(angleRad), sinA = sinf(angleRad);

                for (int j = 0; j < 4; ++j) {
                    float dx = px[j] - cx;
                    float dy = py[j] - cy;
                    verts[j].position.x = cosA * dx - sinA * dy + cx;
                    verts[j].position.y = sinA * dx + cosA * dy + cy;
                }

                float texW = textures[i].getWidth();
                float texH = textures[i].getHeight();
                float u0 = src.x / texW, u1 = (src.x + src.w) / texW;
                float v0 = src.y / texH, v1 = (src.y + src.h) / texH;

                float u[4] = { u0, u1, u1, u0 };
                float v[4] = { v0, v0, v1, v1 };

                if (flip & SDL_FLIP_HORIZONTAL) { std::swap(u[0], u[1]); std::swap(u[3], u[2]); }
                if (flip & SDL_FLIP_VERTICAL) { std::swap(v[0], v[3]); std::swap(v[1], v[2]); }

                for (int j = 0; j < 4; ++j) {
                    verts[j].tex_coord = { u[j], v[j] };
                    verts[j].color = textures[i].color;
                }

                int indexOffset = batch.vertices.size();
                batch.vertices.insert(batch.vertices.end(), std::begin(verts), std::end(verts));

                int quad[6] = { 0, 1, 2, 2, 3, 0 };
                for (int j = 0; j < 6; ++j) {
                    batch.indices.push_back(indexOffset + quad[j]);
                }

                maxX = std::max(maxX, (int)x);
                maxY = std::max(maxY, (int)y);
            }
        }
    }

    width = maxX * mapTileSize.x;
    height = maxY * mapTileSize.y;
}

//void Map::Draw()
//{
//    Vector cameraOffset = Global.camera.transform;
//
//    for (auto& [texture, batch] : batches)
//    {
//         //Clone vertices để không ảnh hưởng batch gốc
//        std::vector<SDL_Vertex> transformedVerts = batch.vertices;
//
//        for (auto& v : transformedVerts)
//        {
//            v.position.x += cameraOffset.x;
//            v.position.y += cameraOffset.y;
//        }
//
//        SDL_RenderGeometry(
//            Global.Renderer,
//            texture,
//            transformedVerts.data(),
//            transformedVerts.size(),
//            batch.indices.data(),
//            batch.indices.size()
//        );
//    }
//}

void Map::Draw()
{
    Vector& cameraOffset = Global.camera.transform;
    Rect& visibleRect = Global.camera.visibleWoldRect;
	std::vector<Rect> rect;

    for (auto& [texture, batch] : batches)
    {
        std::vector<SDL_Vertex> transformedVerts;
        std::vector<int> transformedIndices;
        int vertexBaseIndex = 0;

        // Mỗi tile là 4 vertex, 6 indices (2 tam giác)
        for (int i = 0; i < batch.vertices.size(); i += 4)
        {
            // Lấy 4 vertex của 1 tile
            SDL_Vertex v0 = batch.vertices[i + 0];
            SDL_Vertex v1 = batch.vertices[i + 1];
            SDL_Vertex v2 = batch.vertices[i + 2];
            SDL_Vertex v3 = batch.vertices[i + 3];

            // Tạo bounding rect từ 4 điểm

            Rect tileRect(v0.position.x, v0.position.y, mapTileSize, mapTileSize);

            // Kiểm tra va chạm với camera
            if (!visibleRect.checkCollide(tileRect))
                continue;


            // Offset theo camera
            v0.position.x += cameraOffset.x; v0.position.y += cameraOffset.y;
            v1.position.x += cameraOffset.x; v1.position.y += cameraOffset.y;
            v2.position.x += cameraOffset.x; v2.position.y += cameraOffset.y;
            v3.position.x += cameraOffset.x; v3.position.y += cameraOffset.y;

			//rect.push_back(Rect(v0.position.x, v0.position.y, mapTileSize, mapTileSize));
            // Thêm vào vertex buffer mới
            transformedVerts.push_back(v0);
            transformedVerts.push_back(v1);
            transformedVerts.push_back(v2);
            transformedVerts.push_back(v3);

            // Indices cho 2 tam giác: (0, 1, 2), (2, 3, 0)
            transformedIndices.push_back(vertexBaseIndex + 0);
            transformedIndices.push_back(vertexBaseIndex + 1);
            transformedIndices.push_back(vertexBaseIndex + 2);
            transformedIndices.push_back(vertexBaseIndex + 2);
            transformedIndices.push_back(vertexBaseIndex + 3);
            transformedIndices.push_back(vertexBaseIndex + 0);

            vertexBaseIndex += 4;
        }

        // Nếu không có gì cần vẽ
        if (transformedVerts.empty()) continue;

        SDL_RenderGeometry(
            Global.Renderer,
            texture,
            transformedVerts.data(),
            transformedVerts.size(),
            transformedIndices.data(),
            transformedIndices.size()
        );

        /*for(auto& r : rect)
        {
			DrawRectStatic(r);
		}*/
    }
}





Map::Map(const std::string& level)
{
    InitMap("resource/Map/" + level);
    textures = GetTextures(map.getTilesets());

    const auto& mapLayers = map.getLayers();
    for (auto i = 0u; i < mapLayers.size(); ++i)
    {
        if (mapLayers[i]->getType() == tmx::Layer::Type::Tile)
        {
            BuildGeometryBatches(map, i);
        }
    }

    backDrop = true;
}

float Map::CaculateRotate(uint8_t flags, SDL_RendererFlip& flip)
{
    flip = SDL_FLIP_NONE;
    bool h = flags & tmx::TileLayer::FlipFlag::Horizontal;
    bool v = flags & tmx::TileLayer::FlipFlag::Vertical;
    bool d = flags & tmx::TileLayer::FlipFlag::Diagonal;
    float r = 0.f;

    if (d) {
        if (h && !v) r = 90.f;
        else if (!h && v) r = 270.f;
        else if (h && v) { r = 270.f; flip = SDL_FLIP_VERTICAL; }
        else { r = 90.f; flip = SDL_FLIP_VERTICAL; }
    }
    else {
        if (h && v) r = 180.f;
        else if (h) { r = 0.f; flip = SDL_FLIP_HORIZONTAL; }
        else if (v) { r = 0.f; flip = SDL_FLIP_VERTICAL; }
    }

    return r;
}

Rect Map::getSrcById(int index, int tileCountX, int tileCountY, int mapTileSize)
{
    Rect src;
    src.w = src.h = mapTileSize;
    src.x = (index % tileCountX) * mapTileSize;
    src.y = (index / tileCountX) * mapTileSize;
    return src;
}

void Map::InitMap(const std::string& f_path)
{
    if (!map.load(f_path)) std::cerr << "Failed to load map: " << f_path << "\n";
}

float Map::getWidth() const { return width; }
float Map::getHeight() const { return height; }

std::vector<Rect> Map::GetObjectGroup(const std::string& name)
{
    std::vector<Rect> rects;
    const auto& mapLayers = map.getLayers();
    for (const auto& layer : mapLayers) {
        if (layer->getName() == name) {
            for (const auto& obj : layer->getLayerAs<tmx::ObjectGroup>().getObjects()) {
                rects.emplace_back(obj.getPosition().x, obj.getPosition().y,
                    obj.getAABB().width, obj.getAABB().height);
            }
        }
    }
    return rects;
}

void Map::Update()
{
    // Map-level logic here (e.g., animation tiles later)
}
