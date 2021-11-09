#pragma once

class Player;

class GameCamera :public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	void Move();
	void Update();
	void SetTargetPosition(const Vector3& position)
	{
		cameraTarget = position;
	}
private:
	Vector3 cameraDistance;
	Vector3 cameraPosition;
	Quaternion cameraRotation;
	Player* player;
	Vector2 cameraMove = { 0.0f,0.0f };
	Vector3 cameraDirection;
	Vector3 cameraOldDistance;
	Vector3 cameraAxisX;
	Vector3 cameraTarget;
};

