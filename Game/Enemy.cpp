#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy()
{
	enemyRender.Init("Assets/modelData/enemy/cat.tkm");
	enemyController.Init(enemyRad, enemyHeight, enemyPosition);

	enemyRender.SetPosition(enemyPosition);
}

Enemy::~Enemy()
{

}

void Enemy::Move()
{
	enemyToPlayer = ePlayerPosition - enemyPosition;
	enemyDistance = enemyToPlayer;
	enemyToPlayer.y = 0.0f;
	enemyToPlayer.Normalize();

	
	if (sqrt(enemyDistance.x * enemyDistance.x + enemyDistance.y * enemyDistance.y + enemyDistance.z * enemyDistance.z) <= 500.0f)
		enemyMoveSpeed = enemyToPlayer * 200.0f;
	else
		enemyMoveSpeed = { 0.0f,0.0f,0.0f };

	enemyPosition = enemyController.Execute(enemyMoveSpeed, 1.0f / 60.0f);

	enemyRender.SetPosition(enemyPosition);
}

void Enemy::Rotation()
{
	if (fabsf(enemyMoveSpeed.x) < 0.1f && fabsf(enemyMoveSpeed.z) < 0.1f)
		return;

	enemyAngle = atan2(-enemyMoveSpeed.x, enemyMoveSpeed.z);

	enemyRotation.SetRotationY(-enemyAngle);

	enemyRender.SetRotation(enemyRotation);
}

void Enemy::Update()
{
	Move();
	Rotation();

	enemyRender.Update();
}

void Enemy::Render(RenderContext& rc)
{
	enemyRender.Draw(rc);
}