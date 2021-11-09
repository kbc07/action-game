#include "stdafx.h"
#include "GameCamera.h"
#include"Player.h"

GameCamera::GameCamera()
{
	g_camera3D->SetFar(50000.0f);
	g_camera3D->SetNear(1.0f);
	
	player = FindGO<Player>("player");

	

	cameraDistance.Set(-400.0f, 180.0f, 0.0f);
	
}

GameCamera::~GameCamera()
{

}

void GameCamera::Move()
{
	cameraOldDistance = cameraDistance;

	cameraMove.x = g_pad[0]->GetRStickXF() * (-3.0f);
	cameraMove.y = g_pad[0]->GetRStickYF() * (-3.0f);

	cameraRotation.SetRotationDeg(Vector3::AxisY, 2.0f*cameraMove.x);
	cameraRotation.Apply(cameraDistance);

	cameraAxisX.Cross(Vector3::AxisY, cameraDistance);
	cameraAxisX.Normalize();

	cameraRotation.SetRotationDeg(cameraAxisX, 2.0f*cameraMove.y);
	cameraRotation.Apply(cameraDistance);
	
	cameraDirection = cameraDistance;
	cameraDirection.Normalize();

	
	cameraPosition = cameraTarget + cameraDistance;

	if (cameraDirection.y < -0.2f)
		cameraDistance = cameraOldDistance;
	else if (cameraDirection.y > 0.9f)
		cameraDistance = cameraOldDistance;

	cameraTarget += g_camera3D->GetForward() * 20.0f;
	cameraTarget.y += 70.0f;
	g_camera3D->SetTarget(cameraTarget);

	g_camera3D->SetPosition(cameraPosition);
}
void GameCamera::Update()
{
	Move();


	g_camera3D->Update();
}