#pragma once
#include "Sprite.h"

class Background : public Entity
{
private:
	std::vector<Entity*> clouds;
public:
	Background();
	Background(Vector size);
	~Background()
	{
		/*for (auto& cloud : clouds) {
			delete cloud;
		}*/
		freeEntities();
		LOG("Background destroyed");
	}
	void Update(const float& dt);
	void Draw();
};

