#pragma once

class Enemy: public IGameObject
{
public:
	Enemy();
	~Enemy();
	void Move();
	void Rotation();
	void Update();
	void Render(RenderContext& rc);
	void SetPosition(const Vector3& position1)
	{
		enemyPosition = position1;
	}
	void SetPlayerPosition(const Vector3& position2)
	{
		ePlayerPosition = position2;
	}
	const Vector3& GetPosition() const
	{
		return enemyPosition;
	}
	const Vector3& GetPlayerPosition() const
	{
		return ePlayerPosition;
	}

private:
	Vector3 enemyPosition = { 0.0f,0.0f,0.0f };
	Quaternion enemyRotation;
	ModelRender enemyRender;
	Vector3 enemyToPlayer;
	float enemyHeight = 50.0f;
	float enemyRad = 50.0f;
	Vector3 enemySpeed;
	CharacterController enemyController;
	Vector3 ePlayerPosition;
	Vector3 enemyMoveSpeed;
	float enemyAngle = 0.0f;
	Vector3 enemyDistance;
};

