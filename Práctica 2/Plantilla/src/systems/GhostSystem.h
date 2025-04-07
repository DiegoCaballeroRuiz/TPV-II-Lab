#pragma once

#include "../ecs/System.h"
#include <vector>
#include "../utils/Vector2D.h"
#include <SDL.h>

class GhostSystem : public ecs::System {
	ecs::grpId_t _ghostGroup;
	float _lastGhostSpawnTime, _spawnDelay, _ghostSpeed, _changeTargetProbability;
	std::vector<Vector2D> _spawnPoints;
	SDL_Rect  _defaultSrcRect, _blueSrcRect;
	bool _canSpawn;
public:
	GhostSystem();
	virtual ~GhostSystem();
	void initSystem() override;
	void update() override;
	void recieve(const Message& msg) override;

};