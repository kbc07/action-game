#include "stdafx.h"
#include "Game.h"
#include"Player.h"
#include"Enemy.h"
#include"BackGround.h"
#include"GameCamera.h"

bool Game::Start()
{
	player = NewGO<Player>(0, "Player");
	player->SetPosition({ 0.0f,10.0f,-3000.0f });

	backGround = NewGO<BackGround>(0, "backGround");

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = NewGO<Enemy>(0, "enemy");
		enemy[i]->SetPosition({ -1000.0f+i*200.0f,0.0f,0.0f });
	}
	gameCamera = NewGO<GameCamera>(0, "gameCamera");

	return true;
}


void Game::Update()
{
	for(int i=0;i<10;i++)
		enemy[i]->SetPlayerPosition(player->GetPosition());

	gameCamera->SetTargetPosition(player->GetPosition());

	m_modelRender.Update();
}

