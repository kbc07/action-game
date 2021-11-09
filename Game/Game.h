#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class Enemy;
class BackGround;
class GameCamera;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();

private:
	ModelRender m_modelRender;
	BackGround* backGround;
	Player* player;
	Enemy* enemy[10];
	GameCamera* gameCamera;
};

